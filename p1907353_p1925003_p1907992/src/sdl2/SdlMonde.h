#ifndef SLDMONDE_H_INCLUDED
#define SLDMONDE_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
using namespace std;

#include "Monde.h"

//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
    Image () ;
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



class SdlMonde{
    private:

    Monde m;
    unsigned int dimx, dimy; //les dimensions de l'image



    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

    SDL_Window * window;
    SDL_Renderer * renderer;

    Image im_carte[54]; //tableaux des differents cartes de Uno (+les cartes le dos des cartes + une photo de la pioche)

    TTF_Font * font;
    Image font_im[20]; //tableaux des differents phrases écrit tout au long de la partie (ex: "C'est votre tour", "Choisir une couleur"...)
    SDL_Color font_color; //tableaux des differentes couleurs des differents phrases écrit tout au long de la partie (ici tout en noir )

    bool touche;

     /**
    @brief Initialisation de la SDL et création de la fenêtre.
    @param none
    @return none

    Example code block
    @code
    SdlMonde s;
    s.afficherInit();
    @endcode
    */
    void afficherInit();

     /**
    @brief Détruit l'image.
    @param none
    @return none

    Example code block
    @code
    SdlMonde s;
    s.afficherDetruit();
    @endcode
    */
    void afficherDetruit();

    /**
    @brief Affiche toutes les cartes du jeu.
    @param entier, caractère, entier
    @return none

    Example code block
    @code
    SdlMonde s;
    s.afficherCartes(1,'0',0);
    @endcode
    */
    void afficherCartes(unsigned int k,char c='0',unsigned int choixAffichage=0);

    /**
    @brief Crée une boucle pour maintenir l'image visible sur la fenêtre.
    @param none
    @return none

    Example code block
    @code
    SdlMonde s;
    s.afficherBoucle();
    @endcode
    */
    void afficherBoucle();

    /**
    @brief Vérifie quelles cartes un joueur peut poser.
    @param Joueur, entier, caractère
    @return booléen

    Example code block
    @code
    sdMonde s;
    Joueur j;
    s.peutPoser(j,1,'v');
    @endcode
    */
    bool peutPoser(const Joueur &j,unsigned int indice, char &c);

    /**
    @brief Le joueur pose un +2;
    @param entier, entier
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusDeuxJoueurSdl(1,2);
    @endcode
    */
    void poserPlusDeuxJoueurSdl(int &k,unsigned int nbDeCarteAPiocher);

    /**
    @brief Appelle poserPlusDeuxJoueurSdl et poserPlusDeuxOrdiSdl en fonction de qui est entrain de jouer.
    @param  entier, entier
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusDeuxSdl(1,2);
    @endcode
    */
    void poserPlusDeuxSdl(int &k,unsigned int nbDeCarteAPiocher);

    /**
    @brief L'ordinateur pose un +2.
    @param entier, entier
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusDeuxOrdiSdl(1,2);
    @endcode
    */
    void poserPlusDeuxOrdiSdl(int &k,unsigned int nbDeCarteAPiocher);

    /**
    @brief Retourne la couleur choisie.
    @param none
    @return caractère

    Example code block
    @code
    sdMonde s;
    s.choisirCouleur();
    @endcode
    */
    char choisirCouleur();

    /**
    @brief Le joueur pose un bob.
    @param entier
    @return caractère

    Example code block
    @code
    sdMonde s;
    s.poserBobJoueur(2);
    @endcode
    */
    char poserBobJoueur(int k);

    /**
    @brief Le joueur ou l'ordinateur pose un bob.
    @param entier, caractère
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserBob(2,'v');
    @endcode
    */
    void poserBob(int &k, char &couleur);

    /**
    @brief Apelle poserPlusQuatreJoueurSdl ou poserPlusQuatreOrdiSdl en fontion de qui est entrain de jouer.
    @param entier, entier
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusQuatreSdl(1,2);
    @endcode
    */
    void poserPlusQuatreSdl(int &k,unsigned int nbDeCarteAPiocher, char &couleur);

    /**
    @brief Le joueur pose un +4.
    @param entier, entier, caractère
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusQuatreJoueurSdl(1,2,'j');
    @endcode
    */
    void poserPlusQuatreJoueurSdl(int &k,unsigned int &nbDeCarteAPiocher,char couleur);

    /**
    @brief L'ordinateur pose un +4.
    @param entier, entier, caractère
    @return none

    Example code block
    @code
    sdMonde s;
    s.poserPlusQuatreOrdiSdl(1,2,'b');
    @endcode
    */
    void poserPlusQuatreOrdiSdl(int &k,unsigned int nbDeCarteAPiocher,char couleur);

    /**
    @brief Retourne l'indice de la carte choisie par un joueur.
    @param entier, caractère
    @return caractère

    Example code block
    @code
    sdMonde s;
    s.choisirCarteJoueurSdl(2,'b');
    @endcode
    */
    int choisirCarteJoueurSdl(unsigned int k,char &c);

    /**
    @brief Lance une partie de jeu en SDL.
    @param entier, caractère
    @return none

    Example code block
    @code
    sdMonde s;
    s.jouerSdl(2,'v');
    @endcode
    */
    void jouerSdl(int &k,char &c);

    /**
    @brief Retourner le gagnant de la partie en SDL.
    @param booléen
    @return booléen

    Example code block
    @code
    sdMonde s;
    bool q;
    s.gagnerSdl(q);
    @endcode
    */
    bool gagnerSdl(bool &quitter);
    public:

    /**
    @brief Test les fonctionnalités de la SDL.
    @param none
    @return none

    Example code block
    @code
    sdMonde s;
    s.testerSdl();
    @endcode
    */
    void testerSdl();

    /**
    @brief Affiche le jeu en mode SDL.
    @param none
    @return none

    Example code block
    @code
    sdMonde s;
    s.afficher();
    @endcode
    */
    void afficher ();

};



#endif // SLDWORLD_H_INCLUDED
