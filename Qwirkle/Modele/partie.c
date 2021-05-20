/**
* \file partie.c
*
* \brief Fichier contenant le code nécessaire à la modélisation d'une partie
*
* \author DA LAGE Alexis
* \version 1.0
* \date 03/03/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions decrivant la partie
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "joueur.h"
#include "partie.h"


/*!
* \fn Partie *CommencerPartie(int nbjoueurs)
* \brief  Commence une partie avec un nombre de joueurs nbjoueurs , leur nom sera attribué automatiquement : Joueur i , i compris entre 1 à nbjoueurs
* Un sac est generé avec les tuiles mélangées
* le plateau est également initialisé, avec une tuile posée à son centre,
* les tuiles sont également distribuées dans la main des joueurs
*
* \param[in] int nbjoueurs
* \param[out] Partie * p
*/
Partie *CommencerPartie(int nbjoueurs)
{
    Partie *p=creationPartie(nbjoueurs);

    char nomdujoueur[10] ="Joueur ";
    for(int i=0; i<nbjoueurs; i++)
    {
        nomdujoueur[7]=49+i;

        p->joueurs[i]=creationJoueur(nomdujoueur);
    }
    mettreTuilesdanslot(p);
    genererTuileSac(p);
    melangerSac(p,0);
    distibutionInit(p);
    p->plateau=initPlateau();
    placerTuileMilieu(p);

    return p;
}


/*!
* \fn Partie *  creationPartie(int nbjoueurs)
*
* \brief  crée une partie dynamiquement avec un nombre de joueurs nbjoueurs, dont les autres éléments seront mis à zéro ou NULL
*
* \param[in] int nbjoueurs
*
* \param[out] Partie * p
*/
Partie *  creationPartie(int nbjoueurs)
{
    Partie *p =(Partie*) malloc(sizeof(Partie));
    if(p==NULL)
        return NULL;
    p->NbJoueurs=nbjoueurs;
    for(int i=0;i<nbjoueurs;i++)
    p->joueurs[i]=NULL;
    p->joueurCourant=0;
    p->nbTuilesSac=0;
    p->plateau=NULL;


    return p;
}


/**
* \fn  void  distibutionInit(Partie *p)
* \brief permet la distribution de 6 tuiles (tuiles initiales) aux joueurs en début de partie
*
* \param[in] p , pointeur sur une partie
*/
void distibutionInit(Partie *p)
{
    for( int i=0; i<p->NbJoueurs; i++)
    {
        piocherTuiles(p);
        p->joueurCourant++;
    }
    p->joueurCourant=0;
}



/**
* \fn void joueurSuivant(Partie *p)
* \brief permet à de passer l'attribut joueurCourant de la partie passée en paramètre à l'index du joueur suivant
* joueurCourant est de nouveau mis à 0 lorsque l'index devient égale au nombre de joueur de la partie
*
* \param[in] p , pointeur sur une partie
*/
void joueurSuivant(Partie *p)
{
    if (p==NULL)
    {
        printf("Erreur partie mal initialisée\n");
        return;
    }
    p->joueurCourant++;
    if(p->joueurCourant==p->NbJoueurs)
    {
        p->joueurCourant=0;
    }
}

/**
* \fn Joueur * getJoueurCourant(Partie * p)
* \brief Permet d'obtenir le pointeur vers le joueur courant de la partie passée en paramètre
*
* \param[in] Partie * p
* \param[out] Joueur * j
*/
Joueur * getJoueurCourant(Partie * p)
{
    if (p==NULL)
    {
        printf("Erreur partie mal initialisée\n");
        return NULL;
    }
    if(p->joueurCourant>=p->NbJoueurs)
    {
        printf("Probleme car le joueur courant n'existe pas\n");
        return NULL;
    }
    return p->joueurs[p->joueurCourant];
}


/**
* \fn void placerTuileMilieu(Partie* p)
* \brief Permet de placer une tuile au milieu du plateau
* la fonction pioche une tuile dans le sac pour la positionner sur le plateau avec les coordonnées (100;100) soit le centre du plateau
*
* \param[in] Partie * p
*/
void placerTuileMilieu(Partie*p)
{
    Plateau *plateau=p->plateau;
    plateau->xmin=99;
    plateau->ymin=99;
    Tuile *tuilepiochee=piocherSac(p);
    if(tuilepiochee==NULL)
        return;
    else
    {
        plateau->tuiles[99][99]=tuilepiochee;
        plateau->tuiles[99][99]->x=100;
        plateau->tuiles[99][99]->y=100;
    }
}

/**
* \fn void freePartie(Partie *p)
* \brief liberation mémoire d'une partie
*_
* La fonction permet de liberer la mémoire allouée a une partie passée en paramètre, elle free également le plateau, les joueurs et le sac
*
* \return void
*/
void freePartie(Partie *p)
{
    if(p!=NULL)
    {
        freePlateau(p->plateau);
        int nbjoueur,i;
        nbjoueur=p->NbJoueurs;
        for(i=0; i<nbjoueur; i++)
        {
            freeJoueur(p->joueurs[i]);
        }
        free(p);
    }
}
