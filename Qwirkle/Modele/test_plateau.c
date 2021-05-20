/*!
* \file test_plateau.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaires à la gestion du Plateau
*
* \author VIAUD Léa
* \version 1.0
* \date 01/03/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires à la gestion du Plateau
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmocka.h" //ajout de cmocka pour les test unitaire
#include <stdio.h>
#include <stdlib.h>
#include "tuile.h"
#include "plateau.h"
#include "test.h"

static int setup_zero(void **state)                             //Test unitaire d'initPlateau pour l'initialisation du plateau
{
    Plateau *p = initPlateau();
    if(p == NULL)
    {
        printf("error mem in setup_zero of initPlateau\n");
        return -1;
    }
    *state = p;

    return 0;
}

static void test_poserTuile(void **state){

    Tuile t = createTuile(ROUGE,CERCLE);
    Plateau *test=(Plateau *) (*state);

    poserTuile(test,&t,100,100);

    assert_int_equal(100,test->tuiles[99][99]->x);
    assert_int_equal(100,test->tuiles[99][99]->y);
    assert_int_equal(0,test->tuiles[99][99]->couleur);
    assert_int_equal(0,test->tuiles[99][99]->forme);

}

static void test_modifieZonedeJeu(void **state){
    Plateau *test=(Plateau *) (*state);
    Tuile t1 = createTuile(ROUGE,CERCLE);
    Tuile t2 = createTuile(BLEU,CARRE);

    int xmax = test->xmax;
    int xmin = test->xmin;
    int ymax = test->ymax;
    int ymin = test->ymin;

    poserTuile(test,&t1,101,101);
    poserTuile(test,&t2,99,99);

    modifieZonedeJeu(test);
    assert_int_not_equal(xmax,test->xmax);
    assert_int_not_equal(xmin,test->xmin);
    assert_int_not_equal(ymax,test->ymax);
    assert_int_not_equal(ymin,test->ymin);
}

static void test_iscaseEmpty(void **state){
    Plateau *test=(Plateau *) (*state);
    Tuile t = createTuile(ROUGE,CERCLE);

    assert_int_equal(1,iscaseEmpty(test,101,101));

    poserTuile(test,&t,102,102); //on ajoute un a cause de l'offset
    assert_int_equal(0,iscaseEmpty(test,101,101));

}

static int teardown(void **state)                               //Test unitaire pour free le plateau
{
    freePlateau(*state);
    return 0;
}

int main_test_plateau(void)
{
    const struct CMUnitTest test_plateau[] =
    {
        cmocka_unit_test_setup_teardown(test_poserTuile,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_modifieZonedeJeu,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_iscaseEmpty,setup_zero,teardown),
    };
    return cmocka_run_group_tests(test_plateau,NULL,NULL);
}
