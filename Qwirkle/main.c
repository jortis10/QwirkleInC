/**
* \file main.c
*
* \brief Fichier contenant le main de notre projet Qwirkle
*
* \author VIAUD Lea
* \version 1.0
* \date 17/02/2020
*
* Dans ce fichier ce trouve le main permettant de lancer une partie de jeu Qwirkle.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "Modele/tuile.h"
#include "Modele/joueur.h"
#include "Modele/partie.h"
#include "Modele/plateau.h"
#include "Modele/test.h"
#include "Controleur/message.h"
#include "Vue/affichage_sdl.h"
#include "Controleur/controleur.h"



int main(int argc, char* argv[])
{

    /*! Initialisation des données du Modèle */
   Partie * partie= CommencerPartie(4);

    /*! Initialisation de l'affichage */
   SDL_Window * window = init_window();
   SDL_Renderer * renderer =init_renderer(window);

     /*! Initialisation de la structure stockant l'état des périphériques */
  Input input=init_input();

    /*! Début de la routine de jeu */
   action_joueur(partie,renderer,&input);

    /*! Libération de la mémoire allouée une fois que le joueur à decider de quitter le jeu Qwirkle et fin de partie*/

   action_quitter_partie(partie,window,renderer);


   /*! Main des tests unitaires */

     main_test_regles();
     main_test_gestionSac();
     main_test_joueur();
     main_test_plateau();
     main_test_tuile();
     main_test_score();
     main_test_partie();

    return 0;
}
