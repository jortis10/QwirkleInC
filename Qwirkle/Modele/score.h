/**
* \file score.h
*
* \brief Fichier contenant le code nécessaire au comptage des points
*
* \author VIAUD Léa
* \version 1.0
* \date 21/04/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions permettant de compter les points
*/


#ifndef SCORE_H
#define SCORE_H
#include "partie.h"
#include "regle.h"

void majPoints(Partie *p,int tabtuiles[6]);
void majPointsV0(Partie *p,int tabtuiles[6]);

int getPosX(Partie *p,int i);
int getPosY(Partie *p,int i);
int isDejaComptee(int dejaComptee[50][2],Tuile *t);
int appartient2lignes(Partie *p,int x, int y);
void supprTuileVirtuel(int tabtuiles[6],Partie *p);
void poseTuilevirtuel(int tabtuiles[6],Partie *p);


#endif
