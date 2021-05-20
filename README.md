# QwirkleInC

Jeu Qwirkle en langage C.

Le jeu  Qwirkle se compose de 108 tuiles. Les tuiles peuvent être de plusieurs couleurs et formes différentes.
Les couleurs sont le rouge, l'orange, le jaune, le vert, le bleu et le violet.
et les formes sont le cercle, la croix, le losange, le carré, l'étoile et le trèfle.

Principe du jeu:

Les joueurs commencent le jeu avec six tuiles. Le premier joueur pose des blocs de tuiles d'un seul attribut  (couleur ou forme mais pas les deux) sur le plateau. Par la suite, un joueur ajoute des blocs de tuiles adjacents à au moins un bloc précédemment joué. Les tuiles doivent toutes être jouées sur une même ligne,et correspondre,sans doublons, à la couleur ou à la forme du bloc précédent.

Les joueurs marquent un point pour chaque tuile posée. IL marque également des points pour toutes les tuiles adjacentes. Si un joueur complète une ligne contenant les six formes ou couleurs, six points supplémentaires sont marqués. Le joueur pioche ensuite dans le sac pour avoir 6 tuiles dans sa main.

Le jeu se termine lorsqu'il n'y a plus de tuiles dans le sac et un joueur n'a plus de tuiles dans sa main, le joueur avec le meilleur score gagne la partie.

Les règles du jeu sont disponibles dans QwirkleInC/Règles/Qwirkle_regles_FR_web.pdf.

Pour pouvoir compiler le projet, deux librairies sont nécessaires: la SDL2.0 et la SDL_TTF .
Pour installer le paquet de développement de la SDL2.0 sous linux,il faut écrire la commande suivante dans le terminal: 
	     - apt-get install libsdl2-dev 
et pour avoir la librairie SDL_TTF:
	     - sudo apt-get install libsdl2-ttf-dev
	     
Pour pouvoir compiler le projet avec les tests unitaires, il est nécessaire d'avoir la librairie cmoka
Entrer les commandes suivante dans un dossier que l'on pourra supprimer par la suite :

         - sudo wget https://cmocka.org/files/1.1/cmocka-1.1.1.tar.xz
         - sudo tar xf cmocka-1.1.1.tar.xz
         - sudo cmake cmocka-1.1.1
         - sudo make install
         - sudo ldconfig



