/*!
* \file test_partie.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaires à la gestion de la Partie
*
* \author VIAUD Léa
* \version 1.0
* \date 01/03/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires à la gestion de la Partie
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h" //ajout de cmocka pour les test unitaire
#include <stdio.h>
#include <stdlib.h>
#include "partie.h"
#include "test.h"

static int setupdistributionInit(void **state)                             //Test unitaire d'initPlateau pour l'initialisation du plateau
{
    int nbjoueurs =3;
    Partie *p=creationPartie(nbjoueurs);

    if(p==NULL)
    {
        printf("error mem in setup_zero of creationPartie\n");
        return -1;
    }
    char nomdujoueur[10] ="Joueur ";

    for(int i=0; i<nbjoueurs; i++)
    {
        nomdujoueur[7]=49+i;

        p->joueurs[i]=creationJoueur(nomdujoueur);
    }
    p->NbJoueurs=nbjoueurs;
    p->joueurCourant=0;
    mettreTuilesdanslot(p);
    genererTuileSac(p);
    melangerSac(p,0);
    p->plateau=initPlateau();
    placerTuileMilieu(p);


    *state = p;

    return 0;
}

static int setupplacerTuilemilieu(void **state)                             //Test unitaire d'initPlateau pour l'initialisation du plateau
{
    int nbjoueurs =3;
    Partie *p=creationPartie(nbjoueurs);

    if(p==NULL)
    {
        printf("error mem in setup_zero of creationPartie\n");
        return -1;
    }
    char nomdujoueur[10] ="Joueur ";

    for(int i=0; i<nbjoueurs; i++)
    {
        nomdujoueur[7]=49+i;

        p->joueurs[i]=creationJoueur(nomdujoueur);
    }
    p->NbJoueurs=nbjoueurs;
    p->joueurCourant=0;
    mettreTuilesdanslot(p);
    genererTuileSac(p);
    melangerSac(p,0);
    p->plateau=initPlateau();
    *state = p;

    return 0;
}
static int setupCommencerPartie(void **state)
{
    Partie *p=CommencerPartie(3);
    if(p==NULL)
    {
        printf("error mem in setupCommencerPartie of CommencerPartie\n");
        return -1;
    }
    *state = p;

    return 0;

}

static int teardown(void **state)                               /*!Test unitaire pour free la partie*/
{
    Partie * p= (Partie*)(*state);
    freePartie(p);
    return 0;
}

static void test_distributionInit(void **state)
{
    Partie * p= (Partie*)(*state);

    distibutionInit(p);
    for(int i=0; i<NBTUILESMAX; i++)
    {
        for(int j=0; j<p->NbJoueurs; j++)
        {
            assert_non_null(p->joueurs[j]->tuilesJoueur[i]);
        }
    }
}

static void test_joueurSuivant(void **state)
{
    Partie * p= (Partie*)(*state);
    p->joueurCourant=0;
    joueurSuivant(p);
    assert_int_equal(1,p->joueurCourant);
    joueurSuivant(p);
    joueurSuivant(p);
    assert_int_equal(0,p->joueurCourant);
}

static void test_placerTuileMilieu(void **state)
{
    Partie * p= (Partie*)(*state);
    placerTuileMilieu(p);
    assert_int_equal(p->nbTuilesSac,NBTUILESSACMAX-1);
    assert_non_null(p->plateau->tuiles[99][99]);
}

static void test_getJoueurCourant(void **state)
{
    Partie * p= (Partie*)(*state);
    assert_int_equal(p->joueurs[0],getJoueurCourant(p));
    joueurSuivant(p);
    assert_int_equal(p->joueurs[1],getJoueurCourant(p));
}
static void test_getJoueurCourantNULL(void **state)
{
    Partie *p=NULL;
    assert_int_equal(NULL,getJoueurCourant(p));
}


int main_test_partie(void)
{
    const struct CMUnitTest test_partie[] =
    {

        cmocka_unit_test_setup_teardown(test_joueurSuivant,setupCommencerPartie,teardown),
        cmocka_unit_test_setup_teardown(test_placerTuileMilieu,setupplacerTuilemilieu,teardown),
        cmocka_unit_test_setup_teardown(test_getJoueurCourant,setupCommencerPartie,teardown),
        cmocka_unit_test_setup_teardown(test_distributionInit,setupdistributionInit,teardown),
        cmocka_unit_test(test_getJoueurCourantNULL),
    };
    return cmocka_run_group_tests(test_partie,NULL,NULL);
}
