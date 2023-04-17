#ifndef _JEU_H
#define _JEU_H

#include "Monde.h"

class Jeu {

private :

	Monde monde;
	//Joueur joueur;
	//Cartes pioche;
    //Carte carte;

public :

    /**
    @brief Constructeur par défaut : initialise le monde.
    @param none

    Example code block
    @code
    Jeu j;
    @endcode
    */
    Jeu ();


    /**
    @brief Retourne le monde.
    @param none
    @return Monde

    Example code block
    @code
    jeu j;
    j.getMonde();
    @endcode
    */
    Monde& getMonde ();


    /**
    @brief Retourne le monde.
    @param none
    @return Monde

    Example code block
    @code
    Jeu j;
    j.getConstMonde();
    @endcode
    */
    const Monde& getConstMonde () const;

    /**
    @brief Retourne le nombre de joueurs.
    @param none
    @return entier

    Example code block
    @code
    Jeu j;
    j.getNombreDeJoueur();
    @endcode
    */
    int getNombreDeJoueur() const;

    /**
    @brief Retourne les actions du clavier.
    @param caractere
    @return bool

    Example code block
    @code
    Jeu j;
    j.actionClavier('p');
    @endcode
    */
    bool actionClavier(const char touche);

};

#endif

