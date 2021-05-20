/**
* \file joueur.c
*
* \brief Fichier contenant le code nécessaire à la modélisation du joueur
*
* \author JENNY Thibaud
* \version 1.0
* \date 03/03/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions précedemment définies dans joueur.h
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "joueur.h"



/**
* \fn int getPoints(Joueur *j)
* \brief Retourne les points d'un joueur passé en paramètre de la fonction.
* Si le pointeur est NULL, retourne 0
*
* \param[in] Joueur * j : pointeur sur un joueur
* \param[out] int : nombre de points du joueur
*/
int getPoints(Joueur *j)
{
    if(j==NULL)
        return 0;
    else
        return j->points;
}

/**
* \fn int initPoints(Joueur *j)
* \brief initialisation des points joueur à 0
*
* La fonction permet d'initialiser les points d'un joueur en début de partie
*
* \param[in] Joueur * j
* \param[out] int : retourne 0 si tout s'est bien passé et -1 si l'initiatlisation n'a pas marché
*/
int initPoints(Joueur * j)
{
    if(j==NULL)

        return -1;
    else
    {
        j->points = 0;
        return 0;
    }

}

/**
* \fn void ajouterPoints(int a, Joueur *j)
* \brief ajoute des points à un joueur
*
* La fonction permet d'ajouter des points a un joueur passé en paramètre en cours de partie
*
* \param[in] int a : point à ajouter
* \param[in] Joueur *j : pointeur sur le joueur auquel on ajoute les points
*/
void ajouterPoints(int a,Joueur * j)
{
if(j!=NULL)
    j->points += a;
}

/**
* \fn int creationJoueur(char *n)
* \brief créer un joueur à partir de son nom
*
* La fonction permet de créer un joueur en début de partie à partir de son nom.
* retourne NULL si il y a eu un échec à la création du joueur
* les tuiles de sa main son initialisées à NULL et son nombre de points à 0;
*
* \param[in] char *n : nom du joueur
* \param[out] Joueur *j : pointeur vers le joueur créé
*/
Joueur * creationJoueur(char *n)
{
    int i=0;
    Joueur *j=(Joueur*) malloc(sizeof(Joueur));
    if(j==NULL)
    {
        printf("echec de la creation du joueur");
        return NULL;
    }
    j->nom=(char*)malloc(sizeof(char)*50);
    if(j->nom==NULL)
    {
        return NULL;
    }
    strcpy(j->nom,n);
    initPoints(j);
    for(i=0; i<NBTUILESMAX; i++)
    {
        j->tuilesJoueur[i]=NULL;
    }
    return j;
}

/**
* \fn void freeJoueur(Joueur *j)
* \brief liberation mémoire d'un joueur et de son nom
*
* La fonction permet de liberer la mémoire allouée a un joueur passé en paramètre via un pointeur j,
*  elle free également le nom du joueur
*
* \param[in] Joueur *j : joueur qui va être free
*/
void freeJoueur(Joueur *j)
{
    if(j!=NULL)
    {
        free(j->nom);
        free(j);
    }
}
