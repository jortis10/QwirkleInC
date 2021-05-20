/**
* \file plateau.h
*
* \brief Fichier contenant le code nécessaire à la modélisation du plateau de jeu
*
* \author DA LAGE Alexis
* \version 1.0
* \date 17/02/2020
*
* Dans ce fichier ce trouve la définition de la constante TAILLEMAX ,la déclaration de la structure Plateau ainsi que les prototypes des fonctions basiques servant à manipuler l'instance Plateau
*/
#
#ifndef PLATEAU_H
#define PLATEAU_H


#define TAILLEMAX 200  /*!< Largeur maximale du plateau */

#include "tuile.h"

/**
* \struct Plateau
*
* \brief Objet modélisant le plateau de jeu Qwirkle
*
* L'objet Plateau contient les bornes du plateau où les tuiles sont jouées ainsi qu'un tableau 2 dimensions des tuiles déjà jouées sur ce plateau
*les bornes xmin,ymin,xmax et ymax ne sont utilisés que pour la V0 sur la console
*/
typedef struct
{
    int xmin;                               /*!< bornes xmin du plateau des tuiles jouées*/
    int ymin;                               /*!< bornes ymin du plateau des tuiles jouées*/
    int xmax;                               /*!< bornes xmax du plateau des tuiles jouées*/
    int ymax;                               /*!< bornes ymax du plateau des tuiles jouées*/
    Tuile* tuiles[TAILLEMAX][TAILLEMAX];    /*!< tableau de Tuile représentant le plateau de jeu*/
} Plateau;


Plateau * initPlateau();
void freePlateau(Plateau *p);


void poserTuile(Plateau* p,Tuile* t,int x, int y);
void modifieZonedeJeu(Plateau * p);
int iscaseEmpty(Plateau * p,int x,int y);
#endif // PLATEAU_H
