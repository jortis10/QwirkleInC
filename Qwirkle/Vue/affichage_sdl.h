/**
* \file affichage.h
*
* \brief Fichier contenant le code nécessaire à l'affichage graphique (SDL2) du programme
*
* \author JENNY Thibaud
* \version 1.0
* \date 27/03/2020
*
* Dans ce fichier ce trouvent le code des fonctions servant à afficher le programme graphique
*/

#ifndef AFFICHAGE_GRAPHIQUE_H
#define AFFICHAGE_GRAPHIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Modele/tuile.h"
#include "../Modele/partie.h"

#define DELAY 7000
#define HEIGHT 1024
#define WIDTH 1280


int affichage_init(int flag);
SDL_Window* createWindow(char* titre, int flag1, int flag2,int hauteur,int largeur,int flag3);
SDL_Renderer* createRenderer(SDL_Window* window,int index,int flag);
void affichage_pause(int delay);
SDL_Texture* loadImage(SDL_Renderer* renderer,char* image);
SDL_Texture* loadTuilefromData(Tuile * t,int x,int y,int taille, SDL_Renderer* renderer);
void splashscreen(SDL_Renderer *renderer);
int initialisation_TTF(void);
SDL_Texture* createTexture(SDL_Renderer* renderer,SDL_Surface* surface);
TTF_Font* setPolice(char* font, int tailledepolice);
int writeThis(SDL_Renderer* renderer,SDL_Texture* textureTexte,TTF_Font *police, char* texte, SDL_Color couleurTexte, SDL_Rect* encadrementtexte);
SDL_Rect createFraming(int width, int height, int x,int y);

void affichageScore(SDL_Renderer* renderer,Partie *p);
void affichageScore_demo(SDL_Renderer* renderer,Partie *p); //Affiche score optimise pour 4 joueurs max
void affichageEcran(SDL_Renderer* renderer,char* imagedefond);
void affichage_sac(SDL_Renderer *renderer,Partie *p);
void affiche_plateau_17x17(SDL_Renderer *renderer,Partie *partie,int xoff,int yoff,SDL_bool clearTiles);
void affiche_tuiles_provisoires_17x17(SDL_Renderer *renderer,Partie *partie,int tabtuilesprovisoires[6],int xoff,int yoff,SDL_bool clearTiles);
void affiche_main_joueur_courant(SDL_Renderer *renderer,Partie *partie);
void affichageJoueurCourant(SDL_Renderer *renderer,Partie *partie);
void affichageJoueurCourant_demo(SDL_Renderer *renderer,Partie *partie);//Affichejoueurcourant optimisé pour 4 joueurs max
void affichageFin(SDL_Renderer* renderer,Partie* p);
void affichageFinTour(SDL_Renderer * renderer, Partie *p);


void affiche_bouton_OK(SDL_Renderer *renderer);
void supprime_bouton_OK(SDL_Renderer *renderer);
void affiche_bouton_fin_du_tour(SDL_Renderer *renderer);
void supprime_bouton_fin_du_tour(SDL_Renderer *renderer);
void affiche_bouton_retour(SDL_Renderer *renderer);
void supprime_bouton_retour(SDL_Renderer *renderer);
void affiche_poser(SDL_Renderer *renderer);
void affiche_piocher(SDL_Renderer *renderer);
void supprime_piocher(SDL_Renderer *renderer);
void supprime_poser(SDL_Renderer *renderer);
void affiche_passer_son_tour(SDL_Renderer *renderer);

void affichage_selection_tuiles(SDL_Renderer * renderer,int j);
void affichage_selection_tuiles_finales(SDL_Renderer * renderer,int j);
void supprime_selection_tuiles(SDL_Renderer * renderer,int j);


void affichage_fleches_plateau(SDL_Renderer* renderer);


//LES MESSAGES
void affichage_isregleok(SDL_Renderer *renderer,SDL_bool regleok,SDL_bool showmessage);
void affiche_Tisok_message(SDL_Renderer *renderer,int i,SDL_bool showmessage);
void affichage_trackingerror(SDL_Renderer *renderer,SDL_bool iswordokaligned,SDL_bool showmessage);
void affichage_message(SDL_Renderer *renderer,SDL_Color couleur,SDL_Rect *background,char* message);
void supprime_zonemessage(SDL_Renderer *renderer,SDL_Rect *background);


#endif // AFFICHAGE_GRAPHIQUE_H
