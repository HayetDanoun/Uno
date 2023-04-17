#include <iostream>
using namespace std;
#include "Carte.h"
#include<cassert>

Carte::Carte()
{
    nombre=0;
    c=noir;
}

Carte::Carte(unsigned int nb, Couleur couleur)
{
    nombre=nb;
    c=couleur;
}
Carte::Carte(const Carte &cp)
{
    nombre=cp.nombre;
    c=cp.c;
}

unsigned int Carte::retourNombre() const
{
    return nombre;
}

Couleur Carte::retourCouleur() const
{
    return c;
}

void Carte::modifierNombre(int unsigned nb)
{
    nombre=nb;
}

void Carte::modifierCouleur(Couleur couleur)
{
    c=couleur;
}

void Carte::echangeCarte (Carte &deuxiemeCarte)
{
    Carte permute(*this);
    modifierNombre(deuxiemeCarte.retourNombre());
    modifierCouleur(deuxiemeCarte.retourCouleur());
    deuxiemeCarte.modifierNombre(permute.retourNombre());
    deuxiemeCarte.modifierCouleur(permute.retourCouleur());
}

void Carte::afficherCarte()
{
/*
	cout<<"[";
	if(nombre==10) cout<<"changement";
	else if(nombre==11) cout<<"passe";
	else if(nombre==12) cout<<"+2";
	else if(nombre==13) cout<<"bob";
	else if(nombre==14) cout<<"+4";

	else cout<<nombre;
	if(c==vert) cout<<", vert";
	if(c==bleu) cout<<", bleu";
	if(c==jaune) cout<<", jaune";
	if(c==rouge) cout<<", rouge";
	cout<<"] ";
	// noir on affiche rien
*/

    unsigned int nb;
    Couleur coul;

    cout<<"              _____  "<<endl;

    coul=retourCouleur();
    nb=retourNombre();
    if(coul==vert)cout      <<"             |v    |";
    else if(coul==bleu)cout <<"             |b    |";
    else if(coul==jaune)cout<<"             |j    |";
    else if(coul==rouge)cout<<"             |r    |";
    else if(nb==13)     cout<<"             |bob  |";
    else                cout<<"             |+4   |";
    cout<<endl;


    if(nb<10)cout<<"             |  "<<nb<<"  |";
    else if(nb==10) cout<<"             |  ⇅  |";
    else if(nb==11) cout<<"             |  ⊗  |";
    else if(nb==12) cout<<"             | +2  |";
    else cout           <<"             |     |";
    cout<<endl;

    if(coul==vert)cout      <<"             |    v|";
    else if(coul==bleu)cout <<"             |    b|";
    else if(coul==jaune)cout<<"             |    j|";
    else if(coul==rouge)cout<<"             |    r|";
    else if(nb==13)     cout<<"             |  bob|";
    else                cout<<"             |   +4|";
    cout<<endl;
    cout<<"              _____  "<<endl<<endl<<endl;
    //cout<<" |_____| " ;

}


void Carte::TestCarte()
{
    Carte c1;
    Carte c2(12, vert);
    Carte c3(c1);

    //constructeur par défaut
    assert(c1.c == noir);
    assert(c1.nombre == 0);

    //constructeur de la classe
    assert(c2.c == vert);
    assert(c2.nombre == 12);

    //constructeur par copie
    assert(c3.c == c1.c);
    assert(c3.nombre == c1.nombre);

    //retournerNombre

    //retournerCouleur

    cout<<"On modifie les numeros des cartes"<<endl;
    c1.modifierNombre(2);
    c2.modifierNombre(3);
    c3.modifierNombre(7);
    //modifierNombre
    assert(c1.retourNombre() == 2);
    assert(c2.retourNombre() == 3);
    assert(c3.retourNombre() == 7);


    cout<<"On modifie les couleurs"<<endl;
    c1.modifierCouleur(vert);
    c2.modifierCouleur(bleu);
    c3.modifierCouleur(jaune);
    //modifierCouleur
    assert(c1.retourCouleur() == vert);
    assert(c2.retourCouleur() == bleu);
    assert(c3.retourCouleur() == jaune);

    c1.echangeCarte(c2);
    //échanger carte
    assert(c1.retourNombre() == 3);
    assert(c1.retourCouleur() == bleu);
    assert(c2.retourNombre() == 2);
    assert(c2.retourCouleur() == vert);

}
