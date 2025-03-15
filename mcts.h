#include <vector>
#include "jeu.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <limits>  // Nécessaire pour std::numeric_limits
#include <cmath>   // Pour std::sqrt et std::log

struct NoeudMCTS {
    Jeu etat;                // État du jeu à ce nœud
    int visites = 0;         // Nombre de fois que ce nœud a été visité
    double totalReward = 0;  // Somme des récompenses obtenues
    NoeudMCTS* parent = nullptr;  // Pointeur vers le nœud parent
    std::vector<NoeudMCTS*> enfants; // Liste des enfants
    int dernierCoup;         // Le coup qui a mené à cet état

    NoeudMCTS(Jeu etat, NoeudMCTS* parent = nullptr, int coup = -1) 
        : etat(etat), parent(parent), dernierCoup(coup) {}
};

NoeudMCTS* selectionner(NoeudMCTS* racine) {
    NoeudMCTS* noeud = racine;
    while (!noeud->enfants.empty()) {
        noeud = *std::max_element(noeud->enfants.begin(), noeud->enfants.end(), 
            [](NoeudMCTS* a, NoeudMCTS* b) {
                double uctA = (a->visites == 0) ? std::numeric_limits<double>::max() 
                           : (a->totalReward / a->visites) + sqrt(2 * log(a->parent->visites) / a->visites);
                double uctB = (b->visites == 0) ? std::numeric_limits<double>::max() 
                           : (b->totalReward / b->visites) + sqrt(2 * log(b->parent->visites) / b->visites);
                return uctA < uctB;
            });
    }
    return noeud;
}

void expansion(NoeudMCTS* noeud) {
    int nb_coups = noeud->etat.nb_coups();
    for (int coup=1; coup <=nb_coups;++coup) {
        Jeu nouvelEtat = noeud->etat;
        nouvelEtat.joue(coup);
        noeud->enfants.push_back(new NoeudMCTS(nouvelEtat, noeud, coup));
    }
}

double simulation(Jeu etat) {
    while (!etat.terminal()) {
        int nb_coups = etat.nb_coups();
        if (nb_coups == 0) break;  // Aucun coup possible, on sort

        int coupAleatoire = 1; //+ (rand() % nb_coups); // Choisir un coup entre 1 et nb_coups
        etat.joue(coupAleatoire);
    }

    if (etat.victoire())
        return 1.0;
    else if (etat.pat())
        return 0.0;
    else
        return -1.0; // +1 si on gagne, -1 si on perd, 0 si match nul
}

void retropropagation(NoeudMCTS* noeud, double resultat) {
    while (noeud != nullptr) {
        noeud->visites++;
        noeud->totalReward += resultat;
        noeud = noeud->parent;
        //resultat = -resultat; // Inverser le score pour l'adversaire
    }
}

int MCTS(Jeu etat, int iterations) {
    NoeudMCTS* racine = new NoeudMCTS(etat);

    for (int i = 0; i < iterations; i++) {
        NoeudMCTS* noeud = selectionner(racine);
        if (!noeud->etat.terminal()) {
            expansion(noeud);
            if (!noeud->enfants.empty())
                noeud = noeud->enfants[rand() % noeud->enfants.size()];
        }
        double resultat = simulation(noeud->etat);
        retropropagation(noeud, resultat);
    }

    // Trouver le meilleur nœud (le plus visité)
    auto it = std::max_element(racine->enfants.begin(), racine->enfants.end(),
        [](NoeudMCTS* a, NoeudMCTS* b) { return a->visites < b->visites; });

    // Vérifier que l'itérateur est valide
    if (it != racine->enfants.end() && *it) {
        return (*it)->dernierCoup;  // Retourner le coup du meilleur nœud
    } else {
        return -1;  // Valeur par défaut si aucun coup n'est disponible
    }
}

NoeudMCTS* construireArbreMCTS(Jeu& etat, int iterations) {
    NoeudMCTS* racine = new NoeudMCTS(etat);  // Créer le nœud racine

    for (int i = 0; i < iterations; i++) {
        NoeudMCTS* noeud = selectionner(racine);  // Sélection d'un nœud selon UCT
        if (!noeud->etat.terminal()) {
            expansion(noeud);  // Expansion de nouveaux nœuds
            if (!noeud->enfants.empty())
                noeud = noeud->enfants[rand() % noeud->enfants.size()];
        }
        double resultat = simulation(noeud->etat);  // Simulation d’une partie aléatoire
        retropropagation(noeud, resultat);  // Mise à jour des valeurs des nœuds
    }

    return racine;
}

void sauvegarderArbre(NoeudMCTS* racine, const std::string& fichier) {
    std::ofstream out(fichier);
    if (!out) {
        std::cerr << "Erreur d'ouverture du fichier !" << std::endl;
        return;
    }

    std::queue<NoeudMCTS*> file;
    std::unordered_map<NoeudMCTS*, int> ids;
    ids[racine] = 0;
    file.push(racine);
    int idCourant = 1;

    while (!file.empty()) {
        NoeudMCTS* noeud = file.front();
        file.pop();

        int parentId = (noeud->parent) ? ids[noeud->parent] : -1;

        out << ids[noeud] << " " << parentId << " " << noeud->dernierCoup
            << " " << noeud->visites << " " << noeud->totalReward <<"\n";//<<"=====" <<noeud->totalReward << "/" <<noeud->visites<<  std::endl;

        for (NoeudMCTS* enfant : noeud->enfants) {
            ids[enfant] = idCourant++;
            file.push(enfant);
        }
    }
    out.close();
}
NoeudMCTS* chargerArbre(const std::string& fichier) {
    std::ifstream in(fichier);
    if (!in) {
        std::cerr << "Erreur d'ouverture du fichier !" << std::endl;
        return nullptr;
    }

    std::unordered_map<int, NoeudMCTS*> noeuds;
    int id, parentId, coup, visites;
    double totalReward;

    NoeudMCTS* racine = nullptr;
    
    while (in >> id >> parentId >> coup >> visites >> totalReward) {
        NoeudMCTS* noeud = new NoeudMCTS(Jeu(), nullptr, coup);
        noeud->visites = visites;
        noeud->totalReward = totalReward;
        noeuds[id] = noeud;

        if (parentId == -1) {
            racine = noeud;
        } else {
            noeud->parent = noeuds[parentId];
            noeuds[parentId]->enfants.push_back(noeud);
        }
    }

    in.close();
    return racine;
}
