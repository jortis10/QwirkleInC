/**
* \file controleur.c
*
* \brief Fichier contenant le code nécessaire à la gestion du déroulement de la partie
*
* \author DA LAGE Alexis
* \version 1.0
* \date 07/04/2020
*
* Dans ce fichier ce trouve l'implémentation des fonctions permettant le déroulement d'une partie
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controleur.h"
#include "../Vue/affichage_sdl.h"
#include "../Modele/score.h"
#include "respectRegles.h"

/**
* \fn SDL_Window * init_window()
* \brief
* Initialise une fenetre de taille 1280x1024
*
* \param[out] un pointeur sur une SDL_Window initialisée
*/
SDL_Window * init_window()
{
    affichage_init(SDL_INIT_VIDEO | SDL_INIT_EVENTS); //! Initialise la SDL2
    initialisation_TTF(); //! Initialise l'écriture du texte


    return createWindow("Qwirkle game",SDL_WINDOWPOS_CENTERED,0,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
}


/**
* \fn SDL_Renderer * init_renderer(SDL_Window* window)
* \brief
* Initialise le renderer associé à la fenetre window et affiche l'écran d'accueil pendant 2 secondes
*
* \param[in] un pointeur sur une SDL_Window initialisée
* \param[out] un pointeur sur un SDL_Renderer initialisé
*/
SDL_Renderer * init_renderer(SDL_Window* window)
{
    SDL_Renderer * renderer = createRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    splashscreen(renderer); //! affiche l'écran d'accueil pendant 2 secondes
    affichageEcran(renderer,"res/main.bmp"); //! affiche l'écran du jeu

    return renderer;
}

/**
* \fn void action_joueur(Partie *partie, SDL_Renderer * renderer,Input *input)
* \brief
*
* \param[in] Partie *partie, SDL_Renderer *renderer Input *input
*
*/


void action_joueur(Partie *partie, SDL_Renderer * renderer,Input *input)
{
    int xoffset=0,yoffset=0;
    int boutonpassertourdispo=0;
    int findepartie=0;
    SDL_Rect textsheet=createFraming(250,24,915,50);
    SDL_Color black= {0,0,0};

    /*! mettre à jour les scores de joueurs affiche_points() rafraichir à chaque fois (attention à ne pas réécrire par dessus + affiche_sac()*/
    //affichageScore(renderer,partie);
    affichageScore_demo(renderer,partie);
    affichage_sac(renderer,partie);

    /*! affichage de la flêche à côté du joueur courant*/
    //affichageJoueurCourant(renderer,partie);
    affichageJoueurCourant_demo(renderer,partie);
    /*! affichage du message "C'est au tour de ..."*/
    char * message=(char*)malloc(50*sizeof(char));
    strcpy(message,"C'est au tour de ");
    strcat(message,getJoueurCourant(partie)->nom);
    strcat(message," de jouer");
    affichage_message(renderer,black,&textsheet,message);
    /*! affichage des fleches de deplacement du plateau */
    affichage_fleches_plateau(renderer);

    /*! Maj du plateau */
    affiche_plateau_17x17(renderer,partie,0,0,SDL_FALSE);

    /*! affiche_main(getJoueurCourant(p));*/
    affiche_main_joueur_courant(renderer,partie);

    /*! mise a jour de l'affichage des boutons pour piocher tuiles, poser tuiles ou passer son tour */
    affiche_poser(renderer);
    if(partie->nbTuilesSac!=0)
    {
        affiche_piocher(renderer);
    }
    else
    {
        affiche_passer_son_tour(renderer);
        boutonpassertourdispo=1;
    }
    /*!Début de la boucle de gestion des Evenements*/
    SDL_bool choixAction = SDL_FALSE;
    while(!choixAction)
    {
        /*! récupère informations de l'état des périphériques */
        updateEvent(input);


        /*! Action si on souhaite quitter le programme en appuyant sur la croix ou échap*/
        if(input->key[SDL_SCANCODE_ESCAPE]==SDL_TRUE || input->quit==SDL_TRUE)
        {
            input->key[SDL_SCANCODE_ESCAPE]=SDL_FALSE;
            input->quit=SDL_FALSE;
            return;   /*! On sort de la boucle action_joueur et on libère la mémoire avant de quitter le programme */
        }



        /*! Action si l'utilisateur clique sur le bouton poser_tuile situé en (1155,505) de taille(100,60)*/

        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1155&&input->x<1155+100&&input->y>505&&input->y<505+60)
        {
            input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
            choixAction = SDL_TRUE;

            action_poser_tuiles(partie, renderer,input,&xoffset,&yoffset);
        }


        /*! Action si l'utilisateur clique sur le bouton piocher_tuile ou passer_son_tour situé en (1155,595) de taille(100,60)*/

        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1155&&input->x<1155+100&&input->y>595&&input->y<595+60)
        {
            input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
            choixAction = SDL_TRUE;
            if(boutonpassertourdispo)
            {
                input->nbpassesontour++;

            }
            else
            {
                action_piocher_tuiles(partie,renderer,input,&xoffset,&yoffset);
            }


        }
        /*! GESTION DES FLECHES DE REDIMENSIONNEMENT DU PLATEAU*/
        arrows_rezising_plateau(partie,renderer,input,&xoffset,&yoffset);


    }
    /*! Si le plateau à été décalé, effacage du plateau de jeu*/
    if(xoffset!=0||yoffset!=0)
    {
        affiche_plateau_17x17(renderer,partie,xoffset,yoffset,SDL_TRUE);
    }

    /*! Vérification si le joueur est sorti de la routine action via le bouton RETOUR CHOIX ACTION (n'a donc pas fini son tour) */

    if(input->retouraction==SDL_TRUE)
    {
        input->retouraction=SDL_FALSE;
        action_joueur(partie,renderer,input);
        return;


    }
    /*! Si le joueur a fini son tour :  */
    /*! Verifier si le joueur a encore des tuiles, sinon fin de partie */

    int vide = 0;
    for(int i=0; i<6; i++)
    {
        if(getJoueurCourant(partie)->tuilesJoueur[i] == NULL)
            vide++;
    }
    if(vide == 6)
    {
        getJoueurCourant(partie)->points += 6;
        findepartie=1;
    }
    /*! si tous les joueurs ont passer leur tour : fin de partie*/
    if(input->nbpassesontour==partie->NbJoueurs)
    {
        findepartie=1;
    }



    if(findepartie)
    {

        /*! Affichage de fin de partie*/
        fin_partie(partie,renderer);
    }
    else
    {
        affichageFinTour(renderer,partie);
        while(!input->mouse[SDL_BUTTON_LEFT])
        {
            updateEvent(input);
        }
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affichageEcran(renderer,"res/main.bmp");
        joueurSuivant(partie);
        action_joueur(partie,renderer,input);
    }

}

/**
* \fn void action_piocher_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset)
* \brief
*
*
* \param[in] Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset
*
*/

void action_piocher_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset)
{
    SDL_Rect textsheet=createFraming(250,24,915,50);
    SDL_Color black= {0,0,0};

    /*! Supression des boutons piocher et poser tuiles */
    supprime_poser(renderer);
    supprime_piocher(renderer);
    /*! Affichage du bouton RETOUR CHOIX ACTION*/
    affiche_bouton_retour(renderer);

    /*! Affichage du message "Selectionne les tuiles que tu veux echanger, puis appuie sur OK"*/


    affichage_message(renderer,black,&textsheet,"Selectionne les tuiles a echanger, puis appuie sur OK");
    /*! Gestion de la selection des tuiles (recuperer l'index des tuiles selectionnées) */
    int tabtuiles[6]= {0,0,0,0,0,0};
    SDL_bool choixOK = SDL_FALSE;
    SDL_bool fin = SDL_FALSE;
    SDL_bool OK = SDL_FALSE;
    int sac=partie->nbTuilesSac;
    int j;
    int afficheOK=0;
    while(!choixOK)
    {
        updateEvent(input);
        /*! Gestion de la selection des tuiles */


        for(j=0; j<6; j++)
        {
            if(input->mouse[SDL_BUTTON_LEFT]&&input->x>(140+j*100)&&input->x<(140+j*100)+100&&input->y>910&&input->y<910+100)
            {
                input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                if(tabtuiles[j]!=1)
                {
                    if(getJoueurCourant(partie)->tuilesJoueur[j]!=NULL&&sac>0)
                    {
                        tabtuiles[j]=1;
                        affichage_selection_tuiles(renderer,j);
                        sac--;
                    }
                }
                else
                {
                    tabtuiles[j]=0;
                    supprime_selection_tuiles(renderer,j);
                    sac++;
                }
            }
        }

        /*! Attendre que le bouton OK soit appuyé */
        for(j=0; j<6; j++)
        {
            if(tabtuiles[j]!=0)
                afficheOK=1;
        }
        if((afficheOK==1))
        {
            if(OK!=SDL_TRUE)
            {
                affiche_bouton_OK(renderer);
                OK=SDL_TRUE;
            }
            if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1050&&input->x<1050+100&&input->y>435&&input->y<435+60)
            {
                input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                choixOK = SDL_TRUE;
                supprime_zonemessage(renderer,&textsheet);

            }
            afficheOK=0;
        }
        else if(afficheOK==0 && OK==SDL_TRUE)
        {
            supprime_bouton_OK(renderer);
            OK=SDL_FALSE;
        }
        /*! Gestion du bouton RETOUR CHOIX ACTION */
        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1155&&input->x<1155+100&&input->y>505&&input->y<505+120)
        {
            input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
            supprime_bouton_retour(renderer);
            supprime_zonemessage(renderer,&textsheet);//! efface la zone de message classique en haut à gauche

            supprime_bouton_OK(renderer); //! supprime le bouton OK
            for(int i=0; i<6; i++)
            {
                if(tabtuiles[i]==SDL_TRUE)
                {
                    supprime_selection_tuiles(renderer,i);
                }
            }
            input->retouraction=SDL_TRUE; //! Donne l'indication à action_joueur qu'il faut relancer le choix de l'action (et non passer au tour du joueur suivant)
            return; //! arrêter la routine de action_piocher_tuiles
        }

        /*! Action si on souhaite quitter le programme en appuyant sur la croix ou échap*/
        if(input->key[SDL_SCANCODE_ESCAPE]==SDL_TRUE || input->quit==SDL_TRUE)
        {

            return;   /*! On sort de la fonction action_piocher_tuiles puis action_joueur pour ensuite libèrer la mémoire avant de quitter le programme */
        }

        /*! GESTION DES FLECHES DE REDIMENSIONNEMENT DU PLATEAU   */
        arrows_rezising_plateau(partie,renderer,input,xoffset,yoffset);


    }
    /*! Gestion lorsque les tuiles ont bien été échangées*/

    /*! Suppression du bouton RETOUR CHOIX ACTION */
    supprime_bouton_retour(renderer);

    /*! Appeller la fonction piocher tuiles, melanger sac etc...*/
    action_piocher(partie,tabtuiles);
    for(j=0; j<6; j++)
    {
        if(tabtuiles[j]!=0)
            supprime_selection_tuiles(renderer,j);
    }
    affiche_main_joueur_courant(renderer,partie);
    affiche_bouton_fin_du_tour(renderer); //! affichage du bouton fin du tour à la place du bouton ok
    affichage_message(renderer,black,&textsheet,"Voici votre main avec les nouvelles tuiles piochees");

    while(!fin)
    {
        updateEvent(input);
        /*! Gestion du bouton fin de tour*/
        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1050&&input->x<1050+100&&input->y>435&&input->y<435+60)
        {
            input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
            fin=SDL_TRUE;
            supprime_bouton_fin_du_tour(renderer);//!suppression du bouton Fin Du Tour lorsque le joueur à cliquer dessus et à terminer de jouer
        }
        /*! Action si on souhaite quitter le programme en appuyant sur la croix ou échap*/
        if(input->key[SDL_SCANCODE_ESCAPE]==SDL_TRUE || input->quit==SDL_TRUE)
        {

            return;   /*! On sort de la fonction action_piocher_tuiles puis action_joueur pour ensuite libèrer la mémoire avant de quitter le programme */
        }

        /*! GESTION DES FLECHES DE REDIMENSIONNEMENT DU PLATEAU   */
        arrows_rezising_plateau(partie,renderer,input,xoffset,yoffset);

    }
    /*! Remise à zero du compteur sur le nombre de joueur qui passe leur tour*/
    input->nbpassesontour=0;

}

/**
* \fn void action_poser_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset);
* \brief
*
* \param[in] Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset
*
*/

void action_poser_tuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset)
{
    SDL_Rect textsheet=createFraming(250,24,915,50);
    SDL_Color black= {0,0,0};


    /*! Supression des boutons piocher et poser tuiles*/
    supprime_poser(renderer);
    supprime_piocher(renderer);
    /*! Affichage du bouton RETOUR CHOIX ACTION*/
    affiche_bouton_retour(renderer);

    /*! Gestion de la pose des tuiles */
    SDL_bool poseNouvelleTuile= SDL_FALSE; //!renseigne si le joueur est au cas 1 (SDL_FALSE) ou au cas 2 (SDL_TRUE)
    int tabtuilesposees[6]= {0,0,0,0,0,0};
    SDL_bool choixfinDuTour = SDL_FALSE;
    SDL_bool boutonFinDuTourDispo = SDL_FALSE;
    SDL_bool boutonFinDuTourPresent = SDL_FALSE;
    SDL_bool boutonOKDispo = SDL_FALSE;
    SDL_bool boutonOKPresent = SDL_FALSE;
    SDL_bool ilyaunetuileprovisoire= SDL_FALSE;
    SDL_bool message_cas1=SDL_FALSE;
    SDL_bool message_cas2=SDL_FALSE;
    SDL_bool changemessage_cas2=SDL_FALSE;
    int indextuilecourante=0;

    /*! LES VARIABLES POUR LES REGLES */
    int Tisok=0;   /*! RECUPERE CE QUE RETOURNE ISTUILECORRECT POUR AFFICHER LE MESSAGE D'ERREUR CORRESPONDANT  */
    SDL_bool wordisOk = SDL_FALSE;   /*! POUR SAVOIR SI LES TUILES DU MOT SONT EPARPILLEES  */
    SDL_bool regleok = SDL_FALSE;   /*! FLAG DES REGLES: POUR SAVOIR SI TUILEISOK ET WORDISOK SONT BONS.  */
    SDL_bool fintourprioritaire = SDL_FALSE;
    SDL_Rect background=createFraming(310,23,920,380);


    while(!choixfinDuTour)  /*! Tant qu'on n'appuie pas sur le bouton FIN DE TOUR */
    {
        updateEvent(input);


        /*! Gestion du bouton RETOUR CHOIX ACTION */
        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1155&&input->x<1155+100&&input->y>505&&input->y<505+120)
        {
            input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
            supprime_bouton_retour(renderer);
            affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //!efface les tuiles provisoires
            supprime_zonemessage(renderer,&textsheet); //! efface la zone de message classique en haut à droite
            affichage_trackingerror(renderer,wordisOk,SDL_FALSE);   //! enleve les messages d'erreur lié a une pose illicite de tuile
            supprime_zonemessage(renderer,&background); //! enleve les messages d'erreur lié a une pose illicite de tuile



            supprime_bouton_OK(renderer); //! supprime le bouton OK ou findetour
            for(int i=0; i<6; i++)
            {

                supprime_selection_tuiles(renderer,i);
            }
            input->retouraction=SDL_TRUE; //! Donne l'indication à action_joueur qu'il faut relancer le choix de l'action (et non passer au tour du joueur suivant)
            return; //! arrêter la routine de action_poser_tuiles
        }

        /*! Séparation des actions à effectuer en deux grands cas*/

        /*! Cas 1 : Le joueur doit selectionner une nouvelle tuile à poser ou deselectionner une tuile déja posée ou appuyer sur finDuTour */

        if(poseNouvelleTuile==SDL_FALSE)
        {
            /*! Gestion de la sélection/déselection d'une tuile*/

            for(int j=0; j<6; j++)
            {
                if(input->mouse[SDL_BUTTON_LEFT]&&input->x>(140+j*100)&&input->x<(140+j*100)+100&&input->y>910&&input->y<910+100)
                {

                    input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                    if(getJoueurCourant(partie)->tuilesJoueur[j]!=NULL)
                    {
                        if(tabtuilesposees[j]==0)
                        {
                            indextuilecourante=j;
                            affichage_selection_tuiles(renderer,j);
                            poseNouvelleTuile=SDL_TRUE;

                        }
                        else
                        {
                            affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //!Efface toutes les tuiles provisoires
                            tabtuilesposees[j]=0;
                            getJoueurCourant(partie)->tuilesJoueur[j]->x=-1;
                            getJoueurCourant(partie)->tuilesJoueur[j]->y=-1;
                            affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //!Affiche les tuiles provisoires sans la tuile deselectionnée
                            affiche_Tisok_message(renderer,Tisok,SDL_FALSE);
                            indextuilecourante=-1;

                            /*! La tuile est deselectionnee: on reverifie si les regles sont quand meme respectees avec les tuiles provisoires restantes)*/

                            indextuilecourante=-1;
                            regleok=rules_check(partie,renderer,tabtuilesposees);
                            if(regleok==SDL_TRUE)
                            {
                                affiche_bouton_fin_du_tour(renderer);
                            }
                            supprime_selection_tuiles(renderer,j);
                        }
                    }
                }
            }
            /*! Gestion de la disponibilité du bouton finDuTour (à compléter avec les règles)*/
            boutonFinDuTourDispo=SDL_FALSE;
            for(int j=0; j<6; j++)
            {
                if(tabtuilesposees[j]==1 && regleok==1)   //! AJOUTER LES CONDITIONS AVEC LES REGLES ICI//
                {
                    boutonFinDuTourDispo=SDL_TRUE;
                }
            }
            /*! Gestion de l'affichage du bouton finDuTour et d'un clic sur lui*/
            if(boutonFinDuTourDispo==SDL_TRUE)
            {
                if(boutonFinDuTourPresent==SDL_FALSE)
                {
                    affiche_bouton_fin_du_tour(renderer);
                    boutonFinDuTourPresent=SDL_TRUE;
                }
                if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1050&&input->x<1050+100&&input->y>435&&input->y<435+60)
                {
                    input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                    choixfinDuTour = SDL_TRUE;
                }
            }

            else
            {
                if(boutonFinDuTourPresent==SDL_TRUE)
                {
                    supprime_bouton_fin_du_tour(renderer);
                    boutonFinDuTourPresent=SDL_FALSE;
                }
            }
            /*! Affichage du message "Clique sur la tuile que tu souhaite poser"*/
            if(message_cas1==SDL_FALSE)
            {
                message_cas2=SDL_FALSE;
                changemessage_cas2=SDL_FALSE;
                affichage_message(renderer,black,&textsheet,"Clique sur la tuile que tu souhaite poser");
                message_cas1=SDL_TRUE;
            }
        }
        /*! Cas 2 : Le joueur doit selectionner un endroit sur le plateau ou deselectionner la tuile ou appuyer sur ok */

        if(poseNouvelleTuile==SDL_TRUE)
        {
            /*! Gestion de la selection de la tuile sur le plateau */

            if(input->mouse[SDL_BUTTON_LEFT]) //! empeche à la boucle de s'activer au moindre événement
            {
                for(int i=0; i<17; i++)
                {
                    for(int j=0; j<17; j++)
                    {
                        if(input->mouse[SDL_BUTTON_LEFT]&&input->x>(20+i*50)&&input->x<(20+50+i*50)&&input->y>(20+j*50)&&input->y<(20+50+j*50))
                        {
                            if(partie->plateau->tuiles[91+i+*xoffset][91+j+*yoffset] == NULL) //! verification qu'il n'y a pas deja une tuile posée à l'endroit souhaité
                            {
                                ilyaunetuileprovisoire=0;
                                for(int k=0; k<6; k++) //! verification qu'il n'y a pas deja une tuile PROVISOIREMENT posée à l'endroit souhaité
                                {
                                    if(tabtuilesposees[k]==1 && getJoueurCourant(partie)->tuilesJoueur[k]->x==91+i+*xoffset+1 && getJoueurCourant(partie)->tuilesJoueur[k]->y==91+j+*yoffset+1)
                                    {
                                        ilyaunetuileprovisoire=1; //! ici on empeche le joueur de poser provisoirement deux tuiles au meme endroit
                                    }
                                }

                                if(!(ilyaunetuileprovisoire))
                                {
                                    input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                                    tabtuilesposees[indextuilecourante]=1;
                                    affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE);//! efface les tuiles provisoires (dont peut etre la tuile provisoire courante dont on souhaite modifier la position)
                                    getJoueurCourant(partie)->tuilesJoueur[indextuilecourante]->x=91+*xoffset+i+1;
                                    getJoueurCourant(partie)->tuilesJoueur[indextuilecourante]->y=91+*yoffset+j+1;
                                    affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE);//! affiche des tuiles provisoires

                                    //!dis au joueur si la position de la tuile est bonne*/
                                    Tisok=isTuileCorrect(partie,tabtuilesposees,indextuilecourante);
                                    affiche_Tisok_message(renderer,Tisok,SDL_TRUE);

                                    boutonOKDispo=SDL_TRUE;
                                    changemessage_cas2=SDL_TRUE;
                                    i=17;
                                    j=17; //!afin de quitter la boucle infernale plus vite
                                }
                            }
                        }
                    }
                }
            }


            /*! Gestion de la déselection de la tuile actuelle*/
            if(input->mouse[SDL_BUTTON_LEFT]&&input->x>(140+indextuilecourante*100)&&input->x<(140+indextuilecourante*100)+100&&input->y>910&&input->y<910+100)
            {
                supprime_selection_tuiles(renderer,indextuilecourante);
                input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                supprime_selection_tuiles(renderer,indextuilecourante);
                supprime_zonemessage(renderer,&background);
                affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //!Efface toutes les tuiles provisoires
                tabtuilesposees[indextuilecourante]=0;
                getJoueurCourant(partie)->tuilesJoueur[indextuilecourante]->x=-1;
                getJoueurCourant(partie)->tuilesJoueur[indextuilecourante]->y=-1;
                affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //!Affiche les tuiles provisoires sans la tuile deselectionnée
                affichage_isregleok(renderer,regleok,SDL_FALSE);

                indextuilecourante=-1;
                regleok=rules_check(partie,renderer,tabtuilesposees);
                if(regleok==SDL_TRUE)
                {
                    fintourprioritaire=SDL_TRUE;
                }
                boutonOKDispo=SDL_FALSE;
                poseNouvelleTuile=SDL_FALSE;

            }
            /*! Gestion de l'affichage du bouton OK et d'un clic sur lui*/

            if(boutonOKDispo==SDL_TRUE)
            {
                if(boutonOKPresent==SDL_FALSE)
                {
                    affiche_bouton_OK(renderer);
                    boutonOKPresent=SDL_TRUE;
                }
                if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1050&&input->x<1050+100&&input->y>435&&input->y<435+60)
                {
                    input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
                    affichage_selection_tuiles_finales(renderer,indextuilecourante);
                    tabtuilesposees[indextuilecourante]=1;
                    poseNouvelleTuile=SDL_FALSE;
                    supprime_bouton_OK(renderer);
                    supprime_zonemessage(renderer,&background);
                    /*! Gestion des regles une fois que le joueur appuie sur le bouton OK*/
                    indextuilecourante=-1;
                    regleok=rules_check(partie,renderer,tabtuilesposees);
                    boutonFinDuTourDispo=SDL_FALSE;
                    boutonOKPresent=SDL_FALSE;
                    boutonOKDispo=SDL_FALSE;
                }
            }

            else
            {
                if(boutonOKPresent==SDL_TRUE && fintourprioritaire==SDL_FALSE)
                {
                    supprime_bouton_OK(renderer);
                    boutonOKPresent=SDL_FALSE;
                }
                else
                {
                    fintourprioritaire=SDL_FALSE;
                }
            }
            /*! Affichage du 1er message "Clique sur le plateau pour poser la tuile"*/
            if(message_cas2==SDL_FALSE&&changemessage_cas2==SDL_FALSE)
            {
                message_cas1=SDL_FALSE;
                affichage_message(renderer,black,&textsheet,"Clique sur le plateau pour poser la tuile");
                message_cas2=SDL_TRUE;
            }
            /*! Affichage du 2eme message "Appuie sur OK quand c'est bon"*/
            if(message_cas2==SDL_TRUE&&changemessage_cas2==SDL_TRUE)
            {
                message_cas2=SDL_FALSE;
                affichage_message(renderer,black,&textsheet,"Appuie sur OK quand c'est bon");

            }
            boutonFinDuTourDispo=SDL_FALSE;
        }


        /*! Action si on souhaite quitter le programme en appuyant sur la croix ou échap*/
        if(input->key[SDL_SCANCODE_ESCAPE]==SDL_TRUE || input->quit==SDL_TRUE)
        {
            return;   /*! On sort de la fonction action_piocher_tuiles puis action_joueur pour ensuite libèrer la mémoire avant de quitter le programme */
        }


        /*! GESTION DES FLECHES DE REDIMENSIONNEMENT DU PLATEAU   */

        arrows_rezising_posertuiles(partie,renderer,input,tabtuilesposees,xoffset,yoffset);

    }
    /*! APRES APPUI SUR BOUTON FIN DE TOUR */

    /*! Suppression du bouton RETOUR CHOIX ACTION */
    supprime_bouton_retour(renderer);
    /*! Remise à zero du compteur sur le nombre de joueur qui passe leur tour*/
    input->nbpassesontour=0;



    /*! Appeller la fonction poser tuiles, piocherTuiles  etc...*/
    majPoints(partie,tabtuilesposees);
    for(int i=0; i<6; i++)
    {
        if(tabtuilesposees[i]==SDL_TRUE)
        {
            poserTuile(partie->plateau,getJoueurCourant(partie)->tuilesJoueur[i],getJoueurCourant(partie)->tuilesJoueur[i]->x,getJoueurCourant(partie)->tuilesJoueur[i]->y);
            getJoueurCourant(partie)->tuilesJoueur[i] = NULL;
        }
        piocherTuiles(partie);

    }

    /*! ne pas oublier d'effacer la zone de message ,les tuiles provisoires, le bouton FinDuTour et les fleches de selection des tuiles */
    supprime_zonemessage(renderer,&textsheet);
    supprime_zonemessage(renderer,&background);
    affichage_isregleok(renderer,regleok,SDL_FALSE);
    affichage_trackingerror(renderer,wordisOk,SDL_FALSE);

    supprime_bouton_fin_du_tour(renderer);
    for(int i=0; i<6; i++)
    {
        if(tabtuilesposees[i]==SDL_TRUE)
        {
            supprime_selection_tuiles(renderer,i);
        }
    }

    /*! Remise à zero du compteur sur le nombre de joueur qui passe leur tour*/
    input->nbpassesontour=0;
}


/**
* \fn void action_quitter_partie(Partie *partie, SDL_Window *window, SDL_Renderer *renderer)
* \brief
*
* \param[in] Partie *partie, SDL_Window *window, SDL_Renderer *renderer
*
*/


void action_quitter_partie(Partie *partie, SDL_Window *window, SDL_Renderer *renderer)
{



    /*! Tout les free*/
    TTF_Quit();
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    freePartie(partie);

    /*! A completer*/

}


/**
* \fn Input init_input()
* \brief
* Fonction qui permet d'initialiser Input
*
* \param[out] Input input : une instance d'Input avec ses attributs initialisés à SDL_FALSE
*
*/

Input init_input()
{
    Input input;
    for(int i=0; i<SDL_NUM_SCANCODES; i++)
    {
        input.key[i]=SDL_FALSE;
    }
    input.quit=0;
    input.nbpassesontour=0;
    input.retouraction=0;
    input.x=0;
    input.y=0;
    input.xrel=0;
    input.yrel=0;
    input.xwheel=0;
    input.ywheel=0;

    for(int i=0; i<6; i++)
    {
        input.mouse[i]=SDL_FALSE;
    }

    input.mouse[SDL_BUTTON_LEFT]=SDL_FALSE; //

    return input;
}

/**
* \fn void arrows_rezising_plateau(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset)
* \brief permet de redimensionner le plateau de jeu grace aux fleches (seulement les tuiles réellement posées sur le plateau)

* \param[in] Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset
*\param[out]  none
*/
void arrows_rezising_plateau(Partie *partie, SDL_Renderer * renderer,Input *input,int *xoffset,int *yoffset)
{


    /*! Deplacement du plateau avec la fleche du haut situé en (980,510) de taille(38,58) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>980&&input->x<980+38&&input->y>510&&input->y<510+58)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        (*yoffset)--;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }

    /*! Deplacement du plateau avec la fleche du bas situé en (980,590) de taille(38,58) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>980&&input->x<980+38&&input->y>590&&input->y<590+58)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        (*yoffset)++;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }
    /*! Deplacement du plateau avec la fleche de gauche situé en (930,560) de taille(58,38) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>930&&input->x<930+58&&input->y>560&&input->y<560+38)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        (*xoffset)--;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé

    }
    /*! Deplacement du plateau avec la fleche de droite situé en (1010,560) de taille(58,38) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1010&&input->x<1010+58&&input->y>560&&input->y<560+38)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        (*xoffset)++;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }


}


/**
* \fn void arrows_rezising_posertuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int tabtuilesposees[6],int *xoffset,int *yoffset)
* \brief permet de redimensionner le plateau grace aux fleches lorsque le joueur decide de poser ses tuiles
* La fonction deplace à la fois les tuiles du plateau ET les tuiles provisoirement posées

* \param[in] Partie *partie, SDL_Renderer * renderer,Input *input,int tabtuilesposees[6],int *xoffset,int *yoffset
*\param[out]  none
*/
void arrows_rezising_posertuiles(Partie *partie, SDL_Renderer * renderer,Input *input,int tabtuilesposees[6],int *xoffset,int *yoffset)
{
    /*! Deplacement du plateau avec la fleche du haut situé en (980,510) de taille(38,58) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>980&&input->x<980+38&&input->y>510&&input->y<510+58)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //! efface les tuiles provisoires
        (*yoffset)--;
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //! affiche les tuiles provisoires
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }

    /*! Deplacement du plateau avec la fleche du bas situé en (980,590) de taille(38,58) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>980&&input->x<980+38&&input->y>590&&input->y<590+58)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //! efface les tuiles provisoires
        (*yoffset)++;
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //! affiche les tuiles provisoires
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }

    /*! Deplacement du plateau avec la fleche de gauche situé en (930,560) de taille(58,38) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>930&&input->x<930+58&&input->y>560&&input->y<560+38)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //! efface les tuiles provisoires
        (*xoffset)--;
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //! affiche les tuiles provisoires
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé

    }

    /*! Deplacement du plateau avec la fleche de droite situé en (1010,560) de taille(58,38) */

    if(input->mouse[SDL_BUTTON_LEFT]&&input->x>1010&&input->x<1010+58&&input->y>560&&input->y<560+38)
    {
        input->mouse[SDL_BUTTON_LEFT]=SDL_FALSE;
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_TRUE); //! efface le plateau existant
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_TRUE); //! efface les tuiles provisoires
        (*xoffset)++;
        affiche_tuiles_provisoires_17x17(renderer,partie,tabtuilesposees,*xoffset,*yoffset,SDL_FALSE); //! affiche les tuiles provisoires
        affiche_plateau_17x17(renderer,partie,*xoffset,*yoffset,SDL_FALSE);//! affiche le plateau décalé
    }


}

/**
* \fn SDL_bool rules_check(Partie *partie, SDL_Renderer * renderer,int tabtuilesposees[6])

* \brief verifie si les regles sont respectées lorsque le joueur fait une action dans action posertuiles
*
* \param[in] Partie *partie, SDL_Renderer * renderer,int tabtuilesposees[6]
*\param[out]  regleok=1 si les regles sont respectées ,0 sinon
*/


SDL_bool rules_check(Partie *partie, SDL_Renderer * renderer,int tabtuilesposees[6])
{
    int Tisok,Wok;
    SDL_bool wordisOk=SDL_FALSE, tuileisOk=SDL_FALSE, regleok=SDL_FALSE;


    Tisok=isTuileCorrect2(partie,tabtuilesposees);
    if(Tisok==0)
    {
        tuileisOk=SDL_TRUE;
    }
    else
    {
        tuileisOk=SDL_FALSE;
    }


    Wok=isWordCorrect(partie,tabtuilesposees);
    if(Wok==1)
    {
        wordisOk=SDL_TRUE;
        affichage_trackingerror(renderer,wordisOk,SDL_FALSE);
    }
    else
    {
        wordisOk=SDL_FALSE;
        if(Wok==0)
        {
            affichage_trackingerror(renderer,wordisOk,SDL_TRUE);
        }
    }

    if(wordisOk==SDL_TRUE &&  tuileisOk==SDL_TRUE)
    {
        regleok=SDL_TRUE;
        affiche_bouton_fin_du_tour(renderer);
    }
    else
    {
        regleok = SDL_FALSE;
    }

    if(istabtuilesVide(tabtuilesposees)==1)
    {
        affichage_isregleok(renderer,regleok,SDL_FALSE);
        supprime_bouton_fin_du_tour(renderer);
    }
    else
    {
        affichage_isregleok(renderer,regleok,SDL_TRUE);
    }


    return regleok;
}






/**
* \fn void updateEvent(Input *input)
* \brief
*
* \param[in] Input *input : un pointeur sur la structure input où l'on va stocker les informations sur les périphériques
*
*/


void updateEvent(Input *input)
{
    SDL_Event event;
    SDL_WaitEvent(&event);

    if(event.type == SDL_QUIT)
        input->quit = SDL_TRUE;
    if(event.type == SDL_KEYDOWN)
        input->key[event.key.keysym.scancode] = SDL_TRUE;
    if(event.type == SDL_KEYUP&&event.key.keysym.scancode!=SDL_SCANCODE_ESCAPE) //! Condition faite pour conserver la touche echap préssée virtuellement meme apres passage dans cette fonction
        input->key[event.key.keysym.scancode] = SDL_FALSE;
    if(event.type == SDL_MOUSEMOTION)
    {
        input->x = event.motion.x;
        input->y = event.motion.y;
        input->xrel = event.motion.xrel;
        input->yrel = event.motion.yrel;
    }
    if(event.type == SDL_MOUSEWHEEL)
    {
        input->xwheel = event.wheel.x;
        input->ywheel = event.wheel.y;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN)
        input->mouse[event.button.button] = SDL_TRUE;
    if(event.type == SDL_MOUSEBUTTONUP)
        input->mouse[event.button.button] = SDL_FALSE;
}

/**
* \fn void fin_partie(Partie *partie, SDL_Renderer * renderer)
* \brief Gère la fin de partie
*
* \param[in] Partie *partie, SDL_Renderer * renderer
*
*/

void fin_partie(Partie *partie, SDL_Renderer * renderer)
{

    //! Affichage de l'écran des scores

    affichageFin(renderer,partie);
    SDL_Delay(5000);

}
