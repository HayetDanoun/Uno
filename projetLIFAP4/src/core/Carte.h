#ifndef CARTE_H
#define CARTE_H


enum Couleur{vert,bleu,jaune,rouge,noir}; //le noir represente les bobs ou les +4
class Carte
{
    private:
    unsigned int nombre; //Les nombres va de 1 à 9, 10 pour inversé, 11 pour bloque, 12 pour + 2, 13 pour les bobs et 14 pour les +4
    Couleur c;
    int dimx;
	int dimy;
	char car [100][100];


    public :
    /**
    @brief Constructeur par défaut : initialise le numéro de la carte à 0, et sa couleur à noir.
    @param none


    Example code block
    @code
    Carte carte;
    @endcode
    */
    Carte();
    //~Carte();
    /**
    @brief Constructeur : initialise le numéro et la couleur de la carte.
    @param nb, couleur

    Example code block
    @code
    Carte carte(3, "jaune");
    @endcode
    */
    Carte(unsigned int nb, Couleur couleur);

    /**
    @brief Constructeur : initialise le numéro et la couleur de la carte sans la modifier.
    @param Carte

    Example code block
    @code
    Carte carte;
    @endcode
    */
    Carte(const Carte &cp);

    /**
    @brief Accesseur: récupère en lecture le numéro de la carte.
    @param none
    @return entier positif

    Example code block
    @code
    Carte carte(3, "jaune");
    carte.retournerNombre();
    @endcode
    */
    unsigned int retourNombre() const;

     /**
    @brief Accesseur: récupère en lecture la couleur de la carte.
    @param none
    @return Couleur

    Example code block
    @code
    Carte carte(3, "jaune");
    carte.retournerCouleur();
    @endcode
    */
    Couleur retourCouleur() const;

     /**
    @brief Accesseur: accesseur en écriture au numéro de la carte.
    @param nb
    @return none

    Example code block
    @code
    Carte carte(3, "jaune");
    carte.modifierNombre();
    @endcode
    */
    void modifierNombre(int unsigned nb);
    /**
    @brief Accesseur: accesseur en écriture à la couleur de la carte.
    @param Couleur
    @return none

    Example code block
    @code
    Carte carte(3, "jaune");
    carte.modifierCouleur();
    @endcode
    */
    void modifierCouleur(Couleur couleur);

    /**
    @brief Echange deux cartes entre elles.
    @param Carte
    @return none

    Example code block
    @code
    Carte carte(3, "jaune");
    Carte carte1(4, "vert");
    carte.echangeCarte(carte1);
    @endcode
    */
    void echangeCarte (Carte &deuxiemeCarte);

    /**
    @brief Affiche une carte.
    @param none
    @return none

    Example code block
    @code
    Carte carte(3, "jaune");
    carte.afficherCarte();
    @endcode
    */
    void afficherCarte();

    /**
    @brief Teste les fonctionnalités de classe Carte.
    @param none
    @return none

    Example code block
    @code
    Carte carte;
    carte.TestCarte();
    @endcode
    */
    void TestCarte();

};



#endif // CARTE_H
