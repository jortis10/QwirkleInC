/**
* \file message.c
*
* \brief Fichier contenant le code nécessaire à l'affichage console des messages dans le jeu
*
* \author DA LAGE Alexis
* \version 1.0
* \date 05/03/2020
*
* Dans ce fichier ce trouvent le code des fonctions servant à afficher les messages en console
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "../Vue/affichage_plateau.h"
#include "../Modele/regle.h"
/**
* \fn void message_bienvenue()
* \brief Envoie du message de bienvenue
*
* La fonction s'ecrire un message de bienvenue en console
*
*/
void message_bienvenue()
{
    printf("\033[05m\033[44mBienvenue dans le jeu Qwirkle version 1.0\033[0m\033[0m\n");
    waitEnter();
    clear_console();

}

/**
* \fn void message_action_joueur(Partie *p)
* \brief Envoie du message de bienvenue
*
* La fonction s'ecrire un message de bienvenue en console
* \param[in] Partie *p
*/

void message_action_joueur(Partie *p)
{

    int action1 =0; int poseOK=1;

    printf("C'est au tour de : %s \n",getJoueurCourant(p)->nom);
    affiche_points(getJoueurCourant(p));

do{ waitEnter();
    if(poseOK!=1){waitEnter();}
    clear_console();
    if(poseOK!=1){
    printf("\n\033[44m %s le mot que vous venez de jouer etait INCORRECT: veuillez rejouer  \033[0m\n \n",getJoueurCourant(p)->nom);}
    affiche_plateau(p->plateau);
    affiche_main(getJoueurCourant(p));

    printf("Veux tu jouer (1) ou piocher des nouvelles tuiles dans le sac (2) ?\n");
    while(action1!=1&&action1!=2)
    {
        scanf("%d",&action1);
    }
    //clear_console();
    if(action1==1)
    {
        poseOK=message_poser_tuiles(p);
       if(poseOK!=1){action1=0;}
    }

    if(action1==2)
    {
        message_piocher_tuiles(p);
        affiche_main(getJoueurCourant(p));

    }
   }while((action1==0) && (poseOK!=1));

    affiche_points(getJoueurCourant(p));
    waitEnter();
    waitEnter();

    clear_console();
    joueurSuivant(p);
    if(p->nbTuilesSac<70){
    message_fin_de_partie(p);
    }else{
    message_action_joueur(p);}
}

/**
* \fn void message_piocher_tuiles(Partie *p)
* \brief Message suite au choix de l'action "Piocher tuiles"
*
* La fonction demandera combien de tuile le joueur souhaitera echanger avec la pioche (De 1 à 6), quelles tuiles veut il échanger et ensuite finira le tour du joueur courant
* le joueur courant aura donc de nouveau 6 tuiles en main avec les nouvelles qu'il vient de piocher
* \param[in] Partie * p
*/

void message_piocher_tuiles(Partie *p)
{
    int i,nbtuiles =0;
    int index_tuile=0;
    do{
    printf("Combien de tuiles veux-tu echanger ?\n");
    scanf("%d",&nbtuiles);
    if(nbtuiles<1)
    {
        printf("Vous devez échanger au moins 1 tuile\n");
    }
    else if(nbtuiles>6)
    {
        printf("Vous ne pouvez pas échanger plus de 6 tuiles !\n");
    }
    }while(nbtuiles<1 || nbtuiles>6 );
    i=0;
    while(i<nbtuiles && p->nbTuilesSac>0)
     {
        do{printf("Quelle tuile veux tu échanger ?");
        scanf("%d",&index_tuile);
       if(index_tuile < 1 || index_tuile >6){printf("Erreur : cette tuile n'existe pas ! \n");}

       }while(index_tuile < 1 || index_tuile >6);

        if(p->nbTuilesSac>0)
        {
            retournerTuileSac(p,index_tuile);
            melangerSac(p);
            piocherTuiles(p);
        }
        else
            {printf("Il n'y a plus de Tuile dans le sac");}
            i++;
        }

}

/**
* \fn void message_poser_tuiles(Partie *p)
* \brief Message suite au choix de l'action "Poser tuiles"
*
* La fonction demandera quelle tuile le joueur souhaite poser sur le plateau
* ainsi l'endroit ou le joueur souhaite placer la tuile
* \param[in] Partie * p
*/
int message_poser_tuiles(Partie *p)
{

// int i,xplateau,yplateau;
    int ind=1;int tuiledejapose=0;
    int ntuile = 0;
    int nbtuile = 0;
    int x,k,y = 0;
    int Wisok=0;
    int Tisok=0,Tisok_ind=1;
    int tabtuiles[6]={0,0,0,0,0,0};
    Tuile *tuilesposees;
    int *tabnumtuile;

    do
    {
        printf("Combien de tuiles veux-tu poser ?\n");
        scanf("%d",&nbtuile);

        if(nbtuile < 1 || nbtuile >6)
            printf("Erreur : cette tuile n'existe pas ! \n");

    }while(nbtuile < 1 || nbtuile > 6);
    tuilesposees=(Tuile*)malloc(nbtuile*sizeof(Tuile));
    tabnumtuile=(int*)malloc(nbtuile*sizeof(int));
    for(k = 0; k < nbtuile; k++)
    {
        do
        {
            tuiledejapose=0;
            printf("Quelle tuile veux-tu poser ? (1 à 6) \n");
            scanf("%d",&ntuile);
            if((ntuile < 1) || (ntuile > 6))
                printf("Erreur : On ne peux pas poser cette tuile !");
            if(tabtuiles[ntuile-1]==1){tuiledejapose=1;printf("Vous avez deja pose cette tuile \n");}

        }
        while ((ntuile < 1) || (ntuile > 6) || (tuiledejapose==1));

       do {
        printf("Dans quelle case veux-tu poser la tuile ? (x et y)\n");
        scanf("%d",&x);
        scanf("%d",&y);
        Tisok=isTuileCorrect(p,x,y,ntuile); if(Tisok>1){Tisok_ind=0;}
       }while(Tisok==1);

        tabtuiles[ntuile-1]=1;
        poserTuile(p->plateau,getJoueurCourant(p)->tuilesJoueur[ntuile-1],x,y);

        tuilesposees[k]=*getTuileplateau(p,SELF,x,y);
        tabnumtuile[k]=ntuile-1;

        modifieZonedeJeu(p->plateau);
        printf("On pose la tuile à la position (%d,%d) \n",x,y);
        getJoueurCourant(p)->tuilesJoueur[ntuile-1] = NULL;
   }
   Wisok=isWordCorrect(tuilesposees,nbtuile);
   if(Wisok==1 && Tisok_ind==1){  ind=1;printf("\n--------------\n"); printf("le mot est correct"); printf("\n-------------- \n");
     majPointsV0(p,tabtuiles);  melangerSac(p); piocherTuiles(p);

     }

   else
   { ind=0; printf("\n--------------\n"); printf("le mot est INCORRECT"); printf("\n-------------- \n");
     annuler_action_poser_tuiles(p,nbtuile,tuilesposees,tabnumtuile);
   }

    free(tuilesposees); free(tabnumtuile);
    return ind;
}

/**
* \fn waitEnter()
* \brief Fonction qui arrête le programme jusqu'à ce que l'utilisateur appuie sur Entrée
*
* Fonction qui arrête le programme jusqu'à ce que l'utilisateur appuie sur Entrée
*/


void waitEnter()
{
    while(getchar()!='\n')
    {

    }
}

/**
* \fn void message_fin_de_partie(Partie *p)
* \brief Message de fin de partie déclenché lorsque la partie est terminée
*
* La fonction présentera à l'utilisateur le gagnant, les points de chacun des joueurs et proposera à
* l'utilisateur de lancer une nouvelle partie ou de quitter le jeu.
*
* Cette fonction doit également libérer la mémoire allouée dynamiquement de la partie précédente
* \param[in] Partie * p
*/

void message_fin_de_partie(Partie *p)
{
    waitEnter();
    clear_console();
    int valeurmax=0;
    int index_gagnant=0;
    for(int i=0; i<p->NbJoueurs; i++)
    {
        if(p->joueurs[i]->points>valeurmax)
        {
            valeurmax=p->joueurs[i]->points;
            index_gagnant=i;
        }

    }
    printf("Le gagnant de cette incroyable partie est");
    waitEnter();
    clear_console();
    printf("Le gagnant de cette incroyable partie est.");
    waitEnter();
    clear_console();
    printf("Le gagnant de cette incroyable partie est..");
    waitEnter();
    clear_console();
    printf("Le gagnant de cette incroyable partie est...");
    waitEnter();
    clear_console();
    int nomjoueurlength=strlen(p->joueurs[index_gagnant]->nom);
    printf("\033[05m\033[42m==================>\033[0m\033[0m       ");
    for(int i=0; i<nomjoueurlength; i++)
        printf(" ");
    printf("       \033[05m\033[42m<==================\033[0m\033[0m\n");

    printf("\033[05m\033[42m==================>\033[0m\033[0m       \033[32m%s\033[0m       \033[05m\033[42m<==================\033[0m\033[0m\n",p->joueurs[index_gagnant]->nom);

    printf("\033[05m\033[42m==================>\033[0m\033[0m       ");
    for(int i=0; i<nomjoueurlength; i++)
        printf(" ");
    printf("       \033[05m\033[42m<==================\033[0m\033[0m\n");

    waitEnter();
    clear_console();
    printf("Veux tu relancer une nouvelle partie (1) ou quitter le jeu (2) ? \n");
    int choix=0;
    scanf("%d",&choix);
    if(choix==1)
    {
        Partie * p=CommencerPartie(3);
        message_action_joueur(p);
    }
    else
    {
        clear_console();
        //freePartie(p);
        printf("Merci d'avoir joué au jeu ! A bientôt !");
    }
}


