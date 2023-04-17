#include <iostream>
using namespace std;
#include "Monde.h"

Monde::Monde()
{
    nbDeJoueur=3;
    j=new Joueur[3];
    j[0].estUnOrdinateur=false;
    j[1].estUnOrdinateur=true;
    j[2].estUnOrdinateur=true;
    sensDuJeuChanger=false;
}

Monde::Monde(unsigned int nbJoueur,unsigned int nbOrdi)
{
    unsigned int nbJoueurTotal=nbJoueur+nbOrdi;
    nbDeJoueur=nbJoueurTotal;
    j=new Joueur[nbJoueurTotal];
    for(unsigned int i=0;i<nbJoueur;i++)
    {
        j[i].estUnOrdinateur=false;
    }
    for(unsigned int i=nbJoueur;i<nbJoueurTotal;i++)
    {
        j[i].estUnOrdinateur=true;
    }
    sensDuJeuChanger=false;
}

void Monde::distribuer()
{
    unsigned int i,k;
    for(i=0;i<7;i++) //les joueurs pioche 7 cartes au début de la partie
        for(k=0;k<nbDeJoueur;k++)
            p.piocher(j[k]);
}

void Monde::commercerLaPartie()
{
//pioche
    p.initPioche(); //met toutes les cartes dans la Pioche dans l'ordre
    p.melangerPioche();
//les joueurs
    distribuer();
    for(unsigned int k=0;k<nbDeJoueur;k++)
        j[k].trierCarteJoueur();

//CarteDuMilieu
    unsigned int i=0;
    while(p.retourCarte(p.retourNbCartes()-1).retourNombre()>9) //pour eviter que la premiere carte soit une carte bonus
    {
        p.retourCarte(p.retourNbCartes()-1).echangeCarte(p.retourCarte(i));
        i++;
    }
    milieu.ajouterCarte(p.retourCarte(p.retourNbCartes()-1));
    p.supprimerDerniereCarte();
}

bool Monde::peutPoser(const Joueur &j,unsigned int indice, char &c)
{
  if(indice==0)
  {
    return true;
  }
    Couleur coulCarteJoueur=j.retourCarteJoueur(indice-1).retourCouleur();
  if(indice < 0 || indice > j.nombreCartesJoueur)
  {
    cout<<"Nb trop grand/petit"<<endl;
    return false;
  }
  if(c!='0') //si un des joueurs d'avant avait poser un bob ou un +4
  {
    if(c=='v' && coulCarteJoueur==vert)
    {
        c='0';
        return true;
    }
    else if(c=='b' && coulCarteJoueur==bleu)
    {
        c='0';
        return true;
    }
    else if(c=='j' && coulCarteJoueur==jaune)
    {
        c='0';
        return true;
    }
    else if(c=='r' && coulCarteJoueur==rouge)
    {
        c='0';
        return true;
    }
    else if(coulCarteJoueur==noir)
    {
        return true;
    }
    else
    {
        cout<<"Vous ne pouvez-pas posez cette carte.";
        cout<<" Vous devez poser du ";
        if(c=='v') cout<<"vert."<<endl;
        if(c=='b') cout<<"bleu."<<endl;
        if(c=='j') cout<<"jaune."<<endl;
        if(c=='r') cout<<"rouge."<<endl;
        return false;
    }
  }
  else if(coulCarteJoueur==milieu.retourCarte(milieu.retourNbCartes()-1).retourCouleur())
  {
    return true;
  }
  else if(j.retourCarteJoueur(indice-1).retourNombre()==milieu.retourCarte(milieu.retourNbCartes()-1).retourNombre())
  {
    return true;
  }
  else if(coulCarteJoueur==noir)
  {
    return true;
  }
  else
  {
    cout<<"Vous ne pouvez-pas posez cette carte"<<endl;
    return false;
  }

}

void Monde::poserChangerSens(int &k)
{
    if(sensDuJeuChanger==true) sensDuJeuChanger=false;
    else sensDuJeuChanger=true;
    if(!sensDuJeuChanger)
    {
        k++;
        if(k%nbDeJoueur==0) k=0;
    }
    else
    {
        k--;
        if(k==-1) k=nbDeJoueur-1;
    }
}

void Monde::poserPasseTour(int &k)
{
    if(!sensDuJeuChanger)
    {
        if(k==nbDeJoueur-1) k=1;
        else if(k==nbDeJoueur-2) k=0;
        else k+=2;
    }
    else
    {
        if(k==0) k=nbDeJoueur-2;
        else if (k==1) k=nbDeJoueur-1;
        else k-=2;
    }
}

void Monde::poserPlusDeuxJoueur(int &k,unsigned int nbDeCarteAPiocher)
{
    unsigned int i,indice;
    bool ok=false;
    if(j[k].possedeCarteNombreJoueur(12)) //si le joueur suivant possede un ou plusieurs +2
    {
        afficher(k); //on affiche ses cartes
        do{  //on lui demande s'il veut poser son +2 ou piocher en appuyant sur 0
            cout<<"Pose ton +2 ou pioche en appuyant sur 0 : ";
            cin>>indice;
        }while(indice!=0 && j[k].retourCarteJoueur(indice-1).retourNombre()!=12);

        if(indice==0) //si il veut piocher
        {
            cout<<"T'as decidé de Piocher "<<nbDeCarteAPiocher<<" cartes"<<endl;
            for(i=0;i<nbDeCarteAPiocher;i++)
            {
                p.piocher(j[k]);
            }
            afficher(k);
            passerAuJoueurSuivant(k);
        }
        else //si il a decider de poser son +2 ou son +4
        {
            milieu.ajouterCarte(j[k].retourCarteJoueur(indice-1)); //on pose carte que le joueur a choisi au milieu
            j[k].supprimerCarteJoueur(indice-1); //on la supprime de la main du joueur

            nbDeCarteAPiocher+=2;
            poserPlusDeux(k,nbDeCarteAPiocher);
        }
    }
    else //si le joueur n'a pas de +2 ou le +4 on lui fait piocher directement
    {
        cout<<"Ta pas de + tant pis"<<endl;
        cout<<"Piocher "<<nbDeCarteAPiocher<<" cartes"<<endl;
        for(i=0;i<nbDeCarteAPiocher;i++)
        {
            p.piocher(j[k]);
        }
        afficher(k);
        passerAuJoueurSuivant(k);
    }
}

void Monde::poserPlusDeuxOrdi(int &k,unsigned int nbDeCarteAPiocher)
{
    unsigned int i,compt=0;
    unsigned int tab[j[k].nombreCartesJoueur];

    for( i=0;i<j[k].nombreCartesJoueur;i++)
        if(j[k].retourCarteJoueur(i).retourNombre()==12)
        {
            tab[compt]=i;
            compt++;
        }
    if(compt==0) //l'ordinateur ne possède pas de +2 ou de +4
    {
        for(unsigned int i=0;i<nbDeCarteAPiocher;i++)
        {
            p.piocher(j[k]);
        }
        afficher(k);
        passerAuJoueurSuivant(k);
    }

    if(compt==1) //l'ordinateur possède un +2 ou un +4
    {
        //on pose le +2 ou +4 du joueur
        milieu.ajouterCarte(j[k].retourCarteJoueur(tab[0])); //avt mis indice a la place tab[0] mais comprends pas pk
        j[k].supprimerCarteJoueur(tab[0]);

        nbDeCarteAPiocher+=2;
        poserPlusDeux(k,nbDeCarteAPiocher);
    }
    else
    {
        unsigned int indice;
        indice=PoserMeilleurIndiceOrdi(tab,k,compt);
        milieu.ajouterCarte(j[k].retourCarteJoueur(tab[indice])); //avt mis indice a la place tab[0] mais comprends pas pk
        j[k].supprimerCarteJoueur(tab[indice]);

        nbDeCarteAPiocher+=2;
        poserPlusDeux(k,nbDeCarteAPiocher);
    }
}

void Monde::poserPlusDeux(int &k,unsigned int nbDeCarteAPiocher)
{
    //on passe au joueur suivant
    passerAuJoueurSuivant(k);

    if(j[k].estUnOrdinateur) poserPlusDeuxOrdi(k,nbDeCarteAPiocher);
    else poserPlusDeuxJoueur(k,nbDeCarteAPiocher);
}

char Monde::demanderCouleurJoueur()
{
    char couleur;
    do{
        cout<<"Quelle couleur voulez-vous ? : ";
        cin>>couleur;
    }while(couleur!='v' && couleur!='b' && couleur!='j' && couleur!='r' );

    return couleur;
}

char Monde::demanderCouleurOrdi(int k)
{
    char couleur;
    couleur=j[k].meilleurCouleur(); //met dans couleur, la couleur ou possède le plus de carte
    return couleur;
}

void Monde::poserBob(int &k, char &couleur)
{
    if(j[k].estUnOrdinateur) couleur=demanderCouleurOrdi(k); //si le joueur suivant est un Ordinateur
    else couleur=demanderCouleurJoueur(); //si le joueur est un humain

    //on passe au joueur suivant
    passerAuJoueurSuivant(k);
}

void Monde::poserPlusQuatreJoueur(int &k,unsigned int &nbDeCarteAPiocher,char couleur)
{
    unsigned int i;
    if(j[k].possedeCarteNombreJoueur(14)) //si le joueur suivant possede un ou plusieurs +4
    {
        afficher(k); //on affiche ses cartes
        do{  //on lui demande s'il veut poser son +4 ou piocher en appuyant sur 0
            cout<<"Posez ton +4 ou prenez les cartes : ";
            cin>>i;
        }while(i!=0 && j[k].retourCarteJoueur(i-1).retourNombre()!=14 );

        if(i==0) //si il veut piocher
        {
            cout<<"Ta decider de Piocher "<<nbDeCarteAPiocher<<" cartes"<<endl;
            for(i=0;i<nbDeCarteAPiocher;i++)
            {
                p.piocher(j[k]);
            }
            afficher(k);
            passerAuJoueurSuivant(k);
        }
        else //si le joueur pose un +4
        {
            milieu.ajouterCarte(j[k].retourCarteJoueur(i-1)); //on pose le +4 au milieu
            j[k].supprimerCarteJoueur(i-1); //on le supprime de la main du joueur
            nbDeCarteAPiocher+=4;
            poserPlusQuatre(k,nbDeCarteAPiocher,couleur);
        }
    }

    else //si le joueur possede pas de +4
    {
        cout<<endl;
        cout<<"Piocher "<<nbDeCarteAPiocher<<" cartes"<<endl;
        for(i=0;i<nbDeCarteAPiocher;i++)
        {
            p.piocher(j[k]);
        }
        passerAuJoueurSuivant(k);
    }
}

void Monde::poserPlusQuatreOrdi(int &k,unsigned int nbDeCarteAPiocher,char couleur)
{
    if(j[k].possedeCarteNombreJoueur(14)) //si l'ordinateur possede un +4
    {
        //le pose directement (la derniere carte est forcément un +4
        milieu.ajouterCarte(j[k].retourCarteJoueur(j[k].nombreCartesJoueur-1));
        j[k].supprimerCarteJoueur(j[k].nombreCartesJoueur-1);
        nbDeCarteAPiocher+=4;
        poserPlusQuatre(k,nbDeCarteAPiocher,couleur);
    }
    else //l'ordinateur ne possède pas de +2 ou de +4
    {
        for(unsigned int i=0;i<nbDeCarteAPiocher;i++)
        {
            p.piocher(j[k]);
        }
        passerAuJoueurSuivant(k);
    }
}

void Monde::poserPlusQuatre(int &k,unsigned int nbDeCarteAPiocher, char &couleur)
{


    if(j[k].estUnOrdinateur) couleur=demanderCouleurOrdi(k); //si le joueur suivant est un Ordinateur
    else couleur=demanderCouleurJoueur(); //si le joueur est un humain

    passerAuJoueurSuivant(k);
    if(j[k].estUnOrdinateur) poserPlusQuatreOrdi(k,nbDeCarteAPiocher,couleur);
    else poserPlusQuatreJoueur(k,nbDeCarteAPiocher,couleur);
}

int Monde::choisiCarteJoueur(int k,char &c)
{
    int indice;
    //le joueur choisit quelle carte qu'il veut poser
    do
    {
        cout<<"Choisir quelle carte voulez-vous poser : ";
        cin>>indice;
        cout<<endl<<endl;
    }while(peutPoser(j[k],indice,c)==false);
    return indice-1;
}

int Monde::choisiCarteOrdinateur(int k,char &c)
{
    int indice;
    unsigned int i,compt=0; //compt compte le nb de carte que l'ordi peut poser
    unsigned int tab[j[k].nombreCartesJoueur]; //tableaux des indices des cartes que l'ordinateur peux poser
    if(c=='0')
    {
        for(i=0;i<j[k].nombreCartesJoueur;i++)
            if(j[k].retourCarteJoueur(i).retourNombre()== milieu.retourCarte(milieu.retourNbCartes()-1).retourNombre()
              || j[k].retourCarteJoueur(i).retourCouleur()== milieu.retourCarte(milieu.retourNbCartes()-1).retourCouleur()
              || j[k].retourCarteJoueur(i).retourCouleur()==noir ) ///pour le moment peux poser de carte noir
            {
                tab[compt]=i;
                compt++;
            }
    }
    else //si l'un des joueurs d'avant a poser un bob ou un +4
    {
        Couleur doitPoser;
        if (c=='v') doitPoser=vert;
        if (c=='b') doitPoser=bleu;
        if (c=='j') doitPoser=jaune;
        if (c=='r') doitPoser=rouge;
        for(i=0;i<j[k].nombreCartesJoueur;i++)
            if(j[k].retourCarteJoueur(i).retourCouleur()==doitPoser
               || j[k].retourCarteJoueur(i).retourCouleur()==noir ) ///pour le moment peux poser de carte noir
        {
            tab[compt]=i;
            compt++;
        }
        if(compt!=0) c='0';
    }

    if(compt==0) indice=-1; //ordinateur va piocher
    else if(compt==1)
    {
        indice=tab[0]; //si l'ordinateur ne peux poser qu'une seule carte, il l'a pose directement
    }
    else //si l'ordinateur possède plusieurs carte, il regarde laquelle sera la plus avantagueuse
    {
        //indice=tab[0];
        indice=PoserMeilleurIndiceOrdi(tab,k,compt);
    }

    return indice;
 }

unsigned int Monde::PoserMeilleurIndiceOrdi(const unsigned int *tab,unsigned int k, unsigned int compt)
{
    j[k].trierCarteJoueur();
    unsigned int i,indice=tab[0];
    Couleur temp;
    bool okVert=false,okBleu=false,okJaune=false,okRouge=false;
    unsigned int tabComptNbCouleur[4];
    unsigned int tabComptNbCoulCopie[4];

    unsigned int MeilleurCouleur=0; //=0 si =vert / 1 si bleu / 2 si jaune / 3 si rouge
    for(i=0;i<j[k].nombreCartesJoueur;i++)
    {
        temp=j[k].retourCarteJoueur(i).retourCouleur();
        if(temp==vert) okVert=true;
        if(temp==bleu) okBleu=true;
        if(temp==jaune) okJaune=true;
        if(temp==rouge) okRouge=true;
    }
    j[k].compteCouleur(tabComptNbCouleur);
    for(i=0;i<4;i++)
        tabComptNbCoulCopie[i]=tabComptNbCouleur[i];
    if(!okVert) tabComptNbCouleur[0]=0;
    if(!okBleu) tabComptNbCouleur[1]=0;
    if(!okJaune) tabComptNbCouleur[2]=0;
    if(!okRouge) tabComptNbCouleur[3]=0;

    unsigned int compterNbCouleur=0;
    for(i=0;i<4;i++)
        if(tabComptNbCouleur[i]!=0) compterNbCouleur++;


    if(j[k].retourCarteJoueur(tab[0]).retourCouleur()==noir) //si le joueur ne peut poser que du noir
        {
            unsigned int compCoulPossedeJoue=0;
            for(i=0;i<4;i++)
                    if(tabComptNbCoulCopie[i]!=0) compCoulPossedeJoue++;
            if(compCoulPossedeJoue==3) indice =-1; //s'il a 3 couleurs != dans sa main il pioche
            else indice=tab[0];  //s'il a 1e ou 2 , il pose son bob ou son +4
        }
    if(compterNbCouleur==1) indice=tab[0]; //s'il ne peut poser qu'une seule couleur, il pose la premiere Carte

    else
    {
        for(i=0;i<4;i++)
            if(MeilleurCouleur<tabComptNbCouleur[i])
                MeilleurCouleur=i;
        if(MeilleurCouleur==0) indice=tab[0]; //si la couleur la plus avantagueux est Verte, comme les cartes sont triées
        else                                  //elle sera forcement la premiere
        {
            i=1;
            bool ok=false;
            do
            {
                if(j[k].retourCarteJoueur(tab[i]).retourCouleur()==MeilleurCouleur)
                {
                    indice=tab[i];
                    ok=true;
                }
                i++;
            } while(!ok && i<compt);
        }
    }
        return indice;
}

void Monde::poserCarte(int &k,char &c) //k=Joueur qui est entrain de jouer
{
    int indice;
    if(j[k].estUnOrdinateur) indice=choisiCarteOrdinateur(k,c);
    else indice=choisiCarteJoueur(k,c);
    if(indice==-1) //le joueur pioche
    {
        p.piocher(j[k]);
        passerAuJoueurSuivant(k);
    }
    else
    {
        unsigned int temp=j[k].retourCarteJoueur(indice).retourNombre(); //pour eviter de recalculer j[k].retourCarteJoueur(indice) à chaque fois
        milieu.ajouterCarte(j[k].retourCarteJoueur(indice)); //on pose carte que le joueur a choisi au milieu
        j[k].supprimerCarteJoueur(indice); //on la supprime de la main du joueur
        if(temp<10)passerAuJoueurSuivant(k);
        else
        {
            switch (temp)
    	    {
                case 10: //changement de sens
                poserChangerSens(k);
                break;
                case 11: //bob
                poserPasseTour(k);
                break;
                case 12: //+2
                poserPlusDeux(k,2);
                break;
                case 13: //bob
                c='0';
                poserBob(k,c);
                break;
                case 14: //+4
                c='0';
                poserPlusQuatre(k,4,c);
                break;
            }
        }
    }
}

void Monde::jouer()
{
    commercerLaPartie();
    //TestMonde();
    char c = '0'; //change de valeur quand le joueur pose un bob ou un +4 (peut être egale à v/b/j/r)
    int  k = 0; //numero du joueur qui est entrain de joueur
    bool quitter=false;
    do
    {
        afficher(k);
        poserCarte(k,c);
    }while(!gagner(quitter) || !quitter);
}

bool Monde::gagner(bool &quitter)
{
    unsigned int k;
    bool rejouer=false,gagner=false;
    char c='0';
    for(k=0;k<nbDeJoueur;k++)
        if(j[k].nombreCartesJoueur==0)
        {

            cout<<"Le joueur "<<k+1<<" a gagner !"<<endl;
            gagner=true;
            do
            {
                cout<<"Taper sur p pour rejouer et q pour quitter "<<endl;
                cin>>c;
                if(c=='p') rejouer=true;
                if(c=='q') quitter=true;
            }while(!quitter && !rejouer);

            if(rejouer)
            {
                for(k=0;k<nbDeJoueur;k++) //on supprime toutes les Cartes des joueurs
                    j[k].supprimerJoueur();
                milieu.supprimerCartes(); //on supprime les cartes au milieu
                p.supprimerCartes(); //on suppprime la pioche
                commercerLaPartie();
            }
        }
    return gagner;
}

void Monde::passerAuJoueurSuivant(int &k)
{
    j[k].trierCarteJoueur();
    if(!sensDuJeuChanger)
    {
        k++;
        if(k%nbDeJoueur==0) k=0;
    }
    else
    {
        k--;
        if(k==-1) k=nbDeJoueur-1;
    }
}

const void Monde::afficher(unsigned int k)
{
    for(unsigned int i=0;i<nbDeJoueur;i++)
    {
        if(i!=k)cout<<"Il reste "<<j[i].nombreCartesJoueur <<" cartes au joueur "<<i+1<<endl;
    }
    cout<<endl;
    cout<<"          Carte du milieu"<<endl;
    milieu.retourCarte(milieu.retourNbCartes()-1).afficherCarte();

    cout<<"Tour du joueur "<<k+1<<endl;
    j[k].afficherCarteJoueur();
    cout<<endl<<endl;
}

bool Monde::uno()
{
    unsigned int k;
    if(j[k].nombreCartesJoueur == 1) return true;
}

bool Monde::contreUno(int& jc)
{
    if(j[jc].nombreCartesJoueur == 1)
    {
        p.piocher(j[jc]);
    }
    std::cout<<"euh... non.";
    return false;
}

void Monde::TestMonde()
{
    int k=0;
    char c='0';
    Carte c1(14,noir); //+4
    Carte c2(2,bleu);
    Carte c3(4,rouge);
    Carte c4(12,rouge); //+2 rouge
    Carte c5(13,noir); //bob
    Carte c6(2,vert);


    commercerLaPartie();
    milieu.modifierCarte(0,c3);

  //test l'intelligence de l'ordinateur
    milieu.modifierCarte(0,c2);
    for(unsigned int i=0;i<7;i++)
        j[2].modifierCarteJoueur(i,c3);
    j[1].modifierCarteJoueur(6,c6); //3 vert
    j[1].modifierCarteJoueur(5,c6);
    j[1].modifierCarteJoueur(4,c6);
    j[1].modifierCarteJoueur(3,c2);
    j[1].modifierCarteJoueur(2,c2); //4 bleu
    j[1].modifierCarteJoueur(1,c2);
    j[1].modifierCarteJoueur(0,c2);

}

