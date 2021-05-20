/**
* \file tuile.h
*
* \brief Fichier contenant le code nécessaire à la modélisation d'une tuile
*
* \author DA LAGE Alexis
* \version 1.0
* \date 17/02/2020
*
* Dans ce fichier ce trouve les declarations des types Couleur, Zone, Forme, la déclaration de la structure Tuile ainsi que les prototypes des fonctions basiques servant à manipuler les instances de Tuile
*/

#ifndef TUILE_H
#define TUILE_H

/**
* \enum Couleur
*
* \brief Objet decrivant les differentes couleurs que peut prendre une tuile
*
* Chaque tuile à une couleur, ROUGE = 0 ,ORANGE = 1 ,JAUNE = 2 ,VERT= 3 ,BLEU = 4 ,VIOLET =5
*/

typedef enum {ROUGE=0,ORANGE=1,JAUNE=2,VERT=3,BLEU=4,VIOLET=5} Couleur;

/**
* \enum Forme
*
* \brief Objet decrivant les differentes formes que peut prendre une tuile
*
* Chaque tuile à une forme, CERCLE = 0 ,CROIX = 1 ,LOSANGE = 2 ,CARRE = 3 ,ETOILE = 4 ,TREFLE = 5
*/

typedef enum {CERCLE=0,CROIX=1,LOSANGE=2,CARRE=3,ETOILE=4,TREFLE=5} Forme;


/**
* \struct Tuile
*
* \brief Objet modélisant la tuile du jeu Qwirkle
*
* L'objet tuile possede plusieurs attributs telle que :
* sa couleur,
* sa forme,
* sa position en x et y sur le plateau de jeu,
* La position d'une tuile est initialisé à (-1;-1) lorsqu'elle n'est pas sur le plateau
*/

typedef struct Tuile
{
    Couleur couleur;                                    /*!< couleur de la tuile*/
    Forme forme;                                        /*!< forme de la tuile*/
    int x;                                              /*!< position x de la tuile sur le plateau*/
    int y;                                              /*!< position y de la tuile sur le plateau*/
} Tuile;

Tuile createTuile(Couleur c, Forme f);
void freeTuile(Tuile* t);
void initTuile(Tuile *);

void changePositionTuile(Tuile *t,int x, int y);

Couleur getCouleur(Tuile *t);
Forme getForme(Tuile *t);


#endif // TUILE_H
