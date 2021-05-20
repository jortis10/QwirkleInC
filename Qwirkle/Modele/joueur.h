/**
* \file joueur.h
*
* \brief Fichier contenant le code nécessaire à la modélisation d'un joueur
*
* \author DA LAGE Alexis
* \version 1.0
* \date 17/02/2020
*
* Dans ce fichier ce trouve la définition de la constante NBTUILESMAX ,la déclaration de la structure Joueur ainsi que les prototypes des fonctions basiques servant à manipuler les instances de Joueur
*/

#include "tuile.h"

#ifndef JOUEUR_H
#define JOUEUR_H

#define NBTUILESMAX 6 /*!< Nombre de tuiles maximum dans la main du joueur*/

/**
* \struct Joueur
*
* \brief Objet modélisant le joueur jouant au jeu Qwirkle
*
* L'objet joueur permet de stocker :
* le nom du joueur,
* son nombre de points,
* le tableau des tuiles que possède ce joueur dans sa main (soit 6 Tuiles max)
*/
typedef struct
{
    char * nom;                             /*!<Nom du Joueur*/
    Tuile * tuilesJoueur[NBTUILESMAX];      /*!<Tableau des 6 tuiles possédées par le joueur*/
    int points;                             /*!<points accumulés par le joueur au fur et à mesure de la partie, initialisé à zéro*/
} Joueur;




Joueur * creationJoueur(char *n);
int initPoints(Joueur * j);
void ajouterPoints(int a,Joueur * j);
int getPoints(Joueur *j);
void freeJoueur(Joueur *j);

#endif // JOUEUR_H
