/*!
* \file gestionSac.c
* \brief Fichier contenant les fonctions pour la gestion du Sac de Tuile
*
* \author Léa VIAUD et SOW Aicha
* \version 2.0
* \date 07/03/2020
*
* Dans ce fichier ce trouve les fonctions nécessaires à la manipulation du Sac de Tuile
*/

#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"
#include "tuile.h"
#include "partie.h"

/*!
* \fn void mettreTuilesdanslot(Partie *p)
* \brief  Met les tuiles crées avec la fonction createTuile dans le tableau statique lotTuiles de la partie
* Génération dans l'ordre de toutes les Tuiles
* \param[in]  p , pointeur sur une partie
*/
void mettreTuilesdanslot(Partie *p)
{

    int j=0,k=0;  /*! k représente les formes et j la couleur */
    int i=0;
    for(j=0; j<6; j++)
    {
        for(k=0; k<6; k++)
        {
            p->lotTuiles[i]=createTuile(j,k);
            p->lotTuiles[i+1]=createTuile(j,k);
            p->lotTuiles[i+2]=createTuile(j,k);
            i=i+3;
        }
    }

}

/*!
* \fn void genererTuileSac(Partie *p)
* \brief  génère le sac de Tuile pour le début d'une partie
* la fonction prend les tuiles statiques du lotTuiles de la partie pour mettre leur adresse dans le sac de Tuile en incrémentant le nombre de Tuile du sac à chaque tuile ajoutée
*
* \param[in]  p , pointeur sur une partie
*/
void genererTuileSac(Partie *p)
{
    int i=0;
    for(i=0; i<NBTUILESSACMAX; i++)
    {

        p->sac[i]=&(p->lotTuiles[i]);
        p->nbTuilesSac++;
    }
}


/*!
* \fn void melangerSac(Partie *p)
* \brief  mélange le sac de Tuile pour le début d'une partie
* Mélange de manière aléatoire les pièces initialement ordonnées à la génération du sac
* si k=0 : mélange aléatoirement
* si k!=0 : mélange avec la même seed (srand(1))
*
* \param[in] p , pointeur sur une partie
* \param[in] k , int
*
*/
void melangerSac(Partie *p,int k)
{
    if(k==0)
    {
        srand(time(NULL));
    }else
    {
        srand(1);
    }

    int i=0,j=0,n=p->nbTuilesSac;
    Tuile *temp=NULL;

    for(i=0; i<n-1; i++)
    {
        j=i+rand()/(RAND_MAX /(n-i)+1);
        temp= p->sac[j];
        p->sac[j]= p->sac[i];
        p->sac[i]=temp;
    }
}

/*!
* \fn int verifDoublonsSac(Partie *p)
* \brief  Fonction verifiant qu'il n'y a pas de doublons dans le sac apres le melange de ce dernier
*
* \param[in] sac
* \param[out] retourne 1 si pas de doublons(pas d'erreur de recopie), retourne 0 si doublon(s).
*/
int verifDoublonsSac(Partie *p)
{
    int doublons=0;
    int tabverifsac[6][6]= {{0},{0}};
    int i=0,c=0,f=0;
    for(i=0; i<NBTUILESSACMAX; i++)
    {
        for(c=0; c<6; c++)
        {
            if(p->sac[i]->couleur==c)
            {
                for(f=0; f<6; f++)
                {
                    if(p->sac[i]->forme==f)
                    {
                        tabverifsac[c][f]+=1;
                        f=6;
                        if(tabverifsac[c][f]>3)
                        {
                            doublons=1;
                        }
                    }
                }
            }
            c=6;
        }
    }
    return (doublons==0);

}


/**
* \fn  Tuile * piocherSac(Partie *p)
* \brief permet la piocher la dernière tuile du sac, décrémente le nombre de tuile du sac et met à jour le sac
*
* \param[in] p , pointeur sur une partie
* \param[out] Tuile : la tuile du sac qui vient d'être piochée
*/
Tuile *piocherSac(Partie *p)
{
    if(p==NULL)
    {
        fprintf(stderr,"Partie nulle mise en paramètres de la fonction piocherSac");
        return  NULL;
    }
    if(p->nbTuilesSac<=0)
    {
        fprintf(stderr,"Sac vide on ne peut plus piocher dans sac");
        return NULL;
    }
    int nbsac=p->nbTuilesSac;
    p->nbTuilesSac--;

    Tuile *pioche = p->sac[nbsac-1];

    p->sac[nbsac-1]=NULL;
    return pioche;
}


/**
* \fn void piocherTuiles(Partie *p)
* \brief permet à un joueur de piocher des tuiles du sac
*
* La fonction permet au joueur courant de piocher le nombre de tuiles manquantes pour avoir 6 tuiles dans sa main

* \param[in] p , pointeur sur une partie
*/
void piocherTuiles(Partie *p)
{
    int i=0;
    for (i=0; i<NBTUILESMAX; i++)
    {
        if(getJoueurCourant(p)->tuilesJoueur[i]==NULL)
        {
            if(p->nbTuilesSac!=0)
                getJoueurCourant(p)->tuilesJoueur[i]=piocherSac(p);
        }
    }
}

/**
* \fn void retournerTuileSac(Partie *p, Tuile * tab[6])
* \brief permet de retourner dans le sac les tuiles que le joueur voulait échanger et qui sont stockées dans un tableau de tuile
*
* \param[in] p , pointeur sur une partie
* \param[in] tab, tableau de tuile que le joueur veut échanger
*/
void retournerTuileSac(Partie *p, Tuile* tab[6])
{
    int i=0;
    for(i=0;i<6;i++)
    {
        if(tab[i]!=NULL)
        {
            p->nbTuilesSac++;
            int nbSac =p->nbTuilesSac;
            p->sac[nbSac-1]=tab[i];
        }
    }
}

/**
* \fn void retournerTuileTab(Partie *p, Tuile * tab[6])
* \brief permet au joueur courant de mettre les tuiles qu'il veut échanger dans un tableau de tuile passé en paramètre
*
* La fonction permet au joueur courant de échanger une de ces tuiles (index_tuile). Le joueur a donc une tuile en moins après cette fonction.
* Cette Tuile est stockée dans le tableau de tuile passé en paramètre
* \param[in] p , pointeur sur une partie
* \param[in] index_tuile , int du numéro de la tuile que le joueur veut échanger
* \param[in] tab, tableau de tuile que le joueur veut échanger
*/
void retournerTuileTab(Partie *p, int index_tuile,Tuile * tab[6])
{
    Joueur * j=getJoueurCourant(p);
    int nbSac =p->nbTuilesSac;
    nbSac++;
    tab[index_tuile-1]=j->tuilesJoueur[index_tuile-1];
    j->tuilesJoueur[index_tuile-1]=NULL;

}

/**
* \fn void action_piocher(Partie *p, int tabtuiles[6])
* \brief permet au joueur courant d'échanger des tuiles de sa main avec des tuiles du sac
*
*   Le joueur met les tuiles qu'il veut changer dans un tableau de tuile, il pioche des tuiles dans le sac pour compléter sa main et il retourne dans le sac les tuiles du tableau qu'il voulait échanger
* \param[in] p , pointeur sur une partie
* \param[in] tab, tableau de tuile que le joueur veut échanger
*/
void action_piocher(Partie *p, int tabtuiles[6])
{
    int i;
    Tuile * tab[6]={NULL};
    for(i=0; i<6; i++)
    {
        if(tabtuiles[i]!=0)
        {
            retournerTuileTab(p,i+1,tab);
        }
    }
    piocherTuiles(p);
    retournerTuileSac(p,tab);
    melangerSac(p,0);
}
