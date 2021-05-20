/**
* \file plateau.c
*
* \brief Fichier contenant le code nécessaire à la modélisation du plateau de jeu
*
* \author DA LAGE Alexis
* \version 1.0
* \date 21/02/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions précedemment définies dans plateau.h
*/

#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

/**
* \fn Plateau * initPlateau()
* \brief initialisation plateau
*
* La fonction permet d'initialiser un plateau en mettant toutes ces cases à NULL et mettant ses bornes à (100;100) soit le centre du plateau
*
* \param[out] Plateau *p : un pointeur sur un plateau initialisé
*/
Plateau * initPlateau()
{
    Plateau *p=(Plateau *)malloc(sizeof(Plateau));
    if (p == NULL)
    {
        return NULL;
    }

    for(int i = 0; i<TAILLEMAX; i++)
    {
        for(int j=0; j<TAILLEMAX; j++)
        {
            p->tuiles[i][j]=NULL;
        }
    }

    p->xmax=100;
    p->xmin=100;
    p->ymax=100;
    p->ymin=100;
    return p;
}

/**
* \fn void freePlateau(Plateau *p)
* \brief liberation mémoire plateau
*
* La fonction permet de liberer la mémoire allouée a un plateau passé en paramètre via un pointeur p,
*
* \param[in] Plateau *p : pointeur sur le plateau à free
*/
void freePlateau(Plateau *p)
{
    if(p!=NULL)
    {
        free(p);
    }

}

/**
* \fn void modifierZonedeJeu(Plateau *p)
* \brief modifie la taille de la zone de jeu soit les bornes xmin,ymin,xmax et ymax du plateau
* la fonction parcoure le plateau et si une tuile est non NULL et que sa position est une nouvelle limite pour xmax/xmin ou ymax/ymin,
* elle modifie la valeur des bornes du plateau de façon à avoir toute la zone où des tuiles sont jouées
*
* \param[in] Plateau * p : pointeur sur le plateau
*/
void modifieZonedeJeu(Plateau * p)
{

    if(p==NULL)
        return;

    for(int i=0; i< TAILLEMAX; i++)
    {
        for(int j=0; j< TAILLEMAX; j++)
        {
            if(p->tuiles[i][j]!=NULL)
            {
                if(p->tuiles[i][j]->x > p->xmax)
                    p->xmax=p->tuiles[i][j]->x;
                if((p->tuiles[i][j]->x < p->xmin) && (p->tuiles[i][j]->x >= 0))
                    p->xmin=p->tuiles[i][j]->x;
                if(p->tuiles[i][j]->y > p->ymax)
                    p->ymax=p->tuiles[i][j]->y;
                if((p->tuiles[i][j]->y < p->ymin) && (p->tuiles[i][j]->y >= 0))
                    p->ymin=p->tuiles[i][j]->y;
            }
        }
    }
}

/**
* \fn void poserTuile(Plateau* p,Tuile* t,int x, int y)
* \brief pose une tuile du joueur aux coordonnées (x,y) du plateau de jeu
* .
* Elle met à jour les paramètre de la tuile avec la position x et y correspondant,
* puis elle met cette tuile sur le plateau à la case [x-1][y-1].
*
* \param[in] Plateau *p : le plateau sur lequel on souhaite posé la tuile t
* \param[in] int x position en abcisse où l'on souhaite poser la tuile t
* \param[in] int y position en ordonnée où l'on souhaite poser la tuile t
* \param[in] Tuile* t : la tuile qui doit être posée
*/
void poserTuile(Plateau* p,Tuile* t,int x, int y)
{

    if(t!=NULL && p!=NULL && x>0 && y>0 && x<=TAILLEMAX && y<=TAILLEMAX)
    {
        t->x = x;
        t->y = y;
        p->tuiles[x-1][y-1] = t;
    }
}

/**
* \fn int iscaseEmpty(Plateau * p,int x,int y)
* \brief retourne 1 si la case du plateau aux coordonnées passées en paramètre est vide
*
* \param[in] Plateau *
* \param[in] int x
* \param[in] int y
*
* \param[out] int : 1 si la case est vide et 0 si la case possède une tuile
*/
int iscaseEmpty(Plateau * p,int x,int y)
{
    if(p!=NULL && x>0 && y>0 && x<=TAILLEMAX && y<=TAILLEMAX)
    {
        return  p->tuiles[x][y]== NULL;
    }
    else
        return 0;
}

