/**
* \file regle.c
*
* \brief Fichier contenant le code nécessaire à la gestion des règles
*
* \author SOW Aicha
* \version 2.0
* \date 22/04/2020
* Dans ce fichier ce trouve l'implémentation des fonctions permettant de respecter les règles
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regle.h"
#include "../Controleur/message.h"

/*!
* \fn Tuile * getTuileplateau(Partie *p,Direction d,int x,int y)
* \brief   Permet de recuperer la tuile qui se trouve en HAUT,en BAS,à GAUCHE ou à DROITE d'une tuile dont on a les coordonnées x et y
* \param[in] Partie * p : pointeur vers la partie
* \param[in]  Direction d la direction(HAUT,BAS,GAUCHE,DROITE)
* \param[in] int x,int y les coordonnées de la tuile lorsqu'elle est sur le plateau
* \param[out] Tuile * retourne une tuile en fonction de la direction
*
*/
Tuile *getTuileplateau(Partie *p,Direction d,int x,int y)
{
    int posx=0;
    int posy=0;
    if (d==HAUT)
    {
        posx=1;
        posy=2;
    }
    else if (d==BAS)
    {
        posx=1;
    }
    else if (d==GAUCHE)
    {
        posx=2;
        posy=1;
    }
    else if(d==DROITE)
    {
        posy=1;
    }
    else if(d==SELF)
    {
        posx=1;
        posy=1;
    }
    return p->plateau->tuiles[x-posx][y-posy];

}

/*!
* \fn Direction nextDir(int i)
* \brief  Permet de faire correspondre une valeur de i (0,1,2,3,4) passée en entrée avec une direction (HAUT,BAS,GAUCHE,DROITE) que l'on retournera en sortie
* \param[in] int i : un entier un indique quelle direction l'on veut
* \param[out] Retourne la direction(HAUT,BAS,GAUCHE,DROITE) demandée
*
*/
Direction nextDir(int i)
{
    Direction d=0;
    if (i==0)
    {
        d=HAUT;
    }
    else if (i==1)
    {
        d=BAS;
    }
   else  if (i==2)
    {
        d=GAUCHE;
    }
   else if (i==3)
    {
        d=DROITE;
    }
   else   if (i==4)
    {
        d=SELF;
    }
    return d;
}


/*!
* \fn int hasvoisinTuile(Partie *p,int x,int y)
* \brief Verifie que la tuile est directement adjacente à au moins une autre tuile
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] int x,int y les coordonnées de la tuile
* \param[out] retourne 1 si la tuile est adjacente directement a au moins une autre tuile 0 sinon
*/
int hasvoisinTuile(Partie *p,int x,int y)
{
    int i=0;
    int voisin=0;
    for(i=0; i<4; i++)
    {
        Tuile *td=getTuileplateau(p,nextDir(i),x,y);
        if(td!=NULL)
        {
            voisin++;
        }
    }
    return (voisin!=0);
}

/*!
* \fn int critereCouleurForme(Partie *p,Direction d,Tuile *tj)
* \brief Permet de connaitre le critere de pose que doit avoir la tuile à poser en fonction du critere qu'ont en commun les tuiles déja posées (soit couleur soit forme)
* \param[in] Partie *p : : pointeur vers la partie
* \param[in] Direction d la direction(HAUT,BAS,GAUCHE,DROITE)
* \param[in] Tuile *tj la tuile à poser (pour avoirs ses coordonnées
* \param[out] retourne 10 si la tuile doit avoir la même couleur que celles deja posées
* \param[out] retourne 11 si la tuile doit avoir la même Forme que celles deja posées
* \param[out] retroune 22 si selon la direction, il n'y pas de tuiles deja posée et donc la tuile peut etre poser peu importe la couleur ou la forme en ce qui concerne la DIRECTION en question
*/
int critereCouleurForme(Partie *p,Direction d,Tuile *tj)
{
    int cmpC,cmpF;
    Tuile *parent=getTuileplateau(p,d,tj->x,tj->y);
    if(parent!=NULL)
    {
        Tuile *gparent=getTuileplateau(p,d,parent->x,parent->y);

        if(gparent!=NULL )
        {
            cmpC=compareCouleur(parent,gparent);//compareCouleur retoune 1 si different
            cmpF=compareForme(parent,gparent);
            if(cmpC==0 && cmpF==1)
            {
                return 10;   //Cmpc==0 ils ont la meme couleur
            }
            else if (cmpC==1 && cmpF==0)
            {
                return 11;
            }
        }
    }

    return 22;
}

/*!
* \fn int respectcriterePose(Partie *p,Tuile *tj,Tuile *td,Direction d)
* \brief Verifie que la tuile à poser est de même couleur ou de même forme que les tuiles déja posées du mot à compléter
* \param[in] Partie *p : pointeur vers la partie
* \param[in] Direction d : la direction (HAUT,BAS,GAUCHE,DROITE)
* \param[in] Tuile *tj la tuile à poser (pour avoirs ses coordonnées
* \param[in] Tuile *td tuile qui serait en haut, bas , gauche droite de la tuile tj si cette dernière venait à être posée. td dépend donc de la direction d
* \param[out] retourne 100 si les tuiles td et tj n'ont PAS les mêmes COULEURS
* \param[out] retourne 111 si les tuiles td et tj n'ont PAS les mêmes FORMES
* \param[out] retroune 222 si selon la direction, il n'y ait pas une tuile ou un mot formé de 2 tuiles deja posé et donc la tuile peut être posée peu importe la couleur ou la forme en ce qui concerne la DIRECTION en question
*/
int respectcriterePose(Partie *p,Tuile *tj,Tuile *td,Direction d)
{
    int c=0;
    int comp=0;;
    c=critereCouleurForme(p,d,tj);
    if(c==10)
    {
        comp=compareCouleur(tj,td);
        if(comp==1)
        {
            return 100;
        }
    }
    else if(c==11)
    {
        comp=compareForme(tj,td);
        if(comp==1)
        {
            return 111;
        }
    }
    return 222;

}


/*!
* \fn int dejaPosee(Partie *p,Tuile *tj,Direction d)
* \brief Verifie si une tuile tj est de même couleur ET forme que celles déjà posées dans le mot à compléter, dans une direction donnée
* \param[in] Partie *p : : pointeur vers la partie
* \param[in]  Direction d la direction(HAUT,BAS,GAUCHE,DROITE)
* \param[in]  Tuile *tj la tuile à poser
* \param[out] retourne 1 si une tuile identique à celle poser se trouve déja dans le mot à completer et dans la direction d
*/
int dejaPosee(Partie *p,Tuile *tj,Direction d)
{
    int cmpC=0;
    int cmpF=0;
    Tuile *tp=getTuileplateau(p,d,tj->x,tj->y);
    while(tp!=NULL)
    {
        cmpC=compareCouleur(tj,tp);
        cmpF=compareForme(tj,tp);
        if(cmpC==0 && cmpF==0)
        {
            return  1;
        }
        tp=getTuileplateau(p,d,tp->x,tp->y);
    }
    return 0;
}

/*!
* \fn Erreur isColorFormeCorrect(Partie *p,Tuile *tj)
* \brief Permet de vérifier si la tuile peut être posée: La fonction retourne des -erreurs- si la pose de la tuile ne respecte pas les règles du jeu
* \param[in] Partie *p : : pointeur vers la partie
* \param[in]  Tuile *tj la tuile à poser
* \param[out] retourne l'erreur adéquate en fonction de la nature de la règle non respectée
*/
Erreur isColorFormeCorrect(Partie *p,Tuile *tj)
{
    int i=0;
    int erreurC=0,erreurF=0,error=0,dejaposee=0;
    for(i=0; i<4; i++)
    {
        Tuile *td=getTuileplateau(p,nextDir(i),tj->x,tj->y);
        if(td!=NULL)
        {
            erreurC=compareCouleur(tj,td);
            erreurF=compareForme(tj,td);
            if(erreurC==1 && erreurF==1)
            {
                return  niFORMEniCOULEUR;
            }

            error=respectcriterePose(p,tj,td,nextDir(i));
            if(error==111)
            {
                return FORME;
            }
            else if(error==100)
            {
                return COULEUR;
            }

            dejaposee=dejaPosee(p,tj,nextDir(i));
            if(dejaposee==1)
            {
                return FORMEetCOULEUR;
            }
        }
    }
    return NOERROR;
}



/*!
* int compareCouleur(Tuile *t1, Tuile *t2)
* \brief      Compare les couleurs de deux tuiles
* \param[in]  Tuile *t1
* \param[in]  Tuile *t2
* \param[out] retourne 1 si les tuiles ont des couleurs différentes, 0 sinon
*
*/
int compareCouleur(Tuile *t1, Tuile *t2)
{
    return (getCouleur(t1)!=getCouleur(t2));
}

/*!
* int compareForme(Tuile *t1, Tuile *t2)
* \brief   Compare les formes de deux tuiles
* \param[in]  Tuile *t1
* \param[in]  Tuile *t2
* \param[out] retourne 1 si les tuiles ont des formes différentes, 0 sinon
*
*/
int compareForme(Tuile *t1, Tuile *t2)
{
    return (getForme(t1)!=getForme(t2));
}
