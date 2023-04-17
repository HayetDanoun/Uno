#ifndef CARTES_H
#define CARTES_H
#include "Carte.h"
#include "Joueur.h"

class Cartes
{
    private:
    Carte *tab;


    public:
    unsigned int nbCartes;

    /**
    @brief Supprime les cartes que le joueur a joué.
    @param none
    @return none

    Example code block
    @code
    Cartes carte;
    carte.supprimerCartes();
    @endcode
    */
    void supprimerCartes();

     /**
    @brief Retourne une carte.
    @param entier
    @return Carte

    Example code block
    @code
    Cartes carte;
    carte.retourCarte(2);
    @endcode
    */
    Carte& retourCarte(unsigned int i) const;

    /**
    @brief Retourne le nombre de la derniere carte.
    @param none
    @return entier

    Example code block
    @code
    Cartes carte;
    carte.retourDerniereCarteNombre();
    @endcode
    */
    unsigned int retourDerniereCarteNombre() const;

    /**
    @brief Retourne le nombre de cartes.
    @param none
    @return entier

    Example code block
    @code
    Cartes carte;
    carte.retourNbCartes();
    @endcode
    */
    unsigned int retourNbCartes();
    /**
    @brief Retourne la couleur de la derniere carte.
    @param none
    @return Couleur

    Example code block
    @code
    Cartes carte;
    carte.retourDerniereCarteCouleur();
    @endcode
    */
    Couleur retourDerniereCarteCouleur() const;

     /**
    @brief Constructeur par défaut : initialise le nomre de cartes dans la pioche à ;
    @param none

    Example code block
    @code
    Cartes carte;
    @endcode
    */
    Cartes();

     /**
    @brief Destructeur : déallocation de la mémoire du tableau de pixels et mise à jour du nombre des cartes de la pioche à 0.
    @param none
    */
    ~Cartes();


     /**
    @brief Modifie une carte la pioche.
    @param entier positif, Cartes
    @return none

    Example code block
    @code
    Cartes carte;
    modifierCartePioche(2,carte);
    @endcode
    */
    void modifierCarte(unsigned int i,const Carte &c);

     /**
    @brief Mélange les cartes de la pioche.
    @param none
    @return none

    Example code block
    @code
    Cartes carte;
    carte.melangerPioche();
    @endcode
    */
    void melangerPioche();

     /**
    @brief Initialise la pioche.
    @param none
    @return none

    Example code block
    @code
    Cartes carte;
    carte.initPioche();
    @endcode
    */
    void initPioche();

     /**
    @brief Ajoute une carte dans la pioche.
    @param Cartes
    @return none

    Example code block
    @code
    Cartes carte;
    carte.ajouterCartePioche(carte);
    @endcode
    */
    void ajouterCarte(const Carte &c);

    /**
    @brief Echange deux cartes entre elles.
    @param Cartes
    @return none

    Example code block
    @code
    Cartes carte1;
    Cartes carte2;
    carte1.echangeCartes(carte2);
    @endcode
    */
    void echangeCartes(Cartes &PiocheDuMilieu);


     /**
    @brief Supprime la dernière carte.
    @param none
    @return none

    Example code block
    @code
    Cartes carte;
    carte.supprimerLaDerniereCarte();
    @endcode
    */
    void supprimerDerniereCarte();

    /**
    @brief Fait piocher des cartes au joueur.
    @param Joueur
    @return none

    Example code block
    @code
    Cartes carte;
    Joueur j;
    carte.piocher(j);
    @endcode
    */
    void piocher(Joueur &j);

    /**
    @brief Distribue des cartes aux joueurs.
    @param Joueur j1, j2, j3, j4
    @return none

    Example code block
    @code
    Joueur j1,j2,j3,j4;
    distribuer(j1,j2,j3,j4);
    @endcode
    */
    void distribuer(Joueur &j1,Joueur &j2,Joueur &j3,Joueur &j4);

    /**
    @brief Teste les fonctionnalités de la classe Cartes.
    @param none
    @return none

    Example code block
    @code
    Cartes carte;
    carte.TestCartes();
    @endcode
    */
    void TestCartes();
};

#endif // CARTES_H
