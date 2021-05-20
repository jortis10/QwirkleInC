/*!
* \file test_score.c
* \brief Fichier contenant les tests unitaires des fonctions de score.c
*
* \author VIAUD Léa
* \version 1.0
* \date 03/05/2020
*
* Dans ce fichier ce trouve les tests des fonctions de score.c
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "partie.h"
#include "score.h"

static int setup_zero(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
{
    Partie *setup=(CommencerPartie(2));
    if(setup==NULL)
        return -1;
    *state=setup;
    return 0;
}

static int setup_un(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
{
    Tuile *setup=(Tuile *) malloc(sizeof(Tuile)) ;
    if (setup==NULL)
      return -1;
    Forme f=1;
    Couleur c=1;
    *setup=createTuile(c,f);
    *state=setup;
    return 0;
}

static int teardown(void **state)
{
    freePartie(*state);
    return 0;
}

static int teardown1(void **state)
{
    free(*state);
    return 0;
}
static void test_getPosX(void **state)
{
    Partie *test=(Partie*) (*state);
    int i=0;
    assert_int_equal(getJoueurCourant(test)->tuilesJoueur[i]->x,getPosX(test,i));
}

static void test_getPosY(void **state)
{
    Partie *test=(Partie*) (*state);
    int i=0;
    assert_int_equal(getJoueurCourant(test)->tuilesJoueur[i]->y,getPosY(test,i));
}
static void test_majPointsV0(void **state)
{
    Partie *test=(Partie*) (*state);
    int tab[6]={0};
    majPointsV0(test,tab);
    assert_int_equal(0,getJoueurCourant(test)->points);
    int tab2[6]={1,1,1,1,1,1};
    majPointsV0(test,tab2);
    assert_int_equal(12,getJoueurCourant(test)->points);
    int tab3[6]={0,0,1,1,0,1};
    majPointsV0(test,tab3);
    assert_int_equal(15,getJoueurCourant(test)->points);
}
static void test_isDejaComptee(void **state)
{
    Tuile *test=(Tuile*) (*state);
    int tab[50][2]={0};
    tab[0][0]=100;
    tab[0][1]=100;
    test->x=100;
    test->y=100;
    assert_int_equal(1,isDejaComptee(tab,test));
    test->x=99;
    test->y=99;
    assert_int_equal(0,isDejaComptee(tab,test));
}

static void test_appartienta2lignes(void **state)
{
    Partie *test=(Partie*) (*state);
    poserTuile(test->plateau,test->sac[test->nbTuilesSac-1],100,100);

    test->nbTuilesSac--;
    poserTuile(test->plateau,test->sac[test->nbTuilesSac-1],101,101);
    test->nbTuilesSac--;

    assert_int_equal(1,appartient2lignes(test,100,101));
    assert_int_equal(0,appartient2lignes(test,100,99));
}

static void test_poseTuilevirtuel(void **state)
{
    Partie *test=(Partie*) (*state);
    int tab[6]={1,1,0,0,0,0};
    getJoueurCourant(test)->tuilesJoueur[0]->x=100;
    getJoueurCourant(test)->tuilesJoueur[0]->y=101;
    getJoueurCourant(test)->tuilesJoueur[1]->x=100;
    getJoueurCourant(test)->tuilesJoueur[1]->y=102;
    assert_null(test->plateau->tuiles[99][100]);
    assert_null(test->plateau->tuiles[99][101]);
    poseTuilevirtuel(tab,test);
    assert_non_null(test->plateau->tuiles[99][100]);
    assert_non_null(test->plateau->tuiles[99][101]);
}

static void test_supprTuilevirtuel(void **state)
{
    Partie *test=(Partie*) (*state);
    int tab[6]={1,1,0,0,0,0};
    getJoueurCourant(test)->tuilesJoueur[0]->x=100;
    getJoueurCourant(test)->tuilesJoueur[0]->y=101;
    getJoueurCourant(test)->tuilesJoueur[1]->x=100;
    getJoueurCourant(test)->tuilesJoueur[1]->y=102;
    assert_null(test->plateau->tuiles[99][100]);
    assert_null(test->plateau->tuiles[99][101]);
    poseTuilevirtuel(tab,test);
    assert_non_null(test->plateau->tuiles[99][100]);
    assert_non_null(test->plateau->tuiles[99][101]);
    supprTuileVirtuel(tab,test);
    assert_null(test->plateau->tuiles[99][100]);
    assert_null(test->plateau->tuiles[99][101]);
}

static void test_majPoints(void **state)
{
    Partie *test=(Partie*) (*state);
    assert_int_equal(0,getPoints(getJoueurCourant(test)));


    int tab1[6]={0,1,0,0,0,0};
    getJoueurCourant(test)->tuilesJoueur[1]->x=101;
    getJoueurCourant(test)->tuilesJoueur[1]->y=100;
    majPoints(test,tab1);
    assert_int_equal(2,getPoints(getJoueurCourant(test)));

}

int main_test_score(void)
{
    const struct CMUnitTest test_score[] =
    {
        cmocka_unit_test_setup_teardown(test_getPosX,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_getPosY,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_majPointsV0,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_isDejaComptee,setup_un,teardown1),
        cmocka_unit_test_setup_teardown(test_appartienta2lignes,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_poseTuilevirtuel,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_supprTuilevirtuel,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_majPoints,setup_zero,teardown),
    };
    return cmocka_run_group_tests(test_score,NULL,NULL);
}
