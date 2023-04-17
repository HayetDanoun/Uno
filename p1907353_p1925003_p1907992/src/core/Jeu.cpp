#include "Jeu.h"
#include <iostream>

Jeu::Jeu() : monde()
{
	monde.commercerLaPartie();
}

Monde& Jeu::getMonde() { return monde; }

const Monde& Jeu::getConstMonde () const { return monde; }

bool Jeu::actionClavier (const char touche) {
	int jc;
	char c = '0';
    int  k = 0;
	

	switch(touche) {
		case 'x':
			for(unsigned int i=0; i<monde.nbDeJoueur; i++){
				monde.j[i].estUnOrdinateur = false;
			}
			break;

		case 'p':
			monde.p.piocher(monde.j[k]);
			monde.passerAuJoueurSuivant(k);
			break;

		case 'a' :
			monde.afficher(k);
			break;

		case 'j':
			do{
				monde.poserCarte(k, c);
				k++;
			}while(k!=3);	
			break;

		case 'u':
			monde.uno();
			monde.passerAuJoueurSuivant(k);
			break;

		case 'c':
			std::cin>>jc;
			monde.contreUno(jc);
			break;
		
		default: monde.passerAuJoueurSuivant(k);
	}


	return false;
}
