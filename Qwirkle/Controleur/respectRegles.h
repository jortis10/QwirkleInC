/**
* \file respectRegles.h
*
* \brief Fichier contenant le code nécessaire au respect des regles lorsque le joueur pose des tuiles
*
* \author VIAUD Léa
* \version 1.0
* \date 21/04/2020
*
* Dans ce fichier ce trouvent les prototypes des fonctions basiques vérifiant le respect des règles
*/

#ifndef RESPECTREGLES_H
#define RESPECTREGLES_H
#include "../Modele/tuile.h"
#include "../Modele/plateau.h"
#include "../Modele/partie.h"
#include "../Modele/regle.h"

int isTuileCorrect(Partie *p,int tabtuiles[6],int indextuilecourante);
int isTuileCorrect2(Partie *p,int tabtuiles[6]);
int isWordCorrect(Partie *p,int tabtuiles[6]);
int istabtuilesVide(int tabtuiles[6]);
int linkedtotherest(Partie *p,int tabtuiles[6]);
int stillawordXy(Partie *p,Tuile *tuilemin,int nbrtuiles,int xory);
int nbrtuilesposee(int tabtuiles[6]);

#endif

