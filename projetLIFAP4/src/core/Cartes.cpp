#include "Cartes.h"
#include <stdlib.h>   // pour srand() et rand()
#include <time.h>     // pour time()
#include <iostream>
#include <cassert>

using namespace std;

Cartes::Cartes()
{
    tab=NULL;
    nbCartes=0;
}

Cartes::~Cartes ()
{
    nbCartes=0;
    if(tab!=NULL)
    {
        delete [] tab;
        tab=NULL;
    }
}

void Cartes::supprimerCartes()
{
    nbCartes=0;
    if(tab!=NULL)
    {
        delete [] tab;
        tab=NULL;
    }
}


unsigned int Cartes::retourNbCartes()
{
    return nbCartes;
}

Carte& Cartes::retourCarte(unsigned int i) const
{
    return tab[i];
}

unsigned int Cartes::retourDerniereCarteNombre() const
{
    return retourCarte(nbCartes-1).retourNombre();
}

Couleur Cartes::retourDerniereCarteCouleur() const
{
    return retourCarte(nbCartes-1).retourCouleur();
}

void Cartes::modifierCarte(unsigned int i,const Carte &c)
{
   retourCarte(i).modifierNombre(c.retourNombre());
   retourCarte(i).modifierCouleur(c.retourCouleur());
}
void Cartes::initPioche()
{
    unsigned int i,j,k;
    unsigned int nbCarteCouleur=4*12*2;
    unsigned int nbBob = 8 ;
    unsigned int nbPlusQuatre = 8 ;
    nbCartes= nbCarteCouleur + nbBob + nbPlusQuatre;
    tab=new Carte[nbCartes];

    for(j=0;j<=1;j++) //pour doubler les cartes
        for(k=0;k<4;k++)
            for(i=0; i<12;i++)
            {
                retourCarte(48*j+12*k+i).modifierNombre(i+1);
                if(k==0) retourCarte(48*j+12*k+i).modifierCouleur(vert);
                if(k==1) retourCarte(48*j+12*k+i).modifierCouleur(bleu);
                if(k==2) retourCarte(48*j+12*k+i).modifierCouleur(jaune);
                if(k==3) retourCarte(48*j+12*k+i).modifierCouleur(rouge);
            }

    for(i=nbCarteCouleur;i<=nbCartes;i++) //on rajoute les bobs et les +4
    {
        if (i<nbCarteCouleur+nbPlusQuatre) retourCarte(i).modifierNombre(13);
        else retourCarte(i).modifierNombre(14);
        retourCarte(i).modifierCouleur(noir);
    }
}

void Cartes::melangerPioche()
{
    unsigned int i, aleatoire;
    unsigned int mini = 1, maxi = nbCartes;
    int plage=maxi-mini+1;
    srand((unsigned int)time(NULL));
    for(i=0; i<nbCartes;i++)
    {
        aleatoire = (rand() % plage) + mini;//en prendre un indice d'une carte aux hasard
        retourCarte(i).echangeCarte(tab[aleatoire]); //permutation du 2 carte
    }
}

void Cartes::ajouterCarte(const Carte &c)
{
    if(tab==NULL)
    {
        nbCartes++;
        tab=new Carte[nbCartes];
        modifierCarte(0,c);
    }
    else
    {
        unsigned int i;
        Carte *temp=tab;
        tab=new Carte[nbCartes+1];
        for(i=0;i<nbCartes;i++)
        {
            modifierCarte(i,temp[i]);
        }
        delete [] temp;
        modifierCarte(nbCartes,c);
        nbCartes++;
    }
}


void Cartes::supprimerDerniereCarte()
{
    if(tab==NULL)
    {
        cout<<"il n'y a plus de carte dans la pioche"<<endl;
    }
    else
    {
        unsigned int i;
        Carte *temp=tab;
        nbCartes--;
        tab=new Carte[nbCartes];
        for(i=0;i<nbCartes;i++)
        {
            modifierCarte(i,temp[i]);
        }
        delete [] temp;
    }

}

void Cartes::piocher(Joueur &j)
{

    j.ajouterCarteJoueur(retourCarte(nbCartes-1));
    supprimerDerniereCarte();
}

void Cartes::echangeCartes(Cartes &PiocheDuMilieu)
{
    if(nbCartes==0)
    {
        nbCartes=PiocheDuMilieu.nbCartes-1;
        tab=PiocheDuMilieu.tab;
        PiocheDuMilieu.tab=new Carte[1];
        PiocheDuMilieu.tab[0]=tab[nbCartes];
        supprimerDerniereCarte();
    }
}


void Cartes::TestCartes()
{
    Cartes cs;
    Cartes cs2;
    Carte c(2, vert);

    //tests pour le Constructeur
    assert(cs.tab == NULL);
    assert(cs.nbCartes == 0);

    //tests pour initPioche
    cs.initPioche();
    cs2.initPioche();
    cout<<cs.nbCartes<<endl;
    assert(cs.nbCartes == (4*12*2)+8+8);
    for(unsigned int i = 0; i<cs.nbCartes; i++)
    {
       assert(cs.retourCarte(i).retourCouleur() != noir || cs.retourCarte(i).retourNombre() != 0);
    }

    //tests pour retournerCartePioche
    assert(cs.retourCarte(2).retourCouleur() == cs.tab[2].retourCouleur());

    //tests pour modifierCartePioche
    cs.modifierCarte(1, c);
    assert(cs.retourCarte(1).retourCouleur() == c.retourCouleur());
    assert(cs.retourCarte(1).retourNombre() == c.retourNombre());

    //test pour mélangerPioche
    cs.melangerPioche();
    assert(cs.retourCarte(0).retourCouleur() != cs2.retourCarte(0).retourCouleur()
           || cs.retourCarte(0).retourNombre() != cs2.retourCarte(0).retourNombre());


    unsigned int nb_tot_cartes = 112;
    //test pour ajouterCartePioche
    cs.ajouterCarte(c);
    assert(cs.nbCartes == nb_tot_cartes + 1);
    assert(cs.retourCarte(nb_tot_cartes).retourCouleur() == c.retourCouleur());
    assert(cs.retourCarte(nb_tot_cartes).retourNombre() == c.retourNombre());

    //test pour supprimerlaDerniereCarte
    cs.supprimerDerniereCarte();
    assert(cs.nbCartes == nb_tot_cartes);

    //tests pour piocher
    Joueur j;
    cs.piocher(j);
    assert(cs.nbCartes == nb_tot_cartes -1);
}
