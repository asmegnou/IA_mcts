#pragma once
#include "joueur.h"
#include <vector>
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

    int etat_int=0;

    NoeudMCTS(Jeu etat, NoeudMCTS* parent = nullptr, int coup = -1, int e=0) 
        : etat(etat), parent(parent), dernierCoup(coup), etat_int(e){}
};

NoeudMCTS* selectionner(NoeudMCTS* racine);
void expansion(NoeudMCTS* noeud) ;
double simulation(Jeu etat) ;
void retropropagation(NoeudMCTS* noeud, double resultat);
int MCTS(Jeu etat, int iterations);
NoeudMCTS* construireArbreMCTS(Jeu& etat, int iterations);
void sauvegarderArbre(NoeudMCTS* racine, const std::string& fichier) ;
NoeudMCTS* chargerArbre(const std::string& fichier) ;



class Joueur_MCTS : public Joueur
{

private :
  unsigned int _etat;
   //NoeudMCTS * arbre;
  
public:
  Joueur_MCTS(std::string nom, bool joueur);

  void initialisation() override;

  void init_partie() override;

  char nom_abbrege() const override;

  void recherche_coup(Jeu, int & coup) override;

  void entrainer(Jeu) ;
};
