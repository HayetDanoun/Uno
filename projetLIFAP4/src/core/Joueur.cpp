#include <iostream>
#include <cassert>
using namespace std;
#include "Joueur.h"

Joueur::Joueur()
{
    carteJoueur=NULL;
    nombreCartesJoueur=0;
    //estUnOrdinateur=false;
}

Joueur::~Joueur ()
{
    nombreCartesJoueur=0;
    if(carteJoueur!=NULL)
    {
        delete [] carteJoueur;
        carteJoueur=NULL;
    }
}

void Joueur::supprimerJoueur(){
    nombreCartesJoueur=0;
    if(carteJoueur!=NULL)
    {
        delete [] carteJoueur;
        carteJoueur=NULL;
    }
}

Carte& Joueur::retourCarteJoueur(unsigned int i) const
{
    return carteJoueur[i];
}

void Joueur::modifierCarteJoueur(unsigned int i,const Carte &c)
{
   retourCarteJoueur(i).modifierNombre(c.retourNombre());
   retourCarteJoueur(i).modifierCouleur(c.retourCouleur());
}

void Joueur::ajouterCarteJoueur(const Carte &c)
{
    if(carteJoueur==NULL)
    {
        nombreCartesJoueur++;
        carteJoueur=new Carte[nombreCartesJoueur];
        modifierCarteJoueur(0,c);
    }
    else
    {
        unsigned int i;
        Carte *temp=carteJoueur;
        carteJoueur=new Carte[nombreCartesJoueur+1];
        for(i=0;i<nombreCartesJoueur;i++)
        {
            modifierCarteJoueur(i,temp[i]);
        }
        delete [] temp;
        modifierCarteJoueur(nombreCartesJoueur,c);
        nombreCartesJoueur++;
    }
}

unsigned int Joueur::indiceDeLaCarteChoisie( )
{
    unsigned indice;
    cout<<"Choisir quelle carte voulez-vous poser : ";
    cin>>indice;
    indice-=1; //comme la premiere case du tableau est 0;
    return indice;
}

void Joueur::supprimerCarteJoueur(unsigned int indice)
{
    if(carteJoueur==NULL)
    {
        cout<<"Impossible le joueur n'a plus de carte"<<endl;
    }
    else //Faux car ne choisi pas la carte
    {
        unsigned int i;
        nombreCartesJoueur--;
        Carte *temp=carteJoueur;
        carteJoueur= new Carte[nombreCartesJoueur];
        for(i=0;i<indice;i++)
        {
            modifierCarteJoueur(i,temp[i]);
        }
        for(i=indice;i<nombreCartesJoueur;i++)
        {
            modifierCarteJoueur(i,temp[i+1]);
        }
        delete [] temp;
    }
}

void Joueur::trierCarteJoueur()
{
    Carte CarteAPlacer;
    for(unsigned int i=1; i<nombreCartesJoueur; i++)
    {
        CarteAPlacer = carteJoueur[i];
        int j= i-1;
        while( j>=0 && (CarteAPlacer.retourCouleur() < carteJoueur[j].retourCouleur()
                    || (CarteAPlacer.retourCouleur() == carteJoueur[j].retourCouleur() &&
                        CarteAPlacer.retourNombre() < carteJoueur[j].retourNombre() )))
        {
            carteJoueur[j+1] = carteJoueur[j];
            j--;
        }
        carteJoueur[j+1]=CarteAPlacer;
    }
}

bool Joueur::possedeCarteNombreJoueur(unsigned int nb)
{
    for(unsigned int i=0;i<nombreCartesJoueur;i++)
    {
        if(retourCarteJoueur(i).retourNombre()==nb) return true;
    }

    return false;
}

char Joueur::meilleurCouleur()
{
    Couleur temp;
    char couleur;
    unsigned int indice=0,i;
    unsigned int tab[4];
    tab[0]=0; tab[1]=0; tab[2]=0; tab[3]=0;

    //met dans t[0] le nb de carte verte que possede l'ordinateur,
    //t[1] le nb de carte bleu /t[2] de carte jaune et t[3] de carte rouge
    for(i=0;i<nombreCartesJoueur;i++)
    {
        temp=retourCarteJoueur(i).retourCouleur();
        if(temp==vert) tab[0]++;
        else if(temp==bleu) tab[1]++;
        else if(temp==jaune) tab[2]++;
        else if(temp==rouge) tab[3]++;
    }

    for(i=1;i<4;i++)
        if(tab[indice]<tab[i]) indice=i;

    if(indice==0) couleur='v';
    else if(indice==1) couleur='b';
    else if(indice==2) couleur='j';
    else couleur='r';

    return couleur;

}

void Joueur::compteCouleur(unsigned int tab[4])
{
    Couleur temp;
    tab[0]=0; tab[1]=0; tab[2]=0; tab[3]=0;
    for(unsigned int i=0;i<nombreCartesJoueur;i++)
    {
        //met dans t[0] le nb de carte verte que possede l'ordinateur,
        //t[1] le nb de carte bleu /t[2] de carte jaune et t[3] de carte rouge
        for(i=0;i<nombreCartesJoueur;i++)
        {
            temp=retourCarteJoueur(i).retourCouleur();
            if(temp==vert) tab[0]++;
            else if(temp==bleu) tab[1]++;
            else if(temp==jaune) tab[2]++;
            else if(temp==rouge) tab[3]++;
        }
    }
}
void Joueur::afficherCarteJoueur()
{
    unsigned int i,nb;
    Couleur coul;
    for(i=0;i<nombreCartesJoueur;i++)
        cout<<"  _____  ";
    cout<<endl;

    for(i=0;i<nombreCartesJoueur;i++)
    {
        coul=retourCarteJoueur(i).retourCouleur();
        if(coul==vert)cout      <<" |v    | ";
        else if(coul==bleu)cout <<" |b    | ";
        else if(coul==jaune)cout<<" |j    | ";
        else if(coul==rouge)cout<<" |r    | ";
        else if(retourCarteJoueur(i).retourNombre()==13) cout<<" |bob  | ";
        else                cout<<" |+4   | ";
    }
    cout<<endl;

    for(i=0;i<nombreCartesJoueur;i++)
    {
        nb=retourCarteJoueur(i).retourNombre();
        if(nb<10)cout<<" |  "<<nb<<"  | ";
        else if(nb==10)cout<<" |  ⇅  | ";
        else if(nb==11)cout<<" |  ⊗  | "; //pour passe ⊗
        else if(nb==12)cout<<" | +2  | ";
        else cout          <<" |     | ";
    }
    cout<<endl;
    for(i=0;i<nombreCartesJoueur;i++)
    {
        coul=retourCarteJoueur(i).retourCouleur();
        if(coul==vert)cout      <<" |    v| ";
        else if(coul==bleu)cout <<" |    b| ";
        else if(coul==jaune)cout<<" |    j| ";
        else if(coul==rouge)cout<<" |    r| ";
        else if(retourCarteJoueur(i).retourNombre()==13) cout<<" |  bob| ";
        else                cout<<" |   +4| ";
    }
    cout<<endl;
    for(i=0;i<nombreCartesJoueur;i++)
          cout<<"  _____  " ;
        //cout<<" |_____| " ;
    cout<<endl<<endl<<endl;
}

void Joueur::TestJoueur()
{
    Joueur J1;
    Carte c1(2, vert);
    Carte c2(3, bleu);

    //Constructeur
    assert(J1.carteJoueur == NULL);
    assert(J1.nombreCartesJoueur == 0);
    assert(J1.estUnOrdinateur == false);


    //tests pour ajouterCarteJoueur
    J1.ajouterCarteJoueur(c1);

    assert(J1.nombreCartesJoueur == 1);
    assert(J1.retourCarteJoueur(0).retourCouleur() == c1.retourCouleur());
    assert(J1.retourCarteJoueur(0).retourNombre() == c1.retourNombre());

    //tests pour retournerCarteJoueur
    assert(J1.retourCarteJoueur(0).retourCouleur() == J1.carteJoueur[0].retourCouleur());
    assert(J1.retourCarteJoueur(0).retourNombre() == J1.carteJoueur[0].retourNombre());

    //tests pour modifierCarteJoueur
    J1.modifierCarteJoueur(0, c2);

    assert(J1.retourCarteJoueur(0).retourCouleur() == bleu);
    assert(J1.retourCarteJoueur(0).retourNombre() == 3);

    //test pour indiceDeLACarteChoisie

    //test pour suprimeCarteJoueur

    unsigned int nbcartes = J1.nombreCartesJoueur;

    J1.supprimerCarteJoueur(0);
    assert(J1.nombreCartesJoueur == nbcartes -1);

}
