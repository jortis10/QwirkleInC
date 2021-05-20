/**
* \file affichage_plateau.c
*
* \brief Fichier contenant le code nécessaire à l'affichage console du plateau de jeu
*
* \author DA LAGE Alexis
* \version 1.0
* \date 18/02/2020
*
* Dans ce fichier ce trouvent les prototypes des fonctions basiques servant à afficher le plateau de jeu en console
*/

#ifndef AFFICHAGE_CONSOLE_H
#define AFFICHAGE_CONSOLE_H
#include "../Modele/tuile.h"
#include "../Modele/plateau.h"
#include "../Modele/joueur.h"

void clear_console();  /*!< Effacage de la fenètre console */
void affiche_plateau_vide(int x, int y); /*!< Affichage d'un plateau vide de longueur x et de largeur y */
void affiche_main(Joueur *j); /*! Affichage de la main du joueur */
void affiche_points(Joueur *j); /*!affichage du nombre de point d'un joueur */


/*!< Fonctions pas encore codées*/

void affiche_tuile(Tuile *t); /*!< Affichage d'une tuile en console, affiche "  " si t est le pointeur NULL */
void affiche_plateau(Plateau *p); /*!< Affichage du plateau de jeu en console */
#endif
