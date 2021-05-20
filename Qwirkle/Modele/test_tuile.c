/*!
* \file test_tuile.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaire à l'utilisation de Tuile
*
* \author VIAUD Léa
* \version 1.0
* \date 27/02/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires à la manipulation des Tuiles
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "tuile.h"




static void test_getCouleur(void **state)
{
    Tuile test=createTuile(1,1);
    assert_int_equal(1,getCouleur(&test));
}

static void test_getForme(void **state)
{
    Tuile test=createTuile(1,1);
    assert_int_equal(1,getForme(&test));
}

static void test_createTuile(void **state)
{
    Tuile test=createTuile(1,1);
    assert_int_equal(1,test.couleur);
    assert_int_equal(1,test.forme);
    assert_int_equal(-1,test.x);
    assert_int_equal(-1,test.y);
}

int main_test_tuile(void)
{
    const struct CMUnitTest test_tuile[] =
    {
        cmocka_unit_test(test_createTuile),
        cmocka_unit_test(test_getCouleur),
        cmocka_unit_test(test_getForme),

    };
    return cmocka_run_group_tests(test_tuile,NULL,NULL);
}
