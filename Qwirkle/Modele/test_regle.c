/*!
* \file test_regles.c
* \brief Fichier contenant les tests unitaires des fonctions nécessaires à la gestion des règles
*
* \author VIAUD Léa
* \version 1.0
* \date 17/03/2020
*
* Dans ce fichier ce trouve les tests des fonctions nécessaires à la gestion des règles
*/


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regle.h"
#include "test.h"



static int setup_regles(void **state)                                     /*!Test unitaire de commencerPartie pour la création du Sac de Tuile dans l'ordre avant le début d'une partie */
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

static void test_criterepose(void **state)
{
    Partie *p=(Partie*) (*state);
    Tuile t1 = createTuile(ROUGE,CERCLE);
    Tuile t3 = createTuile(VERT,CERCLE);
    Tuile t4 = createTuile(BLEU,CERCLE);
    poserTuile( p->plateau,&t1,100,100);
    Tuile *t2= getTuileplateau(p,SELF,100,100);
    assert_int_not_equal(10,critereCouleurForme(p,BAS,t2));
    assert_int_equal(22,critereCouleurForme(p,BAS,t2));

    poserTuile( p->plateau,&t3,101,100);
    poserTuile( p->plateau,&t4,102,100);

    assert_int_not_equal(11,critereCouleurForme(p,BAS,t2));
    assert_int_not_equal(11,critereCouleurForme(p,GAUCHE,t2));
    assert_int_equal(11,critereCouleurForme(p,DROITE,t2));
}

static void test_respectcriterepose(void **state)
{
    Partie *p=(Partie*) (*state);

    Tuile t1 = createTuile(ROUGE,CROIX);
    Tuile t3 = createTuile(VERT,CERCLE);
    Tuile t4 = createTuile(BLEU,CERCLE);
    Tuile t6 = createTuile(BLEU,LOSANGE);
    poserTuile( p->plateau,&t1,100,100);
    poserTuile( p->plateau,&t3,101,100);
    poserTuile( p->plateau,&t4,102,100);
    poserTuile( p->plateau,&t6,103,100);
    Tuile *t2= getTuileplateau(p,SELF,100,100);
    Tuile *t5= getTuileplateau(p,DROITE,100,100);

     assert_int_not_equal(100,respectcriterePose(p,t2,t5,DROITE));
     assert_int_equal(111, respectcriterePose(p,t2,t5,DROITE)); //donc ne respecte pas le critere

     t2= getTuileplateau(p,SELF,101,100);
     t5= getTuileplateau(p,DROITE,101,100);
     assert_int_equal(100,respectcriterePose(p,t2,t5,DROITE));


     t2= getTuileplateau(p,SELF,102,100);
     t5= getTuileplateau(p,GAUCHE,102,100);
     assert_int_equal(222,respectcriterePose(p,t2,t5,GAUCHE));


}
static void test_dejaPosee(void **state)
{
    Partie *p=(Partie*) (*state);

    Tuile t1 = createTuile(BLEU,CERCLE);
    Tuile t3 = createTuile(VERT,CERCLE);
    Tuile t4 = createTuile(BLEU,CERCLE);
    poserTuile( p->plateau,&t1,100,100);
    poserTuile( p->plateau,&t3,99,100);
    poserTuile( p->plateau,&t4,98,100);
    Tuile *t2= getTuileplateau(p,SELF,100,100);

    assert_int_not_equal(0, dejaPosee(p,t2,GAUCHE));
    assert_int_equal(1, dejaPosee(p,t2,GAUCHE));


}

static void  test_isColorFormeCorrect(void **state)
{
    Partie *p=(Partie*) (*state);

    Tuile t1 = createTuile(VERT,LOSANGE);
    Tuile t3 = createTuile(VERT,CARRE);
    Tuile t4 = createTuile(BLEU,CARRE);
    Tuile t5 = createTuile(VERT,CARRE);
    Tuile t6 = createTuile(JAUNE,ETOILE);
    Tuile *t2=NULL;
    poserTuile( p->plateau,&t1,100,100);
    poserTuile( p->plateau,&t3,99,100);
    t2 = getTuileplateau(p,SELF,100,100);
    assert_int_equal(NOERROR, isColorFormeCorrect(p,t2));

    poserTuile( p->plateau,&t4,98,100);
    poserTuile( p->plateau,&t5,99,101);

    t2= getTuileplateau(p,SELF,100,100);
    assert_int_not_equal(NOERROR, isColorFormeCorrect(p,t2));
    assert_int_equal(FORME, isColorFormeCorrect(p,t2));

    t2= getTuileplateau(p,SELF,98,100);
    assert_int_equal(COULEUR, isColorFormeCorrect(p,t2));

    t2= getTuileplateau(p,SELF,99,101);
    assert_int_equal(FORMEetCOULEUR, isColorFormeCorrect(p,t2));

    poserTuile( p->plateau,&t6,100,101);
    t2= getTuileplateau(p,SELF,100,101);
    assert_int_equal(niFORMEniCOULEUR,isColorFormeCorrect(p,t2));

}
static void test_nextDir(void **state)
{
    int i=0;
    assert_int_equal(0,nextDir(i));
    i=3;
    assert_int_not_equal(0,nextDir(i));

}

static void test_hasvoisinTuile(void **state)
{
    Partie *p=(Partie*) (*state);

    Tuile t1 = createTuile(ROUGE,CERCLE);
    placerTuileMilieu(p);
    assert_int_equal(0,hasvoisinTuile(p,100,100));
    poserTuile(p->plateau,&t1,101,100);
    assert_int_equal(1,hasvoisinTuile(p,100,100));

}


static void test_getTuileplateau(void **state)
{
    Partie *p=(Partie*) (*state);

    int x=101,y=100;
    Direction d=SELF;

    assert_null(getTuileplateau(p,d,x,y));
    poserTuile(p->plateau,p->sac[p->nbTuilesSac-1],x,y);
    p->nbTuilesSac--;
    assert_non_null(getTuileplateau(p,d,x,y));
}



static int teardown(void **state)                               //Test unitaire pour free le plateau
{
    freePartie(*state);
    return 0;
}

int main_test_regles(void)
{
    const struct CMUnitTest test_regles[] =
    {
        cmocka_unit_test_setup_teardown(test_getTuileplateau,setup_regles,teardown),
        cmocka_unit_test(test_nextDir),
        cmocka_unit_test_setup_teardown(test_hasvoisinTuile,setup_regles,teardown),
        cmocka_unit_test_setup_teardown(test_criterepose,setup_regles,teardown),
        cmocka_unit_test_setup_teardown(test_respectcriterepose,setup_regles,teardown),
        cmocka_unit_test_setup_teardown(test_dejaPosee,setup_regles,teardown),
        cmocka_unit_test_setup_teardown(test_isColorFormeCorrect,setup_regles,teardown),

    };
    return cmocka_run_group_tests(test_regles,NULL,NULL);
}

