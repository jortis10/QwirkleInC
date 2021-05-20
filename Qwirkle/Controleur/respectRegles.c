/**
* \file respectRegles.c
*
* \brief Fichier contenant le code nécessaire au respect des regles lorsque le joueur pose des tuiles
*
* \author SOW Aicha
* \version 2.0
* \date 27/04/2020
*
* Dans ce fichier se trouvent les prototypes des fonctions vérifiant le respect des règles
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "respectRegles.h"
#include "../Modele/score.h"

/*!
* int isTuileCorrect(Partie *p,int tabtuiles[6],int indextuilecourante)
* \brief  Verifie si une tuile respecte les regles de maniere individuelle
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] int tabtuiles[6] le tableau des tuiles posées
* \param[in] int indextuilecourante: l'index de la tuile posée a l'instant t
* \param[out] retourne 0 s'il n'y a pas d'erreur (regles respectées) ,le code erreur correspondant sinon
*
* Code erreur:
*              - 0: pas d'erreur
*              // pris en compte dans la fonction poser tuile - 1: erreur POSITION: tuile est deja posée à cette position
*              - 2: erreur ALONE: la tuile n'est pas adjacente a d'autres tuiles
*              - 3: erreur niFORMEniCOULEUR: la tuile n'a aucune caracteristique en commun avec une tuile adjacente
*              - 4: erreur FORMEetCOULEUR:est de même FORME et COULEUR qu'une (ou plusieurs) tuile(s) adjacente(s)
*              - 5: erreur COULEUR: la tuile est de COULEUR differente de celles qui lui sont adjacentes
*              - 6: erreur FORME: la tuile est de FORME differente de celles qui lui sont adjacentes
*
*/
int isTuileCorrect(Partie *p,int tabtuiles[6],int indextuilecourante)
{
   int i,erreur=0,hasvoisintuile;
   Erreur errorCF;Tuile *tj;
   poseTuilevirtuel(tabtuiles,p);
    i=indextuilecourante;
        if(tabtuiles[i]!=0)
        {
         if(getJoueurCourant(p)->tuilesJoueur[i]!=NULL)
          {
            tj=getJoueurCourant(p)->tuilesJoueur[i];
            hasvoisintuile=hasvoisinTuile(p,tj->x,tj->y);
            //if(getTuileplateau(p,SELF,tj->x,tj->x)!=NULL) {  erreur=1;} // c'est pris en compte dans un autre code on ne peut pas ecraser une tuile
            if(hasvoisintuile!=1)              {  erreur=2;}
            errorCF=isColorFormeCorrect(p,tj);
            if(errorCF==niFORMEniCOULEUR)     { erreur=3;}
            else if(errorCF==FORMEetCOULEUR)  { erreur=4;}
            else if(errorCF==COULEUR)         { erreur=5;}
            else  if(errorCF==FORME)          { erreur=6;}
          }
        }

    supprTuileVirtuel(tabtuiles,p);
    return erreur;
}

/*!
* int nbrtuilesposee(int tabtuiles[6])
*\brief  La fonction permet de connaitre le nombre de tuiles provisoires posees sur le plateau
*\param[in] int tabtuiles[6]: tableau des tuiles provisoirement posees sur le plateau
*\param[out] renvoie le nombre de tuiles provisoires posees sur le plateau
*/
int nbrtuilesposee(int tabtuiles[6])
{
   int i,count=0;
   for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {count++;}
    }
    return count;
}

/*!
* int linkedtotherest(Partie *p,int tabtuiles[6])
* \brief La fonction permet de savoir si le mot posé est rattaché à d'autres tuiles déja posees sur le plateau
        Elle regarde si au moins une tuile autre que celles dans tabtuilesposee est reliee a une tuile du mot posé (une tuile de tabtuileposee)
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] int tabtuiles[6] le tableau des tuiles posées
* \param[in] int indextuilecourante: l'index de la tuile posée a l'instant t
* \param[out] 1 si le mot est rattaché à d'autres tuiles déja posees,0 sinon
*/
int linkedtotherest(Partie *p,int tabtuiles[6])
{
 int nbrtuilesp;int *nbrofneighbors;int*partofword,linked=0;
 Tuile *tj;Tuile *td;
 int i,j,k,ind=0,voisin=0,partofw=0;

    nbrtuilesp=nbrtuilesposee(tabtuiles);if(nbrtuilesp==1){return 1;}
    nbrofneighbors=(int*)malloc(sizeof(int)*nbrtuilesp);
    partofword=(int*)malloc(sizeof(int)*nbrtuilesp);

     for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {
         if(getJoueurCourant(p)->tuilesJoueur[i]!=NULL)
          {
            tj=getJoueurCourant(p)->tuilesJoueur[i];
                for(j=0;j<4;j++)
                    {
                      td=getTuileplateau(p,nextDir(j),tj->x,tj->y);
                        if(td!=NULL)
                        {   voisin++;
                          for(k=0;k<6;k++)
                            {
                              if(td==getJoueurCourant(p)->tuilesJoueur[k]){partofw++;}
                            }
                        }
                    }
                    nbrofneighbors[ind]=voisin;partofword[ind]=partofw;ind++;voisin=0; partofw=0;
          }
        }

    }

    for(i=0;i<nbrtuilesp;i++)
    {
      if(nbrofneighbors[i]>partofword[i])
          {linked=1;}
    }
    free(nbrofneighbors);free(partofword);
    return linked;

}
/*!
* int isTuileCorrect2(Partie *p,int tabtuiles[6])
* \brief  Verifie si une tuile respecte les regles de maniere individuelle et si le mot est toujours correct apres deselection d'une tuile
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] int tabtuiles[6] le tableau des tuiles posées
* \param[in] int indextuilecourante: l'index de la tuile posée a l'instant t
* \param[out] retourne 0 s'il n'y a pas d'erreur (regles respectées) ,le code erreur correspondant sinon
*
* La difference avec isTuilecorrect est que cette fonction revérifie si les tuiles toujours posées sur le plateau sont toujours correctes après qu'une tuile ait été désélectionnée par exemple
*/
int isTuileCorrect2(Partie *p,int tabtuiles[6])
{
    int i,hasvoisintuile,linked;
    Erreur errorCF;Tuile *tj;
    poseTuilevirtuel(tabtuiles,p);
    if(istabtuilesVide(tabtuiles)==1){return 1;}

    linked=linkedtotherest(p,tabtuiles);

    if(linked!=1){supprTuileVirtuel(tabtuiles,p);return 2;}

        for(i=0;i<6;i++)
      {
        if(tabtuiles[i]!=0)
        {
         if(getJoueurCourant(p)->tuilesJoueur[i]!=NULL)
          {
            tj=getJoueurCourant(p)->tuilesJoueur[i];
            hasvoisintuile=hasvoisinTuile(p,tj->x,tj->y);
            if(hasvoisintuile!=1)              { supprTuileVirtuel(tabtuiles,p);return 2;}
            errorCF=isColorFormeCorrect(p,tj);

            if(errorCF==niFORMEniCOULEUR)      {supprTuileVirtuel(tabtuiles,p);return 3;}
            else if(errorCF==FORMEetCOULEUR)  { supprTuileVirtuel(tabtuiles,p);return 4;}
            else if(errorCF==COULEUR)         { supprTuileVirtuel(tabtuiles,p);return 5;}
            else  if(errorCF==FORME)          {supprTuileVirtuel(tabtuiles,p); return 6;}
          }
        }
      }
    supprTuileVirtuel(tabtuiles,p);
    return 0;
}

/*!
* int stillawordXy(Partie *p,Tuile *tuilemin,int nbrtuiles,int xory)
* \brief  Verifie si les tuiles provisoires posées sur le plateau forment toujours un mot correct apres que le joueur ait déselectionné une tuile du mot provisoire
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] Tuile *tuilemin tuile du mot provisoire avec le "x" le plus petit ou avec le y le plus petit
* \param[in] int nbrtuiles nombres de tuiles provisoires actuellement posées sur le plateau
* \param[in] int xory si xory=1 on a la tuile tuilemin avec le y le plus petit sinon,nous avons la tuile  avec le x le plus petit
* \param[out] si erreur=0 il n'y a pas d'erreur les tuiles du tableau forment toujours un mot correct. le contraire si erreur=1
*/
int stillawordXy(Partie *p,Tuile *tuilemin,int nbrtuiles,int xory)
{
  int i,x,y,erreur=0;Tuile *tuileprovi;
  x=tuilemin->x;y=tuilemin->y;
  if(xory==1)
  {
    for(i=1;i<nbrtuiles;i++)  // tuileminy bcsame x, straight down the line so gotta have the one with min y
    {
        if(getTuileplateau(p,BAS,x,y)==NULL){erreur=1;}
        else{
              tuileprovi=getTuileplateau(p,BAS,x,y);
              x=tuileprovi->x;y=tuileprovi->y;
            }
    }
  }
  else
  {
    for(i=1;i<nbrtuiles;i++) // tuileminx bc same y, straight to the right so gotta have the one with min x
    {
        if(getTuileplateau(p,DROITE,x,y)==NULL){erreur=1;}
        else{
              tuileprovi=getTuileplateau(p,DROITE,x,y);
              x=tuileprovi->x;y=tuileprovi->y;
            }
    }
  }
 return erreur;
}



/*!
* int isWordCorrect(Partie *p,int tabtuiles[6])
* \brief  Vérifie si le mot que veut jouer le joueur courant est correct: les tuiles doivent être soit de la même couleur soit de la même forme. Il ne doit pas y avoir deux tuiles de même couleur ou de même forme pour un mot. Les tuiles du mot doivent également être alignées
* \param[in] Partie *p,int tabtuiles[6]
* \param[out] retourne 1 s'il n'y a pas d'erreur (word is correct) ,0 sinon
*/
int isWordCorrect(Partie *p,int tabtuiles[6])
{
    int i,ind=1,tabX,tabY,sameX=1,sameY=1,nbtuiles=0,minx,miny,stillw;
    Tuile *tuileminx;Tuile *tuileminy;
    Tuile *tuilesposees[6]={NULL,NULL,NULL,NULL,NULL,NULL};
    poseTuilevirtuel(tabtuiles,p);
   for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {
        if(getJoueurCourant(p)->tuilesJoueur[i]!=NULL)
          {
            tuilesposees[nbtuiles]=getJoueurCourant(p)->tuilesJoueur[i];
            nbtuiles++;
          }
        }
    }

     if(nbtuiles>1)
    {
        tabX=tuilesposees[0]->x; tabY=tuilesposees[0]->y;
        minx=tabX; miny=tabY; tuileminx=tuilesposees[0];tuileminy=tuilesposees[0];

        for(i=1;i<nbtuiles;i++)
        {
            if(minx>tuilesposees[i]->x)
            {minx=tuilesposees[i]->x;tuileminx=tuilesposees[i];
            }
            if(miny>tuilesposees[i]->y) {miny=tuilesposees[i]->y;tuileminy=tuilesposees[i];
            }

            if(tabX!=tuilesposees[i]->x) {sameX=0;}
            if(tabY!=tuilesposees[i]->y) {sameY=0;}
        }
        if( sameX==0 && sameY==1)
        {
          ind=1;stillw=stillawordXy(p,tuileminx,nbtuiles,0);
          if(stillw==1){supprTuileVirtuel(tabtuiles,p);return 2;}
        }
        else if (sameX==1 && sameY==0)
         {
           ind= 1;stillw=stillawordXy(p,tuileminy,nbtuiles,1);
           if(stillw==1){supprTuileVirtuel(tabtuiles,p);return 2;}
         }
        else {ind=0;}
    }
     supprTuileVirtuel(tabtuiles,p);
     return ind;
}

/*!
* int istabtuilesVide(int tabtuiles[6])
* \brief  permet de savoir au mons une tuile est selectionnée (si  tabtuilesposees est non vide)
* \param[in] int tabtuiles[6]: le tableau des tuiles posées
* \param[out] retourne 1 si tabtuile est vide, 0 sinon

*/
int istabtuilesVide(int tabtuiles[6])
{
    int i,vide=1;
    for(i=0;i<6;i++)
     {
        if(tabtuiles[i]!=0)
        {vide=0;}
     }
    return vide;
}





