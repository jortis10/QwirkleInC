/**
* \file affichage_plateau.c
*
* \brief Fichier contenant le code nécessaire à l'affichage console du plateau de jeu
*
* \author DA LAGE Alexis
* \version 1.0
* \date 18/02/2020
*
* Dans ce fichier ce trouvent le code des fonctions basiques servant à afficher le plateau de jeu en console
*/

#include <stdio.h>
#include <stdlib.h>
#include "affichage_plateau.h"
#include "../Modele/plateau.h"

/**
* \fn void clear_console()
* \brief Effacer le contenu de la console
*
* La fonction permet de supprimer le contenu de la console
*
*/


void clear_console()
{
    system("clear");
}


/**
* \fn void affiche_tuile(Tuile t)
* \brief Affichage d'une tuile en console
*
* La fonction permet d'afficher la tuile sur la console en suivant le formatage suivant:
* [A,B,C,D,E,F]=[CERCLE,CROIX,LOSANGE,CARRE,ETOILE,TREFLE]
* [1,2,3,4,5,6]=[ROUGE,ORANGE,JAUNE,VERT,BLEU,VIOLET]
* La fonction affichera "  " si t est le pointeur NULL ou si l'attribut zone de tuile est different de plateau
* La fonction affichera '?' pour un attribut indéfini
* \param[in] t la tuile que l'on souhaite afficher en console
* \return le retour se fera en console sous la forme C2 pour une tuile de forme LOSANGE et de couleur ORANGE
*/

void affiche_tuile(Tuile* t)
{
    if(t==NULL)
    {
        printf("  ");
        return ;
    }

    if(t->forme <6 && t->forme >=0)
    {
        printf("%c",(char)('A'+t->forme));
    }
    else
        printf("?");
    if(t->couleur<6 && t->couleur >=0)
        printf("%i",t->couleur+1);
    else
        printf("?");

}

/**
* \fn void affiche_plateau_vide(int x, int y)
* \brief Affichage d'un plateau vide
*
* La fonction permet d'afficher le plateau vide de taille x * y
*
* \param[in] x et y
*/

void affiche_plateau_vide(int x, int y)
{
    if(x>TAILLEMAX||y>TAILLEMAX)
    {
        printf("Impossible de charger un plateau de taille superieure a TAILLEMAX = %i\n",TAILLEMAX);
        return;
    }
    if(x<0||y<0)
    {
        printf("Impossible de charger un plateau de ayant de largeur et/ou longueur négative\n");
        return;
    }


    for(int i=0; i<y; i++)
    {
        printf("-  ");

        for(int j=0; j<x; j++)
        {
            printf("-  ");
        }
        printf("\n");
    }

}

/**
* \fn void affiche_plateau(Plateau *p)
* \brief Affichage du plateau
*
* La fonction permet d'afficher le plateau avec les tuiles à leurs emplacements
*
* \param[in] Pointeur de plateau
*/

void affiche_plateau(Plateau *p)
{
printf("     ");
for(int i=p->xmin-5; i<=p->xmax+4; i++){
    if(i<200&&i>0)
        printf(" \033[36m%3d\033[0m",i+1);
}
printf("\n");
    for(int y=p->ymin-5; y<p->ymax+5; y++)
    {
    if(y<200&&y>0)
    printf(" \033[36m%3d\033[0m ",y+1);
        for(int x=p->xmin-5; x<=p->xmax+5; x++)
        {
        if(x<200&&x>0){
            printf("- ");
            affiche_tuile(p->tuiles[x][y]);
            }
        }
        printf("\n");
    }
}


void affiche_main(Joueur *j)
{
    printf("%s votre main est :\n",j->nom);
    int i;
    for(i=0;i<NBTUILESMAX;i++)
    {
        printf(" \033[35m n°%d\033[0m ",(i+1));
        affiche_tuile(j->tuilesJoueur[i]);
        printf(" ");
    }
    printf("\n");
}

void affiche_points(Joueur *j)
{
    printf(" Vous avez %d points !\n",j->points);
}
