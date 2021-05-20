/*!
* \file test_joueur.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaire au joueur
*
* \author VIAUD Léa
* \version 1.0
* \date 17/03/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires au joueur
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "joueur.h"

static int setup_zero(void **state)                             /*!Test unitaire pour créer un Joueur*/
{
    char nom[10]="Joueur";
    Joueur *setup=creationJoueur(nom);
    if (setup==NULL)
      return -1;
    *state=setup;
    return 0;
}

static void test_initPoints(void **state)                       /*!Test unitaire pour l'initialisation des points */
{
    Joueur *test=(Joueur*) (*state);
    initPoints(test);
    assert_int_equal(0,getPoints(test));
}

static void test_ajouterPoints(void **state)                       /*!Test unitaire pour l'initialisation des points */
{
    Joueur *test=(Joueur*) (*state);
    initPoints(test);
    assert_int_equal(0,getPoints(test));
    ajouterPoints(1,test);
    assert_int_equal(1,getPoints(test));
}

static int teardown(void **state)                               /*!Test unitaire pour free un Joueur*/
{
    freeJoueur(*state);
    return 0;
}

static void test_getPoints(void **state)
{
    Joueur *test=(Joueur*) (*state);
    test->points=10;
    assert_int_equal(10,getPoints(test));
}

static void test_getPointsNULL(void **state)
{
    Joueur *j=NULL;
    assert_int_equal(0,getPoints(j));
}
static void test_initPointsNULL(void **state)
{
    Joueur *j=NULL;
    assert_int_equal(-1,initPoints(j));
}

int main_test_joueur(void)
{
    const struct CMUnitTest test_joueur[] =
    {
        cmocka_unit_test_setup_teardown(test_getPoints,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_initPoints,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_ajouterPoints,setup_zero,teardown),
        cmocka_unit_test(test_getPointsNULL),
        cmocka_unit_test(test_initPointsNULL),
    };
    return cmocka_run_group_tests(test_joueur,NULL,NULL);
}

