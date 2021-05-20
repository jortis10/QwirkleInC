/**
* \file score.c
*
* \brief Fichier contenant le code nécessaire au comptage des points
*
* \author VIAUD Léa
* \version 1.0
* \date 21/04/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions permettant de compter les points
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"



/*!
* \fn void majPoints(Partie *p,int tabtuiles[6])
* \brief  met à jour le nombre des points du joueur courant en fonction du nombre de tuiles qu'il pose
* 1 tuile posée = 1point, si elle appartient à deux lignes = 1point supplémentaire
* chaque tuile en plus sur la ligne vaut 1 point si elle n'a pas déjà été comptée
* si le joueur complète un mot de 6 tuiles il a un bonus =6points
* lorsqu'une tuile est comptée elle est ajoutée dans un tableau pour identifier les tuiles déjà comptées
*
* \param[in] int tabtuiles[6] : donne l'index des tuiles que le joueur veut poser
* \param[in] Partie * p  : pointeur vers une partie
*
*/
void majPoints(Partie *p,int tabtuiles[6])
{
    int i=0;
    int dejaComptee[50][2]={0};
    int j=0;
    int vertical=0;
    int horizontale=0;
    int dir=0;
    poseTuilevirtuel(tabtuiles,p);
    for(i=0;i<6;i++)
    {
        vertical=0;
        horizontale=0;
        if(tabtuiles[i]!=0)
        {
            if(!isDejaComptee(dejaComptee,(getJoueurCourant(p)->tuilesJoueur[i])))
            {
                ajouterPoints(1,getJoueurCourant(p));
                dejaComptee[j][0]=getPosX(p,i);
                dejaComptee[j][1]=getPosY(p,i);
                j++;
            }
            for(dir=0;dir<4;dir++)
            {
                if(getTuileplateau(p,dir,getPosX(p,i),getPosY(p,i))!=NULL)
                {
                    Tuile *td=getTuileplateau(p,dir,getPosX(p,i),getPosY(p,i));
                    while(td!=NULL)
                    {
                        if(!isDejaComptee(dejaComptee,td))
                        {
                            ajouterPoints(1,getJoueurCourant(p));
                            dejaComptee[j][0]=td->x;
                            dejaComptee[j][1]=td->y;
                            j++;
                            if(dir==0||dir==1){vertical++;}
                            if(dir==2||dir==3){horizontale++;}
                        }
                        td=getTuileplateau(p,dir,td->x,td->y);
                    }
                }
            }
            if(appartient2lignes(p,getPosX(p,i),getPosY(p,i)))
                ajouterPoints(1,getJoueurCourant(p));
            if(vertical==5||horizontale==5)
                ajouterPoints(6,getJoueurCourant(p));
        }
    }
    supprTuileVirtuel(tabtuiles,p);
}

/*!
* \fn int getPosX(Partie *p,int i)
* \brief  permet d'obtenir la position X de la Tuile de la main du joueur à partir de l'indice donné en paramètre;
*
* \param[in] int i : indice de la tuile de la main du joueur concernée
* \param[in] Partie * p  : pointeur vers une partie
* \param[out] int : position X de la tuile
*/

int getPosX(Partie *p,int i)
{
    return getJoueurCourant(p)->tuilesJoueur[i]->x;
}

/*!
* \fn int getPosY(Partie *p,int i)
* \brief  permet d'obtenir la position Y de la Tuile de la main du joueur à partir de l'indice donné en paramètre;
*
* \param[in] int i : indice de la tuile de la main du joueur concernée
* \param[in] Partie * p  : pointeur vers une partie
* \param[out] int : position Y de la tuile
*/
int getPosY(Partie *p,int i)
{
    return getJoueurCourant(p)->tuilesJoueur[i]->y;
}

/*!
* \fn int isDejaComptee(int dejaComptee[50][2],Tuile *t)
* \brief  permet de vérifier si la tuile passé en paramètre à déjà été comptée
*
* \param[in] int dejaComptee[50][2]
* \param[in] Tuile *t
* \param[out] int : 1 si la tuile a déjà été comptée, 0 si elle n'a pas encore été compté
*/
int isDejaComptee(int dejaComptee[50][2],Tuile *t)
{
    int x=t->x;
    int y=t->y;
    int i=0;
    for(i=0;i<50;i++)
    {
        if(x==dejaComptee[i][0]&&y==dejaComptee[i][1])
        {
            return 1;
        }
    }
    return 0;
}

/*!
* \fn void majPointsV0(Partie *p,int tabtuiles[6])
* \brief  met à jour le nombre des points du joueur courant en fonction du nombre de tuiles qu'il pose (1 tuile posée=1 points, bonus +6 si il pose ses 6 tuiles)
* fonction pour utilisation de la V0
*
* \param[in] int tabtuiles[6] : donne l'index des tuiles que le joueur veut poser
* \param[in] Partie * p  : pointeur vers une partie
*
*/
void majPointsV0(Partie *p,int tabtuiles[6])
{
    int i=0;
    int nbtuiles=0;
    for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {
            ajouterPoints(1,getJoueurCourant(p));
            nbtuiles++;
        }
    }
    if(nbtuiles==6)
        ajouterPoints(6,getJoueurCourant(p));
}

/*!
* \fn int appartient2lignes(Partie *p,int x, int y)
* \brief  permet de vérifier si une tuile appartient à plusieurs lignes
*
* \param[in] int x : position x de la tuile sur le plateau
* \param[in] int y : position y de la tuile sur le plateau
* \param[in] Partie * p  : pointeur vers une partie
* \param[out] int : 1 si la tuile appartient à deux lignes, 0 sinon
*/
int appartient2lignes(Partie *p,int x, int y)
{
    int nblignes=0;
    if(getTuileplateau(p,DROITE,x,y)!=NULL&&(getTuileplateau(p,HAUT,x,y)!=NULL||getTuileplateau(p,BAS,x,y)!=NULL))
        nblignes=1;
    if(getTuileplateau(p,GAUCHE,x,y)!=NULL&&(getTuileplateau(p,HAUT,x,y)!=NULL||getTuileplateau(p,BAS,x,y)!=NULL))
        nblignes=1;
    if(getTuileplateau(p,HAUT,x,y)!=NULL&&(getTuileplateau(p,DROITE,x,y)!=NULL||getTuileplateau(p,GAUCHE,x,y)!=NULL))
        nblignes=1;
    if(getTuileplateau(p,BAS,x,y)!=NULL&&(getTuileplateau(p,DROITE,x,y)!=NULL||getTuileplateau(p,GAUCHE,x,y)!=NULL))
        nblignes=1;
    return nblignes;
}

/*!
* \fn void poseTuilevirtuel(int tabtuiles[6],Partie *p)
* \brief  permet de poser virtuellement les tuiles sur le plateau tout en les laissant dans la main du joueur
*
* \param[in] int tabtuiles[6] : donne l'index des tuiles que le joueur veut poser
* \param[in] Partie * p  : pointeur vers une partie
*
*/
void poseTuilevirtuel(int tabtuiles[6],Partie *p)
{
    int i;
    for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {
            int x=getPosX(p,i);
            int y=getPosY(p,i);
            p->plateau->tuiles[x-1][y-1]=getJoueurCourant(p)->tuilesJoueur[i];
        }
    }
}

/*!
* \fn void supprTuileVirtuel(int tabtuiles[6],Partie *p)
* \brief  permet d'enlever les tuiles qui étaient virtuellement posées sur le plateau par poseTuilevirtuel
*
* \param[in] int tabtuiles[6] : donne l'index des tuiles que le joueur veut poser
* \param[in] Partie * p  : pointeur vers une partie
*
*/
void supprTuileVirtuel(int tabtuiles[6],Partie *p)
{
    int i;
    for(i=0;i<6;i++)
    {
        if(tabtuiles[i]!=0)
        {
            int x=getPosX(p,i);
            int y=getPosY(p,i);
            p->plateau->tuiles[x-1][y-1]=NULL;
        }
    }

}
