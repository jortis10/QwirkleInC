/**
* \file affichage_sdl.c
*
* \brief Fichier contenant le code nécessaire à l'affichage graphique (SDL2) du programme
*
* \author JENNY Thibaud & SOW Aicha
* \version 2.0
* \date 10/05/2020
*
* Dans ce fichier se trouve le code des fonctions de l'interface graphique
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "affichage_sdl.h"


/**
* \fn int affichage_init(int flag)
* \brief initialisation de la bibliotheque SDL2 avec les flags d'initialisation
* \param[in] int flag
* \param[out] int EXIT_FAILURE si erreur , EXIT_SUCCESS sinon
*/


int affichage_init(int flag)
{

    if(SDL_Init(flag)!= 0)
    {

        fprintf(stderr,"Erreur SDL_Init : %s\n",SDL_GetError());
        SDL_Log("Init SDL : Failure\n");
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Log("Init SDL2 : Success\n");
    return EXIT_SUCCESS;
}


/**
* \fn int initialisation_TTF(void)
* \brief initialisation de la bibliotheque SDL2_ttf
* \param[in] none
* \param[out] int EXIT_FAILURE si erreur , EXIT_SUCCESS sinon
*/


int initialisation_TTF(void)
{
    if(!TTF_WasInit() && TTF_Init()==-1)
    {
        fprintf(stderr,"Erreur TTF_Init : %s\n",TTF_GetError());
        SDL_Log("Init TTF : Failure\n");
        TTF_Quit();
        return EXIT_FAILURE;
    }
    SDL_Log("Init TTF: Success\n");
    return EXIT_SUCCESS;

}


/**
* \fn SDL_Window* createWindow(char* titre, int flag1, int flag2,int largeur,int hauteur,int flag3)
* \brief la fonction permet de creer une fenetre graphique avec les flags requis
* \param[in] char* titre, int flag1, int flag2,int largeur,int hauteur,int flag3
* \param[out] SDL_Window* window
*/


SDL_Window* createWindow(char* titre, int flag1, int flag2,int largeur,int hauteur,int flag3)
{
    SDL_Window *window = SDL_CreateWindow(titre,flag1,flag2,largeur,hauteur,flag3);

    if(window == NULL)
    {
        fprintf(stderr,"Erreur SDL_createWindow : %s\n",SDL_GetError());
        SDL_Log("Create Window : Failure\n");
        SDL_DestroyWindow(window);
        return NULL;
    }
    SDL_Log("Create Window : Success\n");
    return window;
}


/**
* \fn SDL_Renderer* createRenderer(SDL_Window* window,int index,int flag)
* \brief la fonction permet de creer le renderer de la fenetre window
* \param[in] SDL_Window* window,int index,int flag
* \param[out] SDL_Renderer* renderer
*/


SDL_Renderer* createRenderer(SDL_Window* window,int index,int flag)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(window,index,flag);
    if(renderer == NULL)
    {
        fprintf(stderr,"Erreur SDL_createRender: %s\n",SDL_GetError());
        SDL_Log("Create Renderer : Failure\n");
        SDL_DestroyRenderer(renderer);
        return NULL;
    }
    SDL_Log("Create Renderer : Sucess\n");
    return renderer;
}


/**
* \fn void affichage_pause(int delay)
* \brief la fonction permet de mettre le programme en pause
* \param[in] int delay // temps de pause en ms
* \param[out] none
*/


void affichage_pause(int delay)
{
    SDL_Log("Delay of %d s\n",delay/1000);
    SDL_Delay(delay);
}


/**
* \fn SDL_Texture* createTexture(SDL_Renderer* renderer,SDL_Surface* surface)
* \brief la fonction permet de creer une texture a partir d'une surface
* \param[in] SDL_Renderer* renderer,SDL_Surface* surface
* \param[out] SDL_Texture* texture
*/


SDL_Texture* createTexture(SDL_Renderer* renderer,SDL_Surface* surface)
{

    SDL_Texture* texture = NULL;
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);                                           //affichage_destroy(NULL,NULL,surface,NULL)
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        SDL_Log("Create Texture : Failure\n");
        SDL_DestroyTexture(texture);
        return NULL;
    }
    SDL_Log("Create Texture : Success \n");

    return texture;

}


/**
* \fn SDL_Texture* loadImage(SDL_Renderer* renderer,char* image)
* \brief la fonction permet de charger une image BMP
* \param[in] SDL_Renderer* renderer,char* image
* \param[out] SDL_Texture* texture
*/


SDL_Texture* loadImage(SDL_Renderer* renderer,char* image)
{
    SDL_Surface* surface_img = NULL;
    surface_img = SDL_LoadBMP(image);

    if(NULL == surface_img)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        SDL_Log("Load Bitmap %s : Failure\n",image);
        SDL_FreeSurface(surface_img);
        return NULL;
    }
    SDL_Texture* texture =createTexture(renderer,surface_img);

    if(NULL!=texture)
    {
        SDL_Log("Load %s : Success\n",image);
    }
    return texture;
}


/**
* \fn SDL_Rect createFraming(int width, int height, int x,int y)
* \brief la fonction permet d'avoir le framing ou delimitation
       afin de restreindre l'ecriture d'un texte ou l'affiche d'une image au framing souhaité
* \param[in] int width, int height, int x,int y
* \param[out] SDL_Rect framing
*/


SDL_Rect createFraming(int width, int height, int x,int y)
{
    SDL_Rect framing;

    framing.w =width;
    framing.h =height;
    framing.x=x;
    framing.y=y;

    return framing;
}

/**
* \fn void affichageEcran(SDL_Renderer* renderer,char* imagedefond)
* \brief la fontion permet d'afficher l'image de fond du jeu
* \param[in] SDL_Renderer* renderer,char* imagedefond
* \param[out] none
*/


void affichageEcran(SDL_Renderer* renderer,char* imagedefond)
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Texture* texture_main = loadImage(renderer,imagedefond);
    SDL_RenderCopy(renderer,texture_main,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_main);


}


/**
* \fn void splashscreen(SDL_Renderer *renderer)
* \brief La fonction permet de gerer l'affichage au démarrage du jeu
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void splashscreen(SDL_Renderer *renderer)
{
    SDL_Texture * texture = loadImage(renderer,"res/qwirkle.bmp");
    SDL_Texture* bottom_splash_texture = loadImage(renderer,"res/bottom.bmp");

    SDL_Rect dst1;
    SDL_Rect dst2;
    dst1.h = HEIGHT/1.4;
    dst1.w = WIDTH/1.2;
    dst1.x = (WIDTH/2 - dst1.w/2);
    dst1.y = (HEIGHT/2 - dst1.h/2);

    dst2.h = HEIGHT/10;
    dst2.w = WIDTH/5;
    dst2.x=(WIDTH/2 - dst2.w/2);
    dst2.y=HEIGHT-dst2.h;

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,bottom_splash_texture,NULL,&dst2);
    SDL_RenderCopy(renderer,texture,NULL,&dst1);
    SDL_RenderPresent(renderer);

    affichage_pause(2000);

    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(bottom_splash_texture);
}


/**
* \fn TTF_Font* setPolice(char* font, int tailledepolice)
* \brief la fontion permet de definir une police d'ecriture (font + taille)
*
* \param[in] char* font, int tailledepolice // le style d'ecriture (font) et la taille du texte
* \param[out] TTF_Font*  police // la police d'ecriture
*/


TTF_Font* setPolice(char* font, int tailledepolice)
{
    TTF_Font *police=NULL;
    police = TTF_OpenFont("res/arial.ttf",tailledepolice);
    if(NULL==police)
    {
        fprintf(stderr,"Erreur d'ouverture du font: %s\n",TTF_GetError());
        SDL_Log("TTF Openfont : Failure\n");
        TTF_CloseFont(police);
        return NULL;
    }

    SDL_Log("TTF Openfont : SUCCESS\n");
    return police;

}


/**
* \fn int writeThis(SDL_Renderer* renderer,SDL_Texture* textureTexte,TTF_Font *police, char* texte, SDL_Color couleurTexte, SDL_Rect* encadrementtexte)
* \brief La fonction permet d'ecrire un texte sur le rendu
* \param[in]  SDL_Renderer* renderer
* \param[in]  SDL_Texture* textureTexte  // la texture sur laquelle ecire
* \param[in]  TTF_Font *police   // la police d'ecriture du texte
* \param[in]  char* texte   // le texte a ecrire
* \param[in]  SDL_Color couleurTexte   // la couleur du texte
* \param[in]  SDL_Rect* encadrementtexte   // le framing du texte
*
* \param[out] int -1 si erreur 0 sinon
*/


int writeThis(SDL_Renderer* renderer,SDL_Texture* textureTexte,TTF_Font *police, char* texte, SDL_Color couleurTexte, SDL_Rect* encadrementtexte)
{
    SDL_Surface*surfaceTexte=NULL;
    surfaceTexte=TTF_RenderText_Blended(police,texte,couleurTexte);

    if(NULL==surfaceTexte)
    {
        fprintf(stderr,"Erreur renderText: %s\n",TTF_GetError());
        SDL_Log("creation de surfaceTexte: Failure\n");
        SDL_FreeSurface(surfaceTexte);
        return -1;
    }
    SDL_Log("TTF_RenderText_Blended : SUCCESS\n");

    textureTexte = createTexture(renderer,surfaceTexte);
    if(NULL!=textureTexte)
    {
        SDL_Log("Ecriture de texte: SUCCESS\n");
    }
    SDL_RenderCopy(renderer,textureTexte,NULL,encadrementtexte);
    return 0;
}

/**
* \fn void affichageScore(SDL_Renderer* renderer,Partie *p)
* \brief La fonction permet d'afficher le score des joueurs
* \param[in] SDL_Renderer *renderer,Partie *p
* \param[out] none
*/


void affichageScore(SDL_Renderer* renderer,Partie *p)
{
    int i,posy;
    TTF_Font *police=NULL;
    SDL_Color couleurNoire= {0,0,0};
    SDL_Texture *textureTexte=NULL;
    char score[200]="";
    SDL_Rect scoresheet;
    SDL_Rect background;

    police=setPolice("C:/Users/Thiba/Desktop/Qwirkle/fonts/Arial.ttf",15);

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    background=createFraming(200,250,910,130);
    SDL_RenderFillRect(renderer,&background);

    for(i=0; i<p->NbJoueurs; i++)
    {
        sprintf(score,"Score du joueur %d est :  %d",i+1,p->joueurs[i]->points);
        posy=140+(i*40);
        scoresheet= createFraming(155,25,910,posy);
        writeThis(renderer,textureTexte,police,score,couleurNoire,&scoresheet);
    }
    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureTexte);

}

/**
* \fn void affichageScore_demo(SDL_Renderer* renderer,Partie *p)
* \brief La fonction permet d'afficher le score des joueurs
* \param[in] SDL_Renderer *renderer,Partie *p
* \param[out] none
*/


void affichageScore_demo(SDL_Renderer* renderer,Partie *p)
{
    int i,posy;
    TTF_Font *police=NULL;
    SDL_Color couleurNoire= {0,0,0};
    SDL_Texture *textureTexte=NULL;
    char score[200]="";
    SDL_Rect scoresheet;
    SDL_Rect background;

    police=setPolice("fonts/Arial.ttf",17);

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    background=createFraming(250,250,910,130);
    SDL_RenderFillRect(renderer,&background);

    for(i=0; i<p->NbJoueurs; i++)
    {
        sprintf(score,"Score du joueur %d est :  %d",i+1,p->joueurs[i]->points);
        posy=140+(i*57);
        scoresheet= createFraming(180,28,910,posy);
        writeThis(renderer,textureTexte,police,score,couleurNoire,&scoresheet);
    }
    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureTexte);

}
/**
* \fn void affichage_message(SDL_Renderer *renderer,SDL_Color couleur,SDL_Rect *background,char* message)
* \brief La fonction permet d'afficher un message avec la couleur que l'on veut
* \param[in] SDL_Renderer *renderer,char* message,SDL_Color couleur,SDL_Rect *background
* \param[out] none
*/


void affichage_message(SDL_Renderer *renderer,SDL_Color couleur,SDL_Rect *background,char* message)
{
    TTF_Font *police=NULL;
    SDL_Texture *textureTexte=NULL;

    police=setPolice("fonts/Arial.ttf",13);

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer,background);


    writeThis(renderer,textureTexte,police,message,couleur,background);
    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureTexte);
}


/**
* \fn void supprime_zonemessage(SDL_Renderer *renderer,SDL_Rect *background)
* \brief La fonction permet d'effacer un message
* \param[in] SDL_Renderer *renderer,SDL_Rect *background
* \param[out] none
*/


void supprime_zonemessage(SDL_Renderer *renderer,SDL_Rect *background)
{

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer,background);
    SDL_RenderPresent(renderer);


}


/**
* \fn void affiche_Tisok_message(SDL_Renderer *renderer,int i,SDL_bool clearmessage)
* \brief La fonction permet d'afficher ou d'effacer un message d'erreur si la tuile est mal positionnée (selon les regles du jeu)
* \param[in] SDL_Renderer *renderer,int i,SDL_bool showmessage
* \param[out] none
*/


void affiche_Tisok_message(SDL_Renderer *renderer,int i,SDL_bool showmessage)
{
    SDL_Rect background=createFraming(310,25,920,380);
    if(SDL_TRUE==showmessage)
    {
        SDL_Color couleur= {255,0,0};

        if(i==0)
        {
            supprime_zonemessage(renderer,&background);
        }
        else if(i==1)
        {
            affichage_message(renderer,couleur,&background,"Erreur: une tuile est deja posee à cette POSITION");
        }
        else if(i==2)
        {
            affichage_message(renderer,couleur,&background,"Erreur: la tuile n'est pas adjacente a d'autres tuiles");
        }
        else if(i==3)
        {
            affichage_message(renderer,couleur,&background,"Erreur: la tuile est de forme et couleur differente");
        }
        else if(i==4)
        {
            affichage_message(renderer,couleur,&background,"Erreur: une tuile de cette forme et couleur a deja ete posee");
        }
        else if(i==5)
        {
            affichage_message(renderer,couleur,&background,"Erreur: la tuile devrait etre de la meme couleur");
        }
        else if(i==6)
        {
            affichage_message(renderer,couleur,&background,"Erreur: la tuile devrait etre de la meme forme");
        }

    }
    else
    {
        supprime_zonemessage(renderer,&background);
    }

}


/**
* \fn  void affichage_trackingerror(SDL_Renderer *renderer,SDL_bool iswordokaligned,SDL_bool showmessage)
* \brief La fonction permet d'afficher ou d'effacer un message indiquant si les tuiles du mot sont eparpillées ou non
* \param[in] SDL_Renderer *renderer, SDL_bool iswordokaligned, SDL_bool showmessage
* \param[out] none
*/


void affichage_trackingerror(SDL_Renderer *renderer,SDL_bool iswordokaligned,SDL_bool showmessage)
{
    SDL_Rect background=createFraming(300,25,930,350);
    if(showmessage==SDL_TRUE)
    {
        SDL_Color couleur= {255,0,0};
        if(iswordokaligned==0)
        {
            affichage_message(renderer,couleur,&background,"Erreur: les tuiles de votre mot sont eparpillees");
        }
        else
        {
            supprime_zonemessage(renderer,&background);
        }

    }
    else
    {
        supprime_zonemessage(renderer,&background);
    }

}


/**
* \fn  void affichage_isregleok(SDL_Renderer *renderer,SDL_bool regleok,SDL_bool showmessage)
* \brief La fonction permet d'afficher ou d'effacer un message indiquant si le mot est valide ou non
* \param[in] SDL_Renderer *renderer,int i,SDL_bool showmessage,SDL_bool regleok
* \param[out] none
*/


void affichage_isregleok(SDL_Renderer *renderer,SDL_bool regleok,SDL_bool showmessage)
{
    SDL_Rect background=createFraming(150,25,1000,380);
    if(showmessage==SDL_TRUE)
    {
        SDL_Color couleurbleu= {0,0,255};
        SDL_Color couleurrouge= {255,0,0};

        if(regleok==SDL_FALSE)
        {
            affichage_message(renderer,couleurrouge,&background,"le mot n'est pas valide");
        }
        else
        {
            background.w=110;
            background.x=1025;
            affichage_message(renderer,couleurbleu,&background,"Le mot est valide");
        }

    }
    else
    {
        supprime_zonemessage(renderer,&background);
    }

}


/**
* \fn void affichage_sac(SDL_Renderer *renderer,Partie *p)
* \brief La fonction permet d'afficher le nombre de tuiles restant du sac à la position (970,650)
* \param[in] SDL_Renderer *renderer,Partie *p
* \param[out] none
*/


void affichage_sac(SDL_Renderer *renderer,Partie *p)
{

    SDL_Color noir= {0,0,0,255};
    TTF_Font *police=NULL;
    SDL_Texture *textureSac=loadImage(renderer,"res/sac.bmp");
    SDL_Rect sacrect=createFraming(275,275,940,650);;
    SDL_RenderCopy(renderer,textureSac,NULL,&sacrect);
    SDL_RenderPresent(renderer);
    char sac[200]="";
    police=setPolice("fonts/Arial.ttf",12);
    sprintf(sac,"%d tuiles restantes",p->nbTuilesSac);
    SDL_Rect sacsheet= createFraming(135,22,1030,800);
    writeThis(renderer,textureSac,police,sac,noir,&sacsheet);
    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureSac);

}


/**
* \fn SDL_Texture* loadTuilefromData(Tuile * t,int x,int y,int taille, SDL_Renderer* renderer)
* \brief La fonction permet d'afficher une tuile t passée en paramètre à la position (x,y) du renderer
* \param[in] Tuile * t,int x,int y,int taille, SDL_Renderer renderer
* \param[out] SDL_Renderer renderer pour pouvoir ensuite free la mémoire correctement
*/


SDL_Texture* loadTuilefromData(Tuile * t,int x,int y,int taille, SDL_Renderer* renderer)
{
    if(x<0||y<0||renderer==NULL)
    {
        fprintf(stderr,"erreur dans les parametres d'entree de la fonction loadTuilefromData\n");
        return NULL;
    }
    char * nomdufichier=(char*)malloc(40*sizeof(char));
    strcpy(nomdufichier,"res/tuile-");
    if(t!=NULL)
    {

        switch (t->forme)
        {

        case CERCLE :
            strcat(nomdufichier,"cercle-");
            break;

        case CROIX :
            strcat(nomdufichier,"croix-");

            break;

        case LOSANGE:
            strcat(nomdufichier,"losange-");

            break;

        case CARRE :
            strcat(nomdufichier,"carre-");

            break;

        case ETOILE:
            strcat(nomdufichier,"etoile-");

            break;

        case TREFLE:
            strcat(nomdufichier,"trefle-");

            break;
        }

        switch (t->couleur)
        {

        case ROUGE :
            strcat(nomdufichier,"rouge.bmp");
            break;

        case ORANGE :
            strcat(nomdufichier,"orange.bmp");

            break;

        case JAUNE:
            strcat(nomdufichier,"jaune.bmp");

            break;

        case VERT :
            strcat(nomdufichier,"vert.bmp");

            break;

        case BLEU:
            strcat(nomdufichier,"bleu.bmp");

            break;

        case VIOLET:
            strcat(nomdufichier,"violet.bmp");

            break;
        }
    }
    else
    {
        strcat(nomdufichier,"vide.bmp");
    }


    SDL_Rect carre = {x,y,taille,taille};
    SDL_Texture * matexturetuile = loadImage(renderer,nomdufichier);
    SDL_RenderCopy(renderer,matexturetuile,NULL,&carre);
    SDL_DestroyTexture(matexturetuile);
    return matexturetuile;
}


/**
* \fn void affiche_plateau_17x17(SDL_Renderer *renderer,Partie *partie,int xoff,int yoff,SDL_bool clearTiles)
* \brief
*
* La fonction permet d'afficher/d'effacer un plateau décallé de xoff en abscisse et yoff en ordonnée de taille 17 x 17
*
* Lorsque clearTiles=SDL_FALSE on affiche les tuiles
* Lorsque clearTiles=SDL_TRUE, on efface les tuiles
*
* Infos utiles :
*
* Le coin gauche du plateau est situé en (20,20) et le coin droit en (870,870)
* La tuile centrale ce trouve à l'index i=99 et j=99 du modèle
* La taille choisie des tuiles est 50x50
*
* \param[in] SDL_Renderer *renderer,Partie *partie,int xoff,int yoff,SDL_bool clearTiles
*
*/


void affiche_plateau_17x17(SDL_Renderer *renderer,Partie *partie,int xoff,int yoff,SDL_bool clearTiles)
{
    if(xoff>91||yoff>91||xoff<-91||yoff<-91)
    {
        fprintf(stderr,"erreur dans les parametres d'offset de la fonction affiche_plateau_17x17\n");
        return;
    }

    for(int i=0; i<17; i++)
    {
        for(int j=0; j<17; j++)
        {
            if((partie->plateau->tuiles[91+i+xoff][91+j+yoff] != NULL) && !(clearTiles))
            {
                SDL_Texture* maTextureTuile =loadTuilefromData(partie->plateau->tuiles[91+i+xoff][91+j+yoff],20+50*i,20+50*j,50,renderer); //! charge la texture de la tuile eventuellement décallée
                SDL_DestroyTexture(maTextureTuile);
            }
            if((partie->plateau->tuiles[91+i+xoff][91+j+yoff] != NULL) && clearTiles)
            {
                SDL_Texture* maTextureTuile =loadTuilefromData(NULL,20+50*i,20+50*j,50,renderer); //! charge la texture de la tuile vide

                SDL_DestroyTexture(maTextureTuile);
            }
        }
    }
    SDL_RenderPresent(renderer); //! actualise le render
}


/**
* \fn void affiche_tuiles_provisoires_17x17(SDL_Renderer *renderer,Partie *partie,int tabtuilesprovisoires[6],int xoff,int yoff,SDL_bool clearTiles)
* \brief
*
* La fonction permet d'afficher/D'effacer les tuiles provisoires décallées de xoff en abscisse et yoff en ordonnée sur le plateau de taille 17 x 17
*
* Lorsque clearTiles=SDL_FALSE on affiche les tuiles provisoires
* Lorsque clearTiles=SDL_TRUE, on efface les tuiles provisoires
*
* Infos utiles :
*
* Le coin gauche du plateau est situé en (20,20) et le coin droit en (870,870)
* La tuile centrale ce trouve à l'index i=99 et j=99 du modèle
* La taille choisie des tuiles est 50x50
*
*
* \param[in] SDL_Renderer *renderer,Partie *partie,int tabtuilesprovisoires[6],int xoff,int yoff,SDL_bool clearTiles
*
*/


void affiche_tuiles_provisoires_17x17(SDL_Renderer *renderer,Partie *partie,int tabtuilesprovisoires[6],int xoff,int yoff,SDL_bool clearTiles)
{

    if(xoff>91||yoff>91||xoff<-91||yoff<-91)
    {
        fprintf(stderr,"erreur dans les parametres d'offset de la fonction affiche_tuiles_provisoires_17x17\n");
        return;
    }
    int i=0;
    int j=0;

    for(int k=0; k<6; k++)
    {
        if((tabtuilesprovisoires[k]==1) && !(clearTiles))
        {
            if(getJoueurCourant(partie)->tuilesJoueur[k]->x>=91+xoff+1 && getJoueurCourant(partie)->tuilesJoueur[k]->x<=91+xoff+1+16)
            {
                if(getJoueurCourant(partie)->tuilesJoueur[k]->y>=91+yoff+1 && getJoueurCourant(partie)->tuilesJoueur[k]->y<=91+yoff+1+16)
                {
                    i=getJoueurCourant(partie)->tuilesJoueur[k]->x-92-xoff;
                    j=getJoueurCourant(partie)->tuilesJoueur[k]->y-92-yoff;

                    SDL_Texture* maTextureTuile =loadTuilefromData(getJoueurCourant(partie)->tuilesJoueur[k],20+5+50*i,20+5+50*j,40,renderer); //! charge la texture de la tuile eventuellement décallée et plus petite pour accentuer le coté provisoire
                    SDL_DestroyTexture(maTextureTuile);
                }
            }
        }

        if((tabtuilesprovisoires[k]==1) && clearTiles)
        {
            if(getJoueurCourant(partie)->tuilesJoueur[k]->x>=91+xoff+1 && getJoueurCourant(partie)->tuilesJoueur[k]->x<=91+xoff+1+16)
            {
                if(getJoueurCourant(partie)->tuilesJoueur[k]->y>=91+yoff+1 && getJoueurCourant(partie)->tuilesJoueur[k]->y<=91+yoff+1+16)
                {
                    i=getJoueurCourant(partie)->tuilesJoueur[k]->x-92-xoff;
                    j=getJoueurCourant(partie)->tuilesJoueur[k]->y-92-yoff;

                    SDL_Texture* maTextureTuile =loadTuilefromData(NULL,20+50*i,20+50*j,50,renderer); //! charge la texture de la tuile vide afin d'effacer le contenu de la case
                    SDL_DestroyTexture(maTextureTuile);
                }
            }
        }
    }


    SDL_RenderPresent(renderer); //! actualise le render
}


/**
* \fn void affiche_main_joueur_courant(SDL_Renderer *renderer,Partie *partie)
* \brief
*
* La fonction permet d'afficher la main du joueur courant
*
* Infos utiles :
*
* Le coin gauche se situe en (140,910)
*
* La taille choisie des tuiles est 100x100
*
*
* \param[in] SDL_Renderer *renderer,Partie *p
*
*/


void affiche_main_joueur_courant(SDL_Renderer *renderer,Partie *partie)
{
    for(int i=0; i<6; i++)
    {
        SDL_Texture* maTextureTuile =loadTuilefromData(getJoueurCourant(partie)->tuilesJoueur[i],140+100*i,910,100,renderer); //! coin haut gauche
        SDL_RenderPresent(renderer); //! actualise le render
        SDL_DestroyTexture(maTextureTuile);
    }
}


/**
* \fn void affiche_bouton_OK(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le Bouton [OK] à la position (1050,435)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_bouton_OK(SDL_Renderer *renderer)
{
    SDL_Color noir= {0,0,0,255};
    TTF_Font *police=NULL;
    SDL_Texture *textureOK=loadImage(renderer,"res/ok.bmp");
    SDL_Rect okrect=createFraming(100,60,1050,435);
    SDL_RenderCopy(renderer,textureOK,NULL,&okrect);
    SDL_RenderPresent(renderer);
    char ok[200]="";
    police=setPolice("fonts/Arial.ttf",12);
    sprintf(ok,"OK");
    SDL_Rect oksheet= createFraming(25,25,1085,455);
    writeThis(renderer,textureOK,police,ok,noir,&oksheet);
    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureOK);
}


/**
* \fn void supprime_bouton_OK(SDL_Renderer *renderer)
* \brief La fonction permet de supprimer le bouton [OK] à la position (1050,435)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void supprime_bouton_OK(SDL_Renderer *renderer)
{
    SDL_Texture *textureOK=loadImage(renderer,"res/supprBouton.bmp");
    SDL_Rect okrect=createFraming(100,60,1050,435);
    SDL_RenderCopy(renderer,textureOK,NULL,&okrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textureOK);
}


/**
* \fn void affiche_bouton_fin_du_tour(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le Bouton [Fin du Tour] à la position (1050,435)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_bouton_fin_du_tour(SDL_Renderer *renderer)
{
    SDL_Texture *textureOK=loadImage(renderer,"res/findutour.bmp");
    SDL_Rect okrect=createFraming(100,60,1050,435);
    SDL_RenderCopy(renderer,textureOK,NULL,&okrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textureOK);
}


/**
* \fn void supprime_bouton_fin_du_tour(SDL_Renderer *renderer)
* \brief La fonction permet de supprimer le bouton [OK] à la position (1050,435)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void supprime_bouton_fin_du_tour(SDL_Renderer *renderer)
{
    SDL_Texture *textureOK=loadImage(renderer,"res/supprBouton.bmp");
    SDL_Rect okrect=createFraming(100,60,1050,435);
    SDL_RenderCopy(renderer,textureOK,NULL,&okrect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textureOK);
}


/**
* \fn void affiche_poser(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le bouton [Poser] (1155,505)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_poser(SDL_Renderer *renderer)
{
    SDL_Rect framingImage=createFraming(100,60,1155,505);
    SDL_Texture *texture=loadImage(renderer,"res/poser.bmp");
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void affiche_bouton_retour(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le bouton [retour choix action] en (1155,505).
* Le bouton est de la taille (100,120)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_bouton_retour(SDL_Renderer *renderer)
{
    SDL_Rect framingImage=createFraming(100,120,1155,505);
    SDL_Texture *texture=loadImage(renderer,"res/retour.bmp");
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void supprime_bouton_retour(SDL_Renderer *renderer)
* \brief La fonction permet de supprimer le bouton [retour choix action] en (1155,505) en affichant un bouton blanc par dessus.
* Le bouton est de la taille (100,120)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void supprime_bouton_retour(SDL_Renderer *renderer)
{
    SDL_Rect framingImage=createFraming(100,120,1155,505);
    SDL_Texture *texture=loadImage(renderer,"res/supprBouton.bmp");
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void affiche_piocher(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le bouton [Piocher] (1155,595)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_piocher(SDL_Renderer *renderer)
{
    SDL_Texture *texture=loadImage(renderer,"res/piocher.bmp");
    SDL_Rect framingImage=createFraming(100,60,1155,595);
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void affiche_passer_son_tour(SDL_Renderer *renderer)
* \brief La fonction permet d'afficher le bouton [Passer son tour] en (1155,595)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affiche_passer_son_tour(SDL_Renderer *renderer)
{
    SDL_Texture *texture=loadImage(renderer,"res/passer.bmp");
    SDL_Rect framingImage=createFraming(100,60,1155,595);
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void supprime_poser(SDL_Renderer *renderer)
* \brief La fonction permet de supprimer les bouton [Poser] (1155,505)
*
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void supprime_poser(SDL_Renderer *renderer)
{

    SDL_Texture *texture=loadImage(renderer,"res/supprBouton.bmp");
    SDL_Rect framingImage=createFraming(100,60,1155,505);
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

}


/**
* \fn void supprime_piocher(SDL_Renderer *renderer)
* \brief La fonction permet de supprimer les bouton [Piocher] (1155,595)
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void supprime_piocher(SDL_Renderer *renderer)
{

    SDL_Texture *texture=loadImage(renderer,"res/supprBouton.bmp");
    SDL_Rect framingImage=createFraming(100,60,1155,595);
    SDL_RenderCopy(renderer,texture,NULL,&framingImage);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

}


/**
* \fn void affichage_fleches_plateau(SDL_Renderer* renderer)
* \brief La fonction permet d'afficher les fleches de redimensionnement du plateau
* \param[in] SDL_Renderer *renderer
* \param[out] none
*/


void affichage_fleches_plateau(SDL_Renderer* renderer)
{

    SDL_Texture * fleche = loadImage(renderer,"res/flecheHAUT.bmp");

    SDL_Rect flechesheet= createFraming(38,58,980,510);

    SDL_RenderCopy(renderer,fleche,NULL,&flechesheet);

    flechesheet.y= 590;
    fleche = loadImage(renderer,"res/flecheBAS.bmp");
    SDL_RenderCopy(renderer,fleche,NULL,&flechesheet);

    flechesheet=createFraming(58,38,930,560);
    fleche = loadImage(renderer,"res/flecheGAUCHE.bmp");
    SDL_RenderCopy(renderer,fleche,NULL,&flechesheet);

    flechesheet.x= 1010 ;
    fleche = loadImage(renderer,"res/flecheDROITE.bmp");
    SDL_RenderCopy(renderer,fleche,NULL,&flechesheet);

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(fleche);

}


/**
* \fn void afficheJoueurCourant(SDL_Renderer *renderer, Partie *p)
* \brief La fonction permet d'afficher le joueur courant avec une flèche
* \param[in] SDL_Renderer *renderer, Partie *p
* \param[out] none
*/


void affichageJoueurCourant(SDL_Renderer* renderer,Partie *p)
{
    int i,posy;

    SDL_Texture * fleche = loadImage(renderer,"res/fleche.bmp");

    SDL_Rect joueurCourantsheet;
    SDL_Rect background;

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    background=createFraming(50,200,1075,135);

    SDL_RenderFillRect(renderer,&background);

    for(i=0; i<p->NbJoueurs; i++)
    {

        if(p->joueurs[i] == getJoueurCourant(p))
        {

            posy=135+(i*40);
            joueurCourantsheet= createFraming(50,30,1075,posy);

            SDL_RenderCopy(renderer,fleche,NULL,&joueurCourantsheet);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(fleche);
}
/**
* \fn void afficheJoueurCourant_demo(SDL_Renderer *renderer, Partie *p)
* \brief La fonction permet d'afficher le joueur courant avec une flèche
* \param[in] SDL_Renderer *renderer, Partie *p
* \param[out] none
*/


void affichageJoueurCourant_demo(SDL_Renderer* renderer,Partie *p)
{
    int i,posy;

    SDL_Texture * fleche = loadImage(renderer,"res/fleche.bmp");

    SDL_Rect joueurCourantsheet;
    SDL_Rect background;

    SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
    background=createFraming(50,200,1090,135);

    SDL_RenderFillRect(renderer,&background);

    for(i=0; i<p->NbJoueurs; i++)
    {

        if(p->joueurs[i] == getJoueurCourant(p))
        {

            posy=140+(i*57);
            joueurCourantsheet= createFraming(50,30,1090,posy);

            SDL_RenderCopy(renderer,fleche,NULL,&joueurCourantsheet);
            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(fleche);
}

/**
* \fn void affichage_selection_tuiles(SDL_Renderer *renderer, int j)
* \brief
*
* La fonction permet d'afficher une flèche au dessus des tuiles qui sont sélectionnées par le joueur
* int j représente l'emplacement de la tuile sélectionnée
*
* \param[in] SDL_Renderer *renderer, int j
* \param[out] none
*/


void affichage_selection_tuiles(SDL_Renderer * renderer,int j)
{
    SDL_Texture *texture=loadImage(renderer,"res/fleche_selection.bmp");
    SDL_Rect rect=createFraming(10,20,(180+j*100),880);
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void supprime_selection_tuiles(SDL_Renderer *renderer, int j)
* \brief
*
* La fonction permet de supprimer la flèche au dessus des tuiles qui ne sont plus sélectionnées par le joueur
* int j représente l'emplacement de la tuile sélectionnée
*
* \param[in] SDL_Renderer *renderer, int j
* \param[out] none
*/


void supprime_selection_tuiles(SDL_Renderer * renderer,int j)
{
    SDL_Texture *texture=loadImage(renderer,"res/supprBouton.bmp");
    SDL_Rect rect=createFraming(10,20,(180+j*100),880);
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void affichage_selection_tuiles_finales(SDL_Renderer *renderer, int j)
* \brief
*
* La fonction permet d'afficher la flèche finale au dessus des tuiles qui ont été posées provisoirement par le joueur
* int j représente l'emplacement de la tuile sélectionnée
*
* \param[in] SDL_Renderer *renderer, int j
* \param[out] none
*/


void affichage_selection_tuiles_finales(SDL_Renderer * renderer,int j)
{
    SDL_Texture *texture=loadImage(renderer,"res/fleche_selection_finale.bmp");
    SDL_Rect rect=createFraming(10,20,(180+j*100),880);
    SDL_RenderCopy(renderer,texture,NULL,&rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}


/**
* \fn void affichageFin(SDL_Renderer *renderer, Partie* p)
* \brief Affichage de fin de partie
*
* La fonction affiche l'écran de fin de partie avec l'écran des scores
*
* \param[in] SDL_Renderer *renderer, Partie* p
* \param[out] none
*/


void affichageFin(SDL_Renderer* renderer,Partie* p)
{

    int i,posy,max,id;
    char messageScore[200]="";
    char messageGagnant[200]="";
    TTF_Font *police=NULL;
    SDL_Color couleurNoire= {0,0,0};
    SDL_Color couleurRouge = {255,0,0};
    SDL_Texture *texture_fin = NULL;
    SDL_Texture *textureTexte=NULL;

    SDL_Rect scoresheet;

    /*!Affichage fond */

    SDL_RenderClear(renderer);

    texture_fin = loadImage(renderer,"res/fin_image.bmp");
    SDL_RenderCopy(renderer,texture_fin,NULL,NULL);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture_fin);

    /*!Affichage Joueur gagnant*/

    max = 0;
    id = 0;
    for(i=0; i<p->NbJoueurs; i++)
    {
        if(p->joueurs[i]->points > max)
        {
            max = p->joueurs[i]->points;
            id = i+1;
        }
    }

    sprintf(messageGagnant,"Le joueur %d est vainqueur !",id);
    scoresheet= createFraming(500,100,400,150);
    writeThis(renderer,textureTexte,setPolice("fonts/Arial.ttf",30),messageGagnant,couleurRouge,&scoresheet);



    /*!Affichage Tableau score*/

    for(i=0; i<p->NbJoueurs; i++)
    {
        sprintf(messageScore,"Joueur %d :  %d",i+1,p->joueurs[i]->points);
        posy=300+(i*150);
        scoresheet= createFraming(500,100,200,posy);
        writeThis(renderer,textureTexte,setPolice("fonts/Arial.ttf",30),messageScore,couleurNoire,&scoresheet);
    }

    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureTexte);

}


/**
* \fn void affichageFin(SDL_Renderer *renderer, Partie* p)
* \brief Affichage de fin de partie
*
* La fonction affiche l'écran de fin de partie avec l'écran des scores
*
* \param[in] SDL_Renderer *renderer, Partie* p
* \param[out] none
*/


void affichageFinTour(SDL_Renderer * renderer, Partie *p){

    char message[200]="";
    TTF_Font *police=NULL;
    SDL_Color couleurNoire= {0,0,0};
    SDL_Texture *textureFond = NULL;
    SDL_Texture *textureTexte = NULL;

    SDL_Rect fondRect;
    SDL_Rect messageRect;


    /*!Affichage fond */

    textureFond = loadImage(renderer,"res/fin_tour.bmp");
    fondRect=createFraming(400,200,440,412);

    SDL_RenderCopy(renderer,textureFond,NULL,&fondRect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(textureFond);


    sprintf(message,"Le tour de %s est fini !",getJoueurCourant(p)->nom);
    messageRect= createFraming(360,50,460,480);
    writeThis(renderer,textureTexte,setPolice("fonts/Arial.ttf",20),message,couleurNoire,&messageRect);


    SDL_RenderPresent(renderer);
    TTF_CloseFont(police);
    SDL_DestroyTexture(textureTexte);


}

