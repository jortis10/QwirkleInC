/*!
* \file test_gestionSac.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaires à la gestion du Sac
*
* \author VIAUD Léa
* \version 1.0
* \date 01/03/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires à la gestion du Sac
*/

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "partie.h"
#include "tuile.h"


static int setup_zero(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
{
    Partie *setup=(Partie*)malloc(sizeof(Partie));
    if (setup==NULL)
      return -1;
    setup->nbTuilesSac=0;
    *state=setup;
    return 0;
}

static int setup_un(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
{
    Partie *setup=creationPartie(2);
    if (setup==NULL)
      return -1;
    mettreTuilesdanslot(setup);
    genererTuileSac(setup);
    *state=setup;
    return 0;
}

static int setup_deux(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
{
    Partie *setup=(CommencerPartie(1));
    if(setup==NULL)
        return -1;
    *state=setup;
    return 0;
}

static void test_mettreTuilesdanslelot(void **state)
{
    Partie * test=(Partie*) (*state);
    mettreTuilesdanslot(test);
    int i=0;
    int j,k;
    for (j=0;j<6;j++)
    {
        for(k=0;k<6;k++)
        {
                assert_int_equal(k,test->lotTuiles[i].forme);
                assert_int_equal(j,test->lotTuiles[i].couleur);
                assert_int_equal(k,test->lotTuiles[i+1].forme);
                assert_int_equal(j,test->lotTuiles[i+1].couleur);
                assert_int_equal(k,test->lotTuiles[i+2].forme);
                assert_int_equal(j,test->lotTuiles[i+2].couleur);
                i=i+3;
        }
    }
}
static int teardown0et1(void **state)
{
    free(*state);
    return 0;
}

static int teardown2(void **state)                                       /*!Test unitaire pour free le sac */
{
    freePartie(*state);
    return 0;
}

static void test_genererTuileSac(void **state)
{
    Partie * test =(Partie*) (*state);
    mettreTuilesdanslot(test);
    genererTuileSac(test);
    assert_int_equal(108,test->nbTuilesSac);
    int i=0;
    int j,k;
    for (j=0;j<6;j++)
    {
        for(k=0;k<6;k++)
        {
                assert_non_null(test->sac[i]);
                assert_int_equal(k,test->sac[i]->forme);
                assert_int_equal(j,test->sac[i]->couleur);
                assert_int_equal(k,test->sac[i+1]->forme);
                assert_int_equal(j,test->sac[i+1]->couleur);
                assert_int_equal(k,test->sac[i+2]->forme);
                assert_int_equal(j,test->sac[i+2]->couleur);
                i=i+3;
        }
    }
}

static void test_melangerSac(void **state)
{
    Partie * test=(Partie*) (*state);
    Partie * verif=(Partie*) (*state);
    melangerSac(test,-1);
    melangerSac(verif,-1);
    int i;
    for(i=0;i<NBTUILESSACMAX;i++)
    {
        assert_int_equal(&verif->sac[i],&test->sac[i]);
    }
}
static void test_verifDoublonsSac(void **state)
{
    Partie * test =(Partie*) (*state);
    assert_int_equal(1,verifDoublonsSac(test));
}

static void test_piocherSac(void **state)
{
    Partie * test =(Partie*) (*state);
    int nbsac=test->nbTuilesSac;
    Tuile * t=test->sac[nbsac-1];
    Tuile * t2=piocherSac(test);
    assert_int_equal(t->couleur,t2->couleur);
    assert_int_equal(t->forme,t2->forme);
    assert_int_equal(nbsac-1,test->nbTuilesSac);
}
static void test_piocherTuiles(void **state)
{
    Partie *test=(Partie*) (*state);
    test->joueurs[test->joueurCourant]->tuilesJoueur[0]=NULL;
    test->joueurs[test->joueurCourant]->tuilesJoueur[1]=NULL;
    piocherTuiles(test);
    assert_int_not_equal(NULL,test->joueurs[test->joueurCourant]->tuilesJoueur[0]);
    assert_int_not_equal(NULL,test->joueurs[test->joueurCourant]->tuilesJoueur[0]);

}
static void test_retournerTuileSac(void **state)
{
    Partie *test=(Partie*) (*state);
    Tuile *tab[6]={NULL};
    int i;
    for(i=0;i<6;i++)
    {
        tab[i]=test->joueurs[test->joueurCourant]->tuilesJoueur[i];
    }
    retournerTuileSac(test,tab);
    int j=5;
    for(i=0;i<6;i++)
    {
        assert_int_equal(tab[i]->couleur,test->sac[test->nbTuilesSac-j-1+i]->couleur);
        assert_int_equal(tab[i]->forme,test->sac[test->nbTuilesSac-j-1+i]->forme);
    }
}
static void test_action_piocher(void **state)
{
     Partie *test=(Partie*) (*state);
     int tab[6]={0,1,1,1,0,1};
     Tuile * tabtuiles[6]={NULL};
     int i;
     for(i=0;i<6;i++)
     {
        tabtuiles[i]=test->joueurs[test->joueurCourant]->tuilesJoueur[i];
     }
     action_piocher(test,tab);
     for(i=0;i<6;i++)
     {
        if(tab[i]!=0)
            assert_int_not_equal(&tabtuiles[i],&(test->joueurs[test->joueurCourant]->tuilesJoueur[i]));
     }
}

int main_test_gestionSac(void)
{
    const struct CMUnitTest test_gestionSac[] =
    {
        cmocka_unit_test_setup_teardown(test_mettreTuilesdanslelot,setup_zero,teardown0et1),
        cmocka_unit_test_setup_teardown(test_genererTuileSac,setup_zero,teardown0et1),
        cmocka_unit_test_setup_teardown(test_piocherSac,setup_un,teardown0et1),
        cmocka_unit_test_setup_teardown(test_verifDoublonsSac,setup_un,teardown0et1),
        cmocka_unit_test_setup_teardown(test_piocherTuiles,setup_deux,teardown2),
        cmocka_unit_test_setup_teardown(test_retournerTuileSac,setup_deux,teardown2),
        cmocka_unit_test_setup_teardown(test_action_piocher,setup_deux,teardown2),
        cmocka_unit_test_setup_teardown(test_melangerSac,setup_un,teardown0et1),
    };
    return cmocka_run_group_tests(test_gestionSac,NULL,NULL);
}


