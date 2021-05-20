/**
* \file partie.h
*
* \brief Fichier contenant le code nécessaire à la modélisation d'une partie
*
* \author DA LAGE Alexis
* \version 1.0
* \date 17/02/2020
*
* Dans ce fichier ce trouve la définition de la constante NBTUILESSACMAX ,la déclaration de la structure Partie ainsi que les prototypes des fonctions basiques servant à manipuler l'instance Partie
*/

#ifndef PARTIE_H
#define PARTIE_H
#include <time.h>
#include "joueur.h"
#include "tuile.h"
#include "plateau.h"

#define NBTUILESSACMAX 108      /*!< Nombre de tuiles maximum dans le sac*/
#define NBJOUEURSMAX 4          /*!< Nombre de joueurs maximum*/


/**
* \struct Partie
*
* \brief Objet modélisant la partie de jeu Qwirkle
*
* L'objet Partie stocke les informations relatives à la partie de jeu tel que :
* le nombre de joueurs NbJoueurs,
* l'index du joueurCourant,
* le tableau de Joueur,
* le nombre de tuiles restantes dans le sac nbTuilesSac,
* le sac contenant les pointeurs sur les Tuiles,
* le lot de Tuile contante les Tuiles crées en statique de manière ordonée,
* le plateau sur lequel les joueurs pose leurs tuiles
*
*/

typedef struct
{
    int NbJoueurs;                      /*!<nombre de joueurs participant à la partie*/

    int joueurCourant;                  /*!< entier correspondant au joueur devant jouer a un moment t donné */

    Joueur *joueurs[NBJOUEURSMAX] ;     /*!< tableau de joueurs de taille NBJOUEURSMAX*/

    int nbTuilesSac;                    /*!< nombre de tuiles restantes dans le sac de pioche*/

    Tuile* sac[NBTUILESSACMAX];         /*!< tableau de tuiles avec les 108 différentes tuiles triées aléatoirement*/
    Tuile lotTuiles[NBTUILESSACMAX];    /*!< Tableau de tuiles physiques*/

    Plateau* plateau ;                  /*!< pointeur vers un tableau*/
} Partie;

/*!prototypes des fonctions liées à la gestion du Sac*/
void mettreTuilesdanslot(Partie *p);
void genererTuileSac(Partie *p);
void melangerSac(Partie *p,int i);
int verifDoublonsSac(Partie *p);
Tuile *piocherSac(Partie *p);
void piocherTuiles(Partie *p);
void retournerTuileSac(Partie *p, Tuile *tab[6]);
void retournerTuileTab(Partie *p, int index_tuile,Tuile *tab[6]);
void action_piocher(Partie *p, int tabtuiles[6]);

/*!prototypes des fonctions liées à la gestion de la Partie*/
Partie * CommencerPartie(int nbjoueurs);
void distibutionInit(Partie *p);
Partie * creationPartie(int nbjoueurs);
void joueurSuivant(Partie *p);
Joueur * getJoueurCourant(Partie * p);
void placerTuileMilieu(Partie*p);
void freePartie(Partie *p);

#endif //PARTIE_H
