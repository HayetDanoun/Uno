#include "SdlMonde.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;


// ============= CLASS IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;

    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }

    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}



// ============= CLASS SDLMONDE =============== //


void SdlMonde::afficherInit(){
    unsigned int dim=12,nb=0;
    char v[50]; char b[50]; char j[50]; char r[50]; //pour mettre le chemin des images
    dimx=1600;
    dimy=1000;

    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    // Creation de la fenetre
    window = SDL_CreateWindow("UNO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    v[0]='\0'; b[0]='\0'; j[0]='\0'; r[0]='\0';
    strcat(v,"data/cartesimage/v00.png");
    strcat(b,"data/cartesimage/b00.png");
    strcat(j,"data/cartesimage/j00.png");
    strcat(r,"data/cartesimage/r00.png");

    nb=strlen(v) -5; //ici nb = 19, il servira a modifier les nombres pour le chemins dans v,b,j,r

    for(unsigned int i=1;i<10;i++) //pour  intialiser les images qui porte un nombre
    {
        v[nb]='0' + i; //v= "data/cartesimage/v0i.png" //avec i qui est un nombre compris entre 1 et 9 compris
        b[nb]='0' + i; //b= "data/cartesimage/b0i.png"
        j[nb]='0' + i; //j= "data/cartesimage/j0i.png"
        r[nb]='0' + i; //r= "data/cartesimage/r0i.png"

        im_carte[i-1].loadFromFile(v,renderer);
        im_carte[dim+i-1].loadFromFile(b,renderer);
        im_carte[dim*2+i-1].loadFromFile(j,renderer);
        im_carte[dim*3+i-1].loadFromFile(r,renderer);
    }

    v[nb-1]='1'; //v= "data/cartesimage/v19.png"
    b[nb-1]='1'; //b= "data/cartesimage/b19.png"
    j[nb-1]='1'; //j= "data/cartesimage/j19.png"
    r[nb-1]='1'; //r= "data/cartesimage/r19.png"

    for(unsigned int i=0;i<3;i++) //pour intialiser les cartes les inverse, passe,+2 (les bonus qui sont de couleur )
    {
        v[nb]='0' + i; //v= "data/cartesimage/v1i.png" //avec i qui est un nombre compris entre 0 et 2 compris
        b[nb]='0' + i; //b= "data/cartesimage/b1i.png"
        j[nb]='0' + i; //j= "data/cartesimage/j1i.png"
        r[nb]='0' + i; //r= "data/cartesimage/r1i.png"

        im_carte[10+i-1].loadFromFile(v,renderer);
        im_carte[10+dim+i-1].loadFromFile(b,renderer);
        im_carte[10+dim*2+i-1].loadFromFile(j,renderer);
        im_carte[10+dim*3+i-1].loadFromFile(r,renderer);
    }

    //pour iniatiliser les images bobs et +4
    v[nb-2]='n'; //v= "data/cartesimage/n12.png"
    v[nb]='3';   //v= "data/cartesimage/n13.png" //ce qui correspond au chemin pour aller chercher l'image du bob
    im_carte[4*dim].loadFromFile(v,renderer); //on rajoute le bob
    v[nb]='4'; //v= "data/cartesimage/n14.png" //ce qui correspond au chemin pour aller chercher l'image du +4
    im_carte[4*dim+1].loadFromFile(v,renderer); //on rajoute le +4

    im_carte[4*dim+2].loadFromFile("data/uno.png",renderer); //on rajoute le dos de la carte uno
    im_carte[4*dim+3].loadFromFile("data/unodroite.png",renderer); //on rajoute le dos de la carte uno pencher sur le coté droit
    im_carte[4*dim+4].loadFromFile("data/unogauche.png",renderer); //on rajoute le dos de la carte uno pencher sur le coté gauche
    im_carte[4*dim+5].loadFromFile("data/pioche.png",renderer); //on rajoute la pioche

    // INITIALISATION DES DIFFERENTES TEXTE
    font = TTF_OpenFont("data/DejaVuSansCondensed.ttf",50);
    if (font == NULL) font = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (font == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
            SDL_Quit();
            exit(1);
    }
    font_color.r = 0;font_color.g = 0;font_color.b = 0;

	font_im[0].setSurface(TTF_RenderText_Solid(font,"C'est votre tour",font_color));
	font_im[0].loadFromCurrentSurface(renderer);

	font_im[1].setSurface(TTF_RenderText_Solid(font,"Tour du joueur 2",font_color));
	font_im[1].loadFromCurrentSurface(renderer);

	font_im[2].setSurface(TTF_RenderText_Solid(font,"Tour du joueur 3",font_color));
	font_im[2].loadFromCurrentSurface(renderer);

	font_im[3].setSurface(TTF_RenderText_Solid(font,"Quelle couleur voulez-vous choisir ?",font_color));
	font_im[3].loadFromCurrentSurface(renderer);

	font_im[4].setSurface(TTF_RenderText_Solid(font,"Pose ton +2 ou pioche ",font_color));
	font_im[4].loadFromCurrentSurface(renderer);

	font_im[5].setSurface(TTF_RenderText_Solid(font,"Pose ton +4 ou pioche ",font_color));
	font_im[5].loadFromCurrentSurface(renderer);

	font_im[6].setSurface(TTF_RenderText_Solid(font,"Vous devez poser du vert",font_color));
	font_im[6].loadFromCurrentSurface(renderer);

	font_im[7].setSurface(TTF_RenderText_Solid(font,"Vous devez poser du bleu",font_color));
	font_im[7].loadFromCurrentSurface(renderer);

	font_im[8].setSurface(TTF_RenderText_Solid(font,"Vous devez poser du jaune",font_color));
	font_im[8].loadFromCurrentSurface(renderer);

	font_im[9].setSurface(TTF_RenderText_Solid(font,"Vous devez poser du rouge",font_color));
	font_im[9].loadFromCurrentSurface(renderer);

	font_im[10].setSurface(TTF_RenderText_Solid(font,"Il doit poser du vert",font_color));
	font_im[10].loadFromCurrentSurface(renderer);

	font_im[11].setSurface(TTF_RenderText_Solid(font,"Il doit poser du bleu",font_color));
	font_im[11].loadFromCurrentSurface(renderer);

	font_im[12].setSurface(TTF_RenderText_Solid(font,"Il doit poser du jaune",font_color));
	font_im[12].loadFromCurrentSurface(renderer);

	font_im[13].setSurface(TTF_RenderText_Solid(font,"Il doit poser du rouge",font_color));
	font_im[13].loadFromCurrentSurface(renderer);

	font_im[14].setSurface(TTF_RenderText_Solid(font,"Bravo vous avez gagner !",font_color));
	font_im[14].loadFromCurrentSurface(renderer);

	font_im[15].setSurface(TTF_RenderText_Solid(font,"Bravo ! La victoire est a vous !",font_color));
	font_im[15].loadFromCurrentSurface(renderer);

	font_im[16].setSurface(TTF_RenderText_Solid(font,"Le joueur 2 a gagne !",font_color));
	font_im[16].loadFromCurrentSurface(renderer);

	font_im[17].setSurface(TTF_RenderText_Solid(font,"Le joueur 3 a gagne !",font_color));
	font_im[17].loadFromCurrentSurface(renderer);

    font_im[18].setSurface(TTF_RenderText_Solid(font,"Voulez-vous rejouer ?",font_color));
	font_im[18].loadFromCurrentSurface(renderer);

    font_im[19].setSurface(TTF_RenderText_Solid(font,"Rejouer",font_color));
	font_im[19].loadFromCurrentSurface(renderer);

    font_im[20].setSurface(TTF_RenderText_Solid(font,"Quitter",font_color));
	font_im[20].loadFromCurrentSurface(renderer);
}

void SdlMonde::afficherCartes(unsigned int k, char c, unsigned int choixAffichage){

    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    unsigned int dim=12, i;

//affiche la pioche
    im_carte[4*12+5].draw(renderer,dimx/2+90,dimy/2-130,150,250);

//affiche la carte du milieu
    unsigned int coulMil=m.milieu.retourCarte(m.milieu.retourNbCartes()-1).retourCouleur(); //on met dans coulMil la valeur de la couleur de la carte du milieu
    unsigned int nbMil=m.milieu.retourCarte(m.milieu.retourNbCartes()-1).retourNombre(); //on met dans nbMil la valeur du nombre de la carte du milieu
    if (coulMil<noir) im_carte[coulMil*dim + nbMil-1].draw(renderer,dimx/2-50,dimy/2-100,100,150); //pour poser les cartes de couleur
    else if(nbMil==13) im_carte[48].draw(renderer,dimx/2-50,dimy/2-100,100,150); //pour poser le bob
    else im_carte[49].draw(renderer,dimx/2-50,dimy/2-100,100,150);

    //affiche le texte "C'est votre tour", "Tour du joueur 2" , Tour du joueur 3 en haut
    SDL_Rect positionTitre;
    positionTitre.x = 150;positionTitre.y = 5;positionTitre.w = dimx-300;positionTitre.h = 80;
    if(k==0)SDL_RenderCopy(renderer,font_im[0].getTexture(),NULL,&positionTitre);
    if(k==1)SDL_RenderCopy(renderer,font_im[1].getTexture(),NULL,&positionTitre);
    if(k==2)SDL_RenderCopy(renderer,font_im[2].getTexture(),NULL,&positionTitre);

    //affiche le texte "vous devez poser du vert/bleu/jaune/rouge" ou "Pioche ou poser +2 ton +4"
    positionTitre.x = 190;positionTitre.y = 85;positionTitre.w = dimx-400;positionTitre.h = 50;
    if(choixAffichage!=0 || c!='0')
    {
        if(choixAffichage==0)
        {
            if(k!=0)
            {
                if(c=='v')SDL_RenderCopy(renderer,font_im[10].getTexture(),NULL,&positionTitre);
                else if(c=='b')SDL_RenderCopy(renderer,font_im[11].getTexture(),NULL,&positionTitre);
                else if(c=='j')SDL_RenderCopy(renderer,font_im[12].getTexture(),NULL,&positionTitre);
                else if(c=='r')SDL_RenderCopy(renderer,font_im[13].getTexture(),NULL,&positionTitre);
            }
            else
            {
                if(c=='v')SDL_RenderCopy(renderer,font_im[6].getTexture(),NULL,&positionTitre);
                else if(c=='b')SDL_RenderCopy(renderer,font_im[7].getTexture(),NULL,&positionTitre);
                else if(c=='j')SDL_RenderCopy(renderer,font_im[8].getTexture(),NULL,&positionTitre);
                else if(c=='r')SDL_RenderCopy(renderer,font_im[9].getTexture(),NULL,&positionTitre);
            }
        }
        else
        {
            if(!m.j[k].estUnOrdinateur)
            {
                if(choixAffichage==1) SDL_RenderCopy(renderer,font_im[4].getTexture(),NULL,&positionTitre);
                if(choixAffichage==2) SDL_RenderCopy(renderer,font_im[5].getTexture(),NULL,&positionTitre);
            }
        }
    }

//affiche les cartes de l'adversaire j1 (ordinateur)
    for(i=0;i<m.j[1].nombreCartesJoueur;i++)
    {
        im_carte[4*12+3].draw(renderer,dimx-160,100+50*i,150,100);
    }

//affiche les cartes de l'adversaire j2(ordinateur)
    for(i=0;i<m.j[2].nombreCartesJoueur;i++)
    {
        im_carte[4*12+4].draw(renderer,10,100+50*i,150,100);
    }

    //affiche les cartes du joueur qui est entrain de jouer (j0)
    for(i=0;i<m.j[0].nombreCartesJoueur;i++)
    {
        unsigned int coulJoueur=m.j[0].retourCarteJoueur(i).retourCouleur();
        unsigned int nbJoueur=m.j[0].retourCarteJoueur(i).retourNombre();
        if (coulJoueur<noir) im_carte[coulJoueur*dim+ nbJoueur-1].draw(renderer,170+100*i,dimy-180,100,150);
        else if (nbJoueur==13) im_carte[4*dim].draw(renderer,170+100*i,dimy-180,100,150); //pose les bobs du joueur
        else if (nbJoueur==14) im_carte[4*dim+1].draw(renderer,170+100*i,dimy-180,100,150); //pose les +4
    }
    SDL_RenderPresent(renderer); // On met à jour notre fenêtre
}

char SdlMonde::choisirCouleur(){
char c='0';
    SDL_Event events;

    unsigned int taille=90; //pour laisser la place décrire le titre : "Quelle couleur voulez-vous choisir ?"
    unsigned int tailleDeux=taille/2;

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_Rect positionTitre;
    positionTitre.x = 150;positionTitre.y = 5;positionTitre.w = dimx-300;positionTitre.h = 80;
    SDL_RenderCopy(renderer,font_im[3].getTexture(),NULL,&positionTitre);

        SDL_Rect r = { 0 ,taille,dimx/2 , dimy/2-tailleDeux  };
        SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 ); //carre rouge
        SDL_RenderFillRect( renderer, &r );

        r = { dimx/2 , taille , dimx/2 , dimy/2-tailleDeux  };
        SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 ); //carre bleu
        SDL_RenderFillRect( renderer, &r );

        r = { 0 , dimy/2+tailleDeux , dimx/2 , dimy/2-tailleDeux  };
        SDL_SetRenderDrawColor( renderer, 255, 255, 0, 255 ); //carre jaune
        SDL_RenderFillRect( renderer, &r );

        r = { dimx/2 , dimy/2+tailleDeux , dimx/2 , dimy/2-tailleDeux  };
        SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); //carre vert
        SDL_RenderFillRect( renderer, &r );

    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderPresent(renderer); // On met à jour notre fenêtre
   
   do
   {
    SDL_WaitEvent(&events);
    if(events.type == SDL_QUIT) c = '1';
    if(events.type == SDL_MOUSEBUTTONUP)
    if(events.button.button == SDL_BUTTON_LEFT && events.button.clicks >= 2)
    {
            double x= events.button.x;
            double y= events.button.y;

            if(x>dimx/2 && x<dimx && y>dimy/2+tailleDeux && y<dimy) c='v'; //l'utilisateur choisi la couleur vert
            else if(x>0 && x<dimx/2 && y>dimy/2+tailleDeux && y<dimy) c='j'; //l'utilisateur choisi la couleur jaune
            else if(x>dimx/2 && x<dimx && y>taille && y<dimy/2+tailleDeux) c='b'; //l'utilisateur choisi la couleur bleu
            else if(x>0 && x<dimx/2 && y>taille && y<dimy/2-tailleDeux) c='r'; //l'utilisateur choisi la couleur rouge
    }
   }while(c=='0');

    return c;
}

void SdlMonde::poserBob(int &k,char &couleur){
    if(m.j[k].estUnOrdinateur) couleur=m.demanderCouleurOrdi(k); //si le joueur suivant est un Ordinateur
    else couleur=choisirCouleur(); //si le joueur est un humain

    //on passe au joueur suivant
    m.passerAuJoueurSuivant(k);
    afficherCartes(k,couleur);
}

bool SdlMonde::peutPoser(const Joueur &j,unsigned int indice, char &c){
  Couleur coulCarteJoueur=j.retourCarteJoueur(indice).retourCouleur();

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
        return false;
    }
  }
  else if(coulCarteJoueur==m.milieu.retourCarte(m.milieu.retourNbCartes()-1).retourCouleur())
  {
    return true;
  }
  else if(j.retourCarteJoueur(indice).retourNombre()==m.milieu.retourCarte(m.milieu.retourNbCartes()-1).retourNombre())
  {
    return true;
  }
  else if(coulCarteJoueur==noir)
  {
    return true;
  }
  else
  {
    return false;
  }

}

int SdlMonde::choisirCarteJoueurSdl(unsigned int k,char &c){
    int indice=-2;
    SDL_Event events;
    SDL_WaitEvent(&events);

    if(events.type == SDL_MOUSEBUTTONUP)
    {
        if(events.button.button == SDL_BUTTON_LEFT && events.button.clicks == 1)
        {
            double x= events.button.x;
            double y= events.button.y;

            if (k==0 && x>dimx/2+90 && x<dimx/2+90+150 && y>dimy/2-130 && y<dimy/2-130+250)
            {
                indice = -1;
            }
            for(unsigned int i=0;i<m.j[0].nombreCartesJoueur;i++)
            if((y>dimy-180 && y<dimy-30)
            && x>170+100*i  &&  x<170+100*(i+1)
            && peutPoser(m.j[k],i,c) )
            {
                indice= i;
            }
        }
    }
    return indice;
}

void SdlMonde::poserPlusDeuxJoueurSdl(int &k,unsigned int nbDeCarteAPiocher){
    unsigned int i;
    bool ok=false;
    if(m.j[k].possedeCarteNombreJoueur(12)) //si le joueur suivant possede un ou plusieurs +2 ou un +4
    {
        while(!ok)
        {
        //on lui demande s'il veut poser son +2 ou piocher en appuyant sur 0
            afficherCartes(k,'0',1);
            SDL_Event events;
            SDL_PollEvent(&events);
            if(events.type == SDL_MOUSEBUTTONUP && events.button.button == SDL_BUTTON_LEFT && events.button.clicks == 1)
            {
                double x= events.button.x;
                double y= events.button.y;

                if (k==0 && x>dimx/2+90 && x<dimx/2+90+150 && y>dimy/2-130 && y<dimy/2-130+250) //si il veut piocher
                {
                    for(i=0;i<nbDeCarteAPiocher;i++)
                    {
                        m.p.piocher(m.j[k]);
                    }
                    m.passerAuJoueurSuivant(k);
                    ok=true;
                }
                for(unsigned int i=0;i<m.j[0].nombreCartesJoueur;i++)
                    if((y>dimy-180 && y<dimy-30)
                       && x>170+100*i  &&  x<170+100*(i+1)
                       && m.j[k].retourCarteJoueur(i).retourNombre()==12 )
                    {
                            m.milieu.ajouterCarte(m.j[k].retourCarteJoueur(i)); //on pose carte que le joueur a choisi au milieu
                            m.j[k].supprimerCarteJoueur(i); //on la supprime de la main du joueur
                            sleep(2);
                            ok=true;
                            afficherCartes(k);
                            nbDeCarteAPiocher+=2;
                            poserPlusDeuxSdl(k,nbDeCarteAPiocher);
                    }

            }
        }
    }

    else //si le joueur n'a pas de +2 on lui fait piocher directement
    {
        for(i=0;i<nbDeCarteAPiocher;i++)
        {
            m.p.piocher(m.j[k]);
        }
        m.passerAuJoueurSuivant(k);
    }
}

void SdlMonde::poserPlusDeuxOrdiSdl(int &k,unsigned int nbDeCarteAPiocher){
    unsigned int i,compt=0;
    unsigned int tab[m.j[k].nombreCartesJoueur];

    for( i=0;i<m.j[k].nombreCartesJoueur;i++)
        if(m.j[k].retourCarteJoueur(i).retourNombre()==12)
        {
            tab[compt]=i;
            compt++;
        }
    if(compt==0) //l'ordinateur ne possède pas de +2
    {
        for(unsigned int i=0;i<nbDeCarteAPiocher;i++)
        {
            m.p.piocher(m.j[k]);
        }
        m.passerAuJoueurSuivant(k);
        afficherCartes(k);
        sleep(2);
    }
    else //l'ordinateur possède un ou plusieurs +2
    {
        m.milieu.ajouterCarte(m.j[k].retourCarteJoueur(tab[0]));
        m.j[k].supprimerCarteJoueur(tab[0]);

        afficherCartes(k);
        sleep(2);

        nbDeCarteAPiocher+=2;
        poserPlusDeuxSdl(k,nbDeCarteAPiocher);
    }

}

void SdlMonde::poserPlusDeuxSdl(int &k,unsigned int nbDeCarteAPiocher){
    //on passe au joueur suivant
    m.passerAuJoueurSuivant(k);

    if(m.j[k].estUnOrdinateur) poserPlusDeuxOrdiSdl(k,nbDeCarteAPiocher);
    else poserPlusDeuxJoueurSdl(k,nbDeCarteAPiocher);
}

void SdlMonde::poserPlusQuatreJoueurSdl(int &k,unsigned int &nbDeCarteAPiocher,char couleur){
    unsigned int i=0;
    bool ok=false;
    if(m.j[k].possedeCarteNombreJoueur(14)) //si le joueur suivant possede un ou plusieurs +4
    {
        while(!ok)
        {
            afficherCartes(k,couleur,2);
            SDL_Event events;
            SDL_PollEvent(&events);
            if(events.type == SDL_MOUSEBUTTONUP)
            {
                if(events.button.button == SDL_BUTTON_LEFT && events.button.clicks == 1)
                {
                    double x= events.button.x;
                    double y= events.button.y;

                    if (k==0 && x>dimx/2+90 && x<dimx/2+90+150 && y>dimy/2-130 && y<dimy/2-130+250)
                    {
                        for(i=0;i<nbDeCarteAPiocher;i++)
                            m.p.piocher(m.j[k]);
                        m.passerAuJoueurSuivant(k);
                        afficherCartes(k,couleur,2);
                        ok=true;
                    }
                    else
                    {
                        for(unsigned int i=0;i<m.j[0].nombreCartesJoueur;i++)
                        if((y>dimy-180 && y<dimy-30)
                        && x>170+100*i  &&  x<170+100*(i+1)
                        && m.j[k].retourCarteJoueur(i).retourNombre()==14 ) //si le joueur pose un +4
                        {
                            ok=true;
                            m.milieu.ajouterCarte(m.j[k].retourCarteJoueur(i)); //on pose le +4 au milieu
                            m.j[k].supprimerCarteJoueur(i); //on le supprime de la main du joueur
                            nbDeCarteAPiocher+=4;
                            poserPlusQuatreSdl(k,nbDeCarteAPiocher,couleur);
                        }
                    }
                }
            }

        }
    }
    else //si le joueur possede pas de +4
    {
        for(i=0;i<nbDeCarteAPiocher;i++)
        {
            m.p.piocher(m.j[k]);
        }
        m.passerAuJoueurSuivant(k);
    }
}

void SdlMonde::poserPlusQuatreOrdiSdl(int &k,unsigned int nbDeCarteAPiocher,char couleur){
    if(m.j[k].possedeCarteNombreJoueur(14)) //si l'ordinateur possede un +4
    {
        //le pose directement (la derniere carte est forcément un +4)
        m.milieu.ajouterCarte(m.j[k].retourCarteJoueur(m.j[k].nombreCartesJoueur-1));
        m.j[k].supprimerCarteJoueur(m.j[k].nombreCartesJoueur-1);
        nbDeCarteAPiocher+=4;
        poserPlusQuatreSdl(k,nbDeCarteAPiocher,couleur);
    }
    else //l'ordinateur ne possède pas de +2 ou de +4
    {
        for(unsigned int i=0;i<nbDeCarteAPiocher;i++)
        {
            m.p.piocher(m.j[k]);
        }
        m.passerAuJoueurSuivant(k);
    }
}

void SdlMonde::poserPlusQuatreSdl(int &k,unsigned int nbDeCarteAPiocher, char &couleur) {

    if(m.j[k].estUnOrdinateur) couleur=m.demanderCouleurOrdi(k); //si le joueur suivant est un Ordinateur
    else couleur=choisirCouleur(); //si le joueur est un humain

    m.passerAuJoueurSuivant(k);
    if(m.j[k].estUnOrdinateur) poserPlusQuatreOrdiSdl(k,nbDeCarteAPiocher,couleur);
    else poserPlusQuatreJoueurSdl(k,nbDeCarteAPiocher,couleur);
}

void SdlMonde::jouerSdl(int &k,char &c){
    int i=-2;

    if(m.j[k].estUnOrdinateur)
    {
        i=m.choisiCarteOrdinateur(k,c);
        sleep(2);
    }
    else i=choisirCarteJoueurSdl(k,c);
    if (i==-1) //le joueur a decider de piocher
    {
        m.p.piocher(m.j[k]);
        m.passerAuJoueurSuivant(k);
        afficherCartes(k,c);
    }
    else if(i!=-2)
    {
        int temp=m.j[k].retourCarteJoueur(i).retourNombre();
        m.milieu.ajouterCarte(m.j[k].retourCarteJoueur(i));
        m.j[k].supprimerCarteJoueur(i);
        if(temp<10) m.passerAuJoueurSuivant(k);
        else
        {
            switch (temp)
            {
                case 10: //changement de sens
                m.poserChangerSens(k);
                break;
                case 11: //passe tour
                m.poserPasseTour(k);
                break;
                case 12: //+2
                poserPlusDeuxSdl(k,2);
                break;
                case 13: //bob
                c='0';
                poserBob(k,c);
                break;
                case 14: //+4
                c='0';
                poserPlusQuatreSdl(k,4,c);
                break;
            }
        }
        afficherCartes(k,c);
   }
}

void SdlMonde::afficherBoucle() {
    bool quit=false;
    char c = '0'; //change de valeur quand le joueur pose un bob ou un +4 (peut être egale à v/b/j/r)
    int  k = 0; //numero du joueur qui est entrain de joueur
    SDL_Event e;

//fonction qui permet de mélanger la pioche + de distribuer 7 cartes axu joueurs
    m.commercerLaPartie();
    //testerSdl();
//on affiche les Cartes + le fond bleu clair
    afficherCartes(k,c);

    while (!gagnerSdl(quit) || !quit) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) break;
        jouerSdl(k,c);
   }
}

void SdlMonde::afficherDetruit() {
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SdlMonde::afficher() {
    afficherInit();
    afficherBoucle();
    afficherDetruit();
}

void SdlMonde::testerSdl(){
   // m.commercerLaPartie();
   /*
    int k=0;
    char c='0';
    Carte c1(14,noir);
    Carte c2(2,bleu);
    Carte c3(4,rouge);
    Carte c4(13,noir); //bob
    Carte c5(12,rouge); //+2 bleu
 //test poser +2
    m.milieu.modifierCarte(0,c3);
    m.j[0].modifierCarteJoueur(5,c5);
    m.j[0].modifierCarteJoueur(6,c1);
    for(unsigned int i=0;i<7;i++)
    {
        m.j[1].modifierCarteJoueur(i,c2);
        m.j[2].modifierCarteJoueur(i,c2);
    }
	*/

/*
    m.milieu.modifierCarte(0,c3);
    for(unsigned int i=0;i<7;i++)
    {
        m.j[1].modifierCarteJoueur(i,c2);
        m.j[2].modifierCarteJoueur(i,c2);
    }
    m.j[0].modifierCarteJoueur(5,c4);
    m.j[0].modifierCarteJoueur(6,c4);
    m.j[1].modifierCarteJoueur(6,c4);
*/
 //tester le fonction gagnerSdl
        Carte c1(14,noir);
        Carte c2(2,bleu);
        Carte c3(4,rouge);
        Carte c4(13,noir);
        Carte c5(12,rouge); //+2 bleu

        m.milieu.modifierCarte(0,c2);
        for(unsigned int i=0;i<7;i++)
        {
            m.j[0].modifierCarteJoueur(i,c2);          
            m.j[1].modifierCarteJoueur(i,c2);
            m.j[2].modifierCarteJoueur(i,c2);
        }
        m.j[0].supprimerCarteJoueur(6);
        m.j[0].supprimerCarteJoueur(5);
        m.j[0].supprimerCarteJoueur(4);
        m.j[0].supprimerCarteJoueur(3);
        m.j[0].supprimerCarteJoueur(2);
        m.j[0].supprimerCarteJoueur(1);
        m.j[0].modifierCarteJoueur(0,c2);

}

bool SdlMonde::gagnerSdl(bool &quitter){
    unsigned int k;
    bool rejouer=false,gagner=false;
    char c='0';
    for(k=0;k<m.nbDeJoueur;k++)
        if(m.j[k].nombreCartesJoueur==0)
        {
            SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
            SDL_RenderClear(renderer);

            SDL_Rect positionTitre;
            positionTitre.x = 150;positionTitre.y = 5;positionTitre.w = dimx-300;positionTitre.h = 80;
            SDL_RenderCopy(renderer,font_im[15+k].getTexture(),NULL,&positionTitre); //affiche le text "Le joueur 1/2 ou 3 a gagne"
            positionTitre.x +=30; positionTitre.y += dimy/2-100 -120; positionTitre.h-=5; positionTitre.w -= 30; //positionTitre.h =;
            SDL_RenderCopy(renderer,font_im[18].getTexture(),NULL,&positionTitre); //affiche "voulez-vous rejouer ?"


            SDL_Rect r = { positionTitre.x-10 ,positionTitre.y-10, positionTitre.w+10 , dimy/2+150  };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 ); //rectangle noir
            SDL_RenderDrawRect( renderer, &r ); //creer le carre centrale

            r = { dimx/2-100 ,dimy/2-100,300 , 100  };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 ); //rectangle noir
            SDL_RenderDrawRect( renderer, &r ); //creer une case pour le bouton rejouer
            positionTitre.x =dimx/2-100 ; positionTitre.y =dimy/2-100; positionTitre.w = 300; positionTitre.h =100;
            SDL_RenderCopy(renderer,font_im[19].getTexture(),NULL,&positionTitre); //affiche "Rejouer"

            r = { dimx/2-100 ,dimy/2+150,300 , 100  };
            SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 ); //rectangle noir
            SDL_RenderDrawRect( renderer, &r ); //creer une case pour le bouton rejouer
            positionTitre.x =dimx/2-100 ; positionTitre.y =dimy/2+150; positionTitre.w = 300; positionTitre.h =100;
            SDL_RenderCopy(renderer,font_im[20].getTexture(),NULL,&positionTitre); //affiche "Rejouer"

            SDL_RenderPresent(renderer);

            gagner=true;
            SDL_Event e;
            do
            {
                SDL_PollEvent(&e);
                if (e.type == SDL_QUIT) quitter=true;

                if(e.type == SDL_MOUSEBUTTONUP)
                {
                    if(e.button.button == SDL_BUTTON_LEFT && e.button.clicks == 1)
                    {
                        double x= e.button.x;
                        double y= e.button.y;

                        if(x>dimx/2-100 && x<dimx/2-100+300 &&  y>dimy/2-100 && y<dimy/2/*-100 +100 */) rejouer=true;
                        else if(x>dimx/2-100 && x<dimx/2-100+300 &&  y>dimy/2+150 && y<dimy/2 +150+100) quitter=true;
                    }
                }
            }while(!quitter && !rejouer);

            if(rejouer)
            {
                for(k=0;k<m.nbDeJoueur;k++) //on supprime toutes les Cartes des joueurs
                    m.j[k].supprimerJoueur();
                m.milieu.supprimerCartes(); //on supprime les cartes au milieu
                m.p.supprimerCartes(); //on suppprime la pioche
                m.commercerLaPartie();
                m.sensDuJeuChanger=false;
                cout<<"ok";
            }
        }
    return gagner;
}

