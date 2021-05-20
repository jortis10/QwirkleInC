/**
* \file regle.h
*
* \brief Fichier contenant le code nécessaire à la gestion des règles et au comptage des points
*
* \author VIAUD Léa et SOW Aicha
* \version 1.0
* \date 16/03/2020
*
*/

#ifndef REGLE_H
#define REGLE_H
#include "partie.h"
#include "joueur.h"
#include "plateau.h"
#include "tuile.h"
#include "../Controleur/respectRegles.h"

typedef enum {HAUT,BAS,GAUCHE,DROITE,SELF} Direction; /*!< Direction par rapport à une tuile de référence, SELF correspondant à la tuile de référence elle-même */
typedef enum {COULEUR,FORME,POSITION,FORMEetCOULEUR,niFORMEniCOULEUR,NOERROR,ALONE} Erreur; /*!< Erreur référencées selon leur type */



Erreur isColorFormeCorrect(Partie *p,Tuile *tj);
int critereCouleurForme(Partie *p,Direction d,Tuile *tj);
int respectcriterePose(Partie *p,Tuile *tj,Tuile *td,Direction d);
int dejaPosee(Partie *p,Tuile *tj,Direction d);

int hasvoisinTuile(Partie *p,int x,int y);
Tuile *getTuileplateau(Partie *p,Direction d,int x,int y);

Direction nextDir(int i);

int compareCouleur(Tuile *t1, Tuile *t2);
int compareForme(Tuile *t1, Tuile *t2);



#endif //REGLE_H
