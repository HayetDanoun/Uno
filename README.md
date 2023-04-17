- Bahadi Imane p1907992
- Danoun Hayet p1925003
- Cayuela Anna p1907353

Identifiant de projet sur la forge: 18533

# UNO

Jeu du Uno

Le but du jeu est de se débarrasser le premier de toutes ses cartes. 
Au début de la partie, le joueur dispose de 7 cartes de couleurs différentes (rouge, bleu, vert et jaune) et numérotées de 1 à 9. Quatre cartes d'action existent.
Une carte est placée au centre de la fenêtre face visible. 
Si le paquet du joueur 1 dispose d’une carte de même couleur ou portant le même numéro ou de même symbole que la carte de départ, il la sélectionne. Sinon, il pioche une carte.

- **Cartes de 1 à 9**

- **Carte +2** : Le joueur suivant pioche deux cartes

- **Carte Inverser** : Le sens de jeu change

- **Carte Passer** : Le joueur suivant ne joue pas

- **Carte Bob** : Le joueur qui pose cette carte choisit de changer (ou non) la couleur

- **Carte +4** : Le joueur qui pose cette carte choisit de changer (ou non) la couleur et le Le joueur suivant pioche quatre cartes

## Organisation des fichiers/répertoires

- **uno/projetLIFAP4/src/core** : Les classes de base du Uno

- **uno/projetLIFAP4/src/txt** : Les classes permettant de jouer au Uno en l'affichant dans la console en mode texte

- **uno/projetLIFAP4/src/sdl2** : Les classes permettant de faire tourner le Uno en l'affichant avec sdl en mode graphique

- **uno/projetLIFAP4/bin** : répertoire où les executables sont compilés

- **uno/projetLIFAP4/data** : répertoire dans lequel se trouvent les images utilisées dans la sdl

- **uno/projetLIFAP4/data/carteimage** : répertoire dans lequel se trouvent les images des différentes cartes

- **uno/projetLIFAP4/obj** : répertoire dans lequel se trouvent les compilations intermédiaires (.o)

- **uno/projetLIFAP4/Makefile** : 

- **uno/README.md** : Ce readme

## Pour Compiler

Dans un terminal se placer dans le répertoire **uno/projetLIFAP4** et taper la commande
``` 
make all
```
### Mode texte du jeu
se placer dans le répertoire **uno/projetLIFAP4/bin** et exécuter txtJeu en tapant
```
./txtJeu
```

### Mode graphique du jeu
se placer dans le répertoire **uno/projetLIFAP4/bin** et exécuter sdlJeu en tapant 
```
./sdlJeu
```


## Pour utiliser le jeu en mode texte

touches à utiliser:

- **a** :	affiche les cartes du joueur

- **j** :	permet de jouer contre deux ordinateurs (joueur-2 et joueur-3). Demande au joueur-1 quelle carte il veut poser. Le joueur-1 entre l'indice de la carte qu'il veut poser. 

- **p** :	permet au joueur de piocher une carte

- **u** :	le joueur annonce qu'il ne lui reste plus qu'une carte

- **c** : 	le joueur peut contrer un autre joueur. On lui demande d'entrer le numéro du joueur qu'il veut contrer.
	
- **x** :   permet de jouer à plusieurs


## Pour utiliser le jeu en mode graphique

- Lorsque le message "C'est votre tour" s'affiche, choisir une carte en cliquant dessus. Si le joueur decide de piocher, il clique la pioche (tas de carte au milieu de la fenêtre).
- Lorsque le joueur pose un **Bob** ou un **+4** quatre couleurs s'affichent dans la fenêtre. Le joueur choisi sa couleur en double cliquant sur celle de son choix.
