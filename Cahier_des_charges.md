**Qwirkle**
ahah
Le but de ce projet est de faire une version numérique du jeu de plateau Qwirkle. Ce jeux est un peu similaire à un scrabble avec des formes et des couleurs. Chaque joueur essaye de marquer le maximum de points en constituant des lignes de formes ou de couleurs identiques.

Version V0 : version console simplifiée

- --jouer une partie avec 3 joueurs (joueur 1, joueur 2, joueur 3);
- --modélisation des structures de données : .h et .c des structures Partie, Joueur, Tuile et Plateau;
- --comptage des points simplifié : 1 point par Tuile posée (les tuiles déjà posées ne sont pas prises en compte;
- --Règles simplifiées : possibilité de poser une tuile si même couleur ou même forme que les tuiles qui lui sont adjacentes verticalement et horizontalement;
- --Gestion du sac :

- création des 108 tuiles;
- si sac vide on ne peut plus piocher
- distribution aléatoire de 6 tuiles à chaque joueur en début de jeu
-  Distribution aléatoire du nombre de tuiles nécessaires :

-Cas 1: le joueur a posé X tuiles sur le plateau et demandes X tuiles;

-Cas 2: le joueur passe son tour et échange ses tuiles contre d&#39;autres           qui se trouvent dans le sac;

Pour le cas 2, il faudra mettre à jour le tableau de tuiles du sac en y ajoutant les tuiles du joueur et en enlevant les tuiles qui ont été prises.

- --affichage console : afficher le plateau ligne par ligne sur la zone occupée

(un tiret pour représenter une zone vide, une lettre pour la forme et un chiffre pour la couleur);

- --Gestion de la Partie : gestion des règles (messages d&#39;erreurs), des tours et comptage des points;
- --Gestion du Joueur : fonctions poser Tuile;

Version V1 :  Premier affichage graphique et respect des règles et des points

- --interface Graphique (SDL 2.0) : affichage plateau, pièces, joueurs, sac et nombre de tuiles restantes :

- étape 1 : affichage de base : lancer la partie, plateau mais sans possibilité de jouer et pièces sorties;
- étape 2 : rotation entre les joueurs, gestion des tours, choix entre échanger ou poser des tuiles;
- étape 3 : dimensionnement du plateau (le plateau grandit au fur et à mesure du jeu), pose des tuiles par des clics;

- --Respect des vraies règles du jeux : pour le comptage des points et la pose des tuiles;

Version V2 : Intelligence artificielle

- --intelligence artificielle basique : poser les tuiles où elle peut sans chercher à avoir le maximum de points;
- --amélioration interface graphique : Drag&#39;n Drop, Zoom, Message d&#39;erreur lors du non respect des règles + explication de l&#39;erreur commise;
- --affichage de base : lancer la partie, plateau mais sans possibilité de jouer et pièces sortie;
- --Personnalisation de la partie : nom des joueurs et avatar;
- --possibilité de bouger sur le plateau de jeux, avec un système de balayage voire zoom;



Version V3 : améliorations graphiques

- --Bouton option : choix du thème (fond d&#39;écran, motifs des tuiles), musique et audio;
- --Bouton règles : permet d&#39;afficher les règles du jeux (possibilité de faire défiler les règles de bas en haut);
- --différents niveaux de jeux pour l&#39;intelligence artificielle (facile, intermédiaire, expert) sélectionnable depuis le menu du jeux;