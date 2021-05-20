/**
* \file controleur.h
*
* \brief Fichier contenant le code nécessaire à la gestion du déroulement de la partie
*
* \author DA LAGE Alexis
* \version 1.0
* \date 07/04/2020
*
*
*/

#ifndef CONTROLEUR_H
#define CONTROLEUR_H
#include "../Modele/partie.h"
#include "../Vue/affichage_sdl.h"

typedef struct
{
    SDL_bool key[SDL_NUM_SCANCODES]; //! contient la valeur SDL_TRUE si la touche du clavier à été appuyée, l'indice du tableau correspondant à la touche en question.
    SDL_bool quit; //!sera mis à SDL_TRUE si l'on appuie sur la croix de la fenètre
    SDL_bool retouraction; //! attribut qui sera mis à SDL_TRUE si l'on appuie sur le bouton Retour choix action
    int nbpassesontour; //! compte le nombre de joueur qui appuient consécutivement sur le bouton Passer son tour
    int x, y, xrel, yrel; //! (x,y) la position absolue de la souris   (xrel,yrel) le déplacement de la souris
    int xwheel, ywheel;  //! déplacement de la molette
    SDL_bool mouse[6]; //! contient la valeur SDL_TRUE si le bouton de la souris à été préssé, l'indice du tableau correspondant à la touche en question. exemple :SDL_BUTTON_LEFT=1
} Input;


SDL_Window * init_window();
SDL_Renderer * init_renderer(SDL_Window* window);

void action_joueur(Partie *partie, SDL_Renderer * renderer,Input *input);
void action_piocher_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset);
void action_poser_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset);
void action_quitter_partie(Partie *partie, SDL_Window *window, SDL_Renderer *renderer);
void fin_partie(Partie *partie, SDL_Renderer * renderer);
Input init_input();
void updateEvent(Input *input);

void arrows_rezising_plateau(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset);
void arrows_rezising_posertuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int tabtuilesposees[6],int *xoffset,int *yoffset);
SDL_bool rules_check(Partie *partie, SDL_Renderer * renderer,int tabtuilesposees[6]);

#endif
