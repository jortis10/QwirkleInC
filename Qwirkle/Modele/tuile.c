/*!
* \file tuile.c
* \brief Fichier contenant les fonctions nécessaire à l'utilisation de Tuile
*
* \author VIAUD Léa
* \version 1.0
* \date 25/02/2020
*
* Dans ce fichier ce trouve les fonctions nécessaires à la manipulation des Tuiles
*/

#include <stdio.h>
#include <stdlib.h>
#include "tuile.h"

/*!
* \fn Tuile createTuile(Couleur c,Forme f)
* \brief  créé une Tuile avec une forme et une couleur données en paramètre
* sa position x et y est initialisé à -1
*
* \param[in] c Couleur de la Tuile
* \param[in] f Forme de la Tuile
* \param[out] Tuile
*
*/
Tuile createTuile(Couleur c, Forme f)
{
    Tuile t;
    t.couleur=c;
    t.forme=f;
    t.x=-1;
    t.y=-1;
    return t;
}


/*!
* \fn Couleur getCouleur(Tuile *t)
* \brief  retourne la couleur d'une Tuile passée en pramètre
*
* \param[in] t , pointeur vers une Tuile
* \param[out] Couleur
*/
Couleur getCouleur(Tuile *t)
{
    return t->couleur;
}

/*!
* \fn Forme getForme(Tuile *t)
* \brief  retourne la forme d'une Tuile passée en pramètre
*
* \param[in] t , pointeur vers une Tuile
* \param[out] Forme
*/
Forme getForme(Tuile *t)
{
    return t->forme;
}

