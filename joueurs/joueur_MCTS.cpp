#include "joueur_MCTS.h"
#include <algorithm>


Joueur_MCTS::Joueur_MCTS(std::string nom, bool joueur) :  Joueur(nom, joueur)
  {
}
void Joueur_MCTS::init_partie(){
    std::cout << "la partie a commencé" << std::endl;
}

char Joueur_MCTS::nom_abbrege() const{
    return 'm';
}

void Joueur_MCTS::initialisation() {
    std::cout << "Initialisation de l'arbre MCTS" << std::endl;
   //delete arbre;
    //
    //arbre = chargerArbre("mcts_arbre.txt");
}


void Joueur_MCTS::recherche_coup(Jeu jeu, int &coup) {
     // Si le jeu est terminé, on ne fait rien
     if (jeu.terminal()) {
        std::cout << "Le jeu est terminé." << std::endl;
        return;
    }

    // Étape 1 : Calculer l'état résultant après le coup de l'adversaire
    int coup_pred = coup;
    int etat_pred = _etat *10 +coup;


    // Étape 2 : Naviguer dans l'arbre MCTS pour atteindre le nœud correspondant à 
    NoeudMCTS* noeud = chargerArbre("mcts_arbre.txt"); // Commencer à la racine de l'arbre
    if (!noeud) {
        std::cerr << "Erreur : impossible de charger l'arbre MCTS." << std::endl;
        return;
    }

    bool etat_trouve = false;

    int nb=0;
    while (!noeud->enfants.empty() && nb <100) {
        auto it = std::find_if(noeud->enfants.begin(), noeud->enfants.end(),
            [&](NoeudMCTS* enfant) {
                return enfant->etat_int == etat_pred; // Supposons que chaque nœud a un attribut `etat`
            });
            nb++;
        if (it != noeud->enfants.end()) {
            noeud = *it; // Aller à l'enfant correspondant
            etat_trouve = true;
        } else {
            break; // L'état n'est pas dans l'arbre
        }
    }

    // Si l'état n'est pas trouvé dans l'arbre, on initialise un nouveau nœud
    if (!etat_trouve) {
        noeud = new NoeudMCTS(jeu, noeud); // Créer un nouveau nœud pour cet état
        noeud->etat_int = etat_pred; // Assigner l'état au nœud
        noeud->parent->enfants.push_back(noeud); // Ajouter ce nœud comme enfant de son parent
    }
    float c = sqrt(2);
    // Étape 3 : Choisir le meilleur coup parmi les enfants de ce nœud
    if (!noeud->enfants.empty()) {
        // Trouver l'enfant avec la meilleure récompense moyenne
        auto meilleur_enfant_it = std::max_element(noeud->enfants.begin(), noeud->enfants.end(),
            [&c](NoeudMCTS* a, NoeudMCTS* b) {
                return (a->totalReward / (a->visites + 1e-6) + c *sqrt(2 *log(a->visites+1) / a->visites+  1e-6))  < (b->totalReward / (b->visites + 1e-6) + c *sqrt(2 *log(b->visites+1) / b->visites+  1e-6));
            });

        // Récupérer le coup associé au meilleur enfant
        coup = (*meilleur_enfant_it)->dernierCoup; // Supposons que chaque nœud stocke le coup joué pour y arriver
        std::cout << "Coup MCTS choisi : " << coup << std::endl;
    } else {
        // Si aucun enfant n'est disponible, jouer un coup aléatoire licite
        coup = rand() % jeu.nb_coups() + 1;
        while (!jeu.coup_licite(coup)) {
            coup = rand() % jeu.nb_coups() + 1;
        }
        std::cout << "Coup aléatoire choisi : " << coup << std::endl;
    } 
    _etat= coup_pred*10 +coup;
}



void Joueur_MCTS::entrainer(Jeu jeu){
    NoeudMCTS* arbre = construireArbreMCTS(jeu, 1000000);  // Construire l'arbre avec 10 000 simulations
    sauvegarderArbre(arbre, "mcts_arbre.txt");
}


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
        //maj de etat 
        int e =noeud->etat_int*10+coup;
        nouvelEtat.joue(coup);
        noeud->enfants.push_back(new NoeudMCTS(nouvelEtat, noeud, coup, e));
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
/*
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
}*/

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
            << " " << noeud->visites << " " << noeud->totalReward <<" "<<noeud->etat_int<<"\n";//<<"=====" <<noeud->totalReward << "/" <<noeud->visites<<  std::endl;

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
    int id, parentId, coup, visites , etat_int;
    double totalReward;

    NoeudMCTS* racine = nullptr;
    
    while (in >> id >> parentId >> coup >> visites >> totalReward>>etat_int) {
        NoeudMCTS* noeud = new NoeudMCTS(Jeu(), nullptr, coup, etat_int );
        noeud->visites = visites;
        noeud->totalReward = totalReward;
        noeuds[id] = noeud;
        noeud->etat_int=etat_int;

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
