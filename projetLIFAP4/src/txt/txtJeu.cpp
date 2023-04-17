#include <iostream>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
#include "Jeu.h"

void txtAff(WinTXT & win, const Jeu & j) {

    const Monde &monde = j.getConstMonde();
    Carte mil(monde.milieu.retourDerniereCarteNombre(), monde.milieu.retourDerniereCarteCouleur());
	win.clear();
	std::cout<<"carte de départ: ";
	std::cout<<std::endl;
	mil.afficherCarte();
	std::cout<<std::endl;
}

void txtBoucle (Jeu & j) {
	// Creation d'une nouvelle fenetre en mode texte
	// => fenetre de dimension et position (WIDTH,HEIGHT,STARTX,STARTY)
    WinTXT win(100,100);

	bool ok = true;
	int c;

	do {

		txtAff(win,j);
		std::cout<<std::endl;
		win.pause();
		std::cout<<std::endl;

		char v = '0';
        int  k = 0;
        bool quitter=false;

		c = win.getCh();
		switch (c) {

			case 'p':
				j.actionClavier('p');
				break;

			case 'a':
				std::cout<<"Vos cartes sont: "<<std::endl;
				j.actionClavier('a');
				std::cout<<std::endl;
				break;

			case 'j':
				std::cout<<"quelle carte voulez-vous poser? ";
				j.actionClavier('j');
				std::cout<<std::endl;
				break;

			case 'c':
				j.actionClavier('c');
				std::cout<<std::endl;
				break;

			case 'u':
				std::cout<<"quel joueur voulez-vous contrer? ";
				j.actionClavier('u');
				std::cout<<std::endl;
				break;

			case 'x':
				std::cout<<"Vous jouez à plusieurs"<<std::endl;
				j.actionClavier('x');
				do{
					j.getMonde().afficher(k);
					j.getMonde().poserCarte(k,v);
					termClear();
					//win.pause();
				}while(!j.getMonde().gagner(quitter) && !quitter);
				break;

			case 'q':
				ok = false;
				break;
		}

	} while (ok);
}
