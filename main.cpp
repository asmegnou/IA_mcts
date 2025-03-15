
#include <iostream>
#include <mutex>
#include "arbitre.h"

#define NB_PARTIES 100
using namespace std;

int main()
{
    Jeu jeu ;
    Joueur_MCTS j("assia", true);
    j.entrainer(jeu);

    ///initialise la graine du générateur aléatoire
    std::srand(std::time(nullptr));


    // création de l'Arbitre (graine , joueur 1, joueur 2 , nombre de parties)
    Arbitre a (player::BRUTAL, player::MCTS, NB_PARTIES);
    // commence le challenge
    a.challenge();

    
    
    return 0;
}
