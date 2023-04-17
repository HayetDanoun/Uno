#ifndef JOUEUR_H
#define JOUEUR_H
#include "Carte.h"

class Joueur
{
        private:
    Carte *carteJoueur;


    public :
    unsigned int nombreCartesJoueur;
    bool estUnOrdinateur;

    /**
    @brief Constructeur par défaut : initialise le nombre de cartes d'un joueur à 0, l'action de l'ordinateur et estSonTour à faux.
    @param none

    Example code block
    @code
    Joueur j;
    @endcode
    */
    Joueur();

    /**
    @brief Deconstructeur : déallocation de la mémoire du tableau de Carte et mise à jour du nombre de cartes d'un joueur à 0.
    @param none

    */
    ~Joueur();

    /**
    @brief Supprime le joueur qui a perdu.
    @param none
    @return none

    Example code block
    @code
    Joueur j;
    j.supprimerJoueur();
    @endcode
    */
    void supprimerJoueur();

    /**
    @brief Retourne la carte d'un joueur.
    @param entier
    @return Carte

    Example code block
    @code
    Joueur j;
    j.retournerCarteJoueur(3);
    @endcode
    */
    Carte& retourCarteJoueur(unsigned int i) const;

    /**
    @brief Modifie la carte d'un joueur.
    @param entier, Carte
    @return none

    Example code block
    @code
    Joueur j;
    Carte c;
    j.modifierCarteJoueur(c);
    @endcode
    */
    void modifierCarteJoueur(unsigned int i,const Carte &c);

    /**
    @brief Ajoute une carte à un joueur.
    @param Carte
    @return none

    Example code block
    @code
    Joueur j;
    Carte c;
    j.ajouterCarteJoueur(c);
    @endcode
    */
    void ajouterCarteJoueur(const Carte &c);

    /**
    @brief Retourne l'indice de la carte choisie par un joueur.
    @param none
    @return entier

    Example code block
    @code
    Joueur j;
    j.indiceDeLaCarteChoisie();
    @endcode
    */
    unsigned int indiceDeLaCarteChoisie();

    /**
    @brief Supprime la carte d'un joueur.
    @param entier
    @return none

    Example code block
    @code
    Joueur j;
    j.supprimerCarteJoueur(3);
    @endcode
    */
    void supprimerCarteJoueur(unsigned int i); //pas bien coder n'enleve pas la carte choisie car le joueur

    /**
    @brief Trie les cartes d'un joueur par couleur et numéro de cartes (tri par insertion).
    @param none
    @return none

    Example code block
    @code
    Joueur j;
    j.trierCarteJoueur();
    @endcode
    */
    void trierCarteJoueur();

    /**
    @brief Vérifie quel numéro de carte un joueur possède.
    @param entier
    @return bool

    Example code block
    @code
    Joueur j;
    j.possedeCarteNombreJoueur(3);
    @endcode
    */
    bool possedeCarteNombreJoueur(unsigned int nb);

    /**
    @brief Compte le nombre de couleur qu'un joueur possède.
    @param entier
    @return none

    Example code block
    @code
    Joueur j;
    j.compteCouleur(2);
    @endcode
    */
    void compteCouleur(unsigned int tab[4]);

    /**
    @brief Retourne la meilleure couleur que l'ordinateur doit jouer pour gagner.
    @param none
    @return caractère

    Example code block
    @code
    Joueur j;
    j.meilleurCouleur();
    @endcode
    */
    char meilleurCouleur();

    /**
    @brief Affiche la carte d'un joueur.
    @param none
    @return none

    Example code block
    @code
    Joueur j;
    j.afficherCarteJoueur(3);
    @endcode
    */
    void afficherCarteJoueur();

    /**
    @brief Teste les fonctionnalités de la classe Joueur.
    @param none
    @return none

    Example code block
    @code
    Joueur j;
    j.TestJoueur();
    @endcode
    */
    void TestJoueur();

};



#endif // JOUEUR_H
