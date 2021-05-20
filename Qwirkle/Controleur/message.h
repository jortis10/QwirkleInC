/**
* \file message.h
*
* \brief Fichier contenant le code nécessaire à l'affichage des messages en console
*
* \author DA LAGE Alexis
* \version 1.0
* \date 05/03/2020
*
* Dans ce fichier ce trouvent les prototypes des fonctions basiques servant à afficher des messages dans la console
*/

#ifndef MESSAGE_H
#define MESSAGE_H
#include "../Modele/tuile.h"
#include "../Modele/plateau.h"
#include "../Modele/partie.h"
#include "../Modele/score.h"

void message_bienvenue();  /*!< Message au debut du jeu dans la console */
void message_action_joueur(Partie *p); /*!< Message indiquant quel joueur doit jouer et quelles actions il peut effectuer */
int message_poser_tuiles(Partie *p); /*!< Message suite au choix de l'action "Poser tuiles" */
void message_piocher_tuiles(Partie *p); /*!< Message suite au choix de l'action "Piocher tuiles" */
void waitEnter(); /*!< Fonction qui arrête le programme jusqu'à ce que l'utilisateur appuie sur Entrée */
void message_fin_de_partie(Partie *p); /*!< Message de fin de partie déclenché lorsque la partie est terminée */

#endif

