#ifndef MONDE_H
#define MONDE_H

#include "Carte.h"
#include "Cartes.h"
#include "Joueur.h"

class Monde
{
    public:
    Cartes milieu; //la carte du milieu
    Cartes p; //pioche
    Joueur *j;
    unsigned int nbDeJoueur;
    bool sensDuJeuChanger;

    /**
    @brief Constructeur par défaut : initialise le nombre de joueurs à 3 : un joueur et deux ordinateurs.
    @param none

    Example code block
    @code
    Monde m;
    @endcode
    */
    Monde();

    /**
    @brief Constructeur : initialise le nombre de joueurs total et le nombre d'ordinateurs.
    @param entier, entier

    Example code block
    @code
    Monde m(1,2);
    @endcode
    */
    Monde(unsigned int nbJoueur,unsigned int nbOrdi);


    unsigned int PoserMeilleurIndiceOrdi(const unsigned int *tab,unsigned int k, unsigned int compt);

    //~Monde();
    /**
    @brief Distribue les cartes à chaque joueur.
    @param none
    @return none

    Example code block
    @code
    Monde m;
    m.distribuer();
    @endcode
    */
    void distribuer();

    /**
    @brief Initialise la partie avec la pioche, la carte au milieu et les cartes des joueurs.
    @param none
    @return none

    Example code block
    @code
    Monde m;
    m.commencerLaPartie();
    @endcode
    */
    void commercerLaPartie();

    /**
    @brief Vérifie quelles cartes le joueur peut poser.
    @param Joueur, entier, caractere (initial d'un couleur)
    @return bool

    Example code block
    @code
    Monde m;
    Joueur j;
    m.peutPoser(j,1,'v');
    @endcode
    */
    bool peutPoser(const Joueur &j,unsigned int indice,char &c);

    /**
    @brief Permet à un joueur k de choisir la carte qu'il veut poser.
    @param entier, caractere (initial d'une couleur)
    @return entier

    Example code block
    @code
    Monde m;
    m.choisiCarteJoueur(2,'c');
    @endcode
    */
    int choisiCarteJoueur(int k,char &c);

    /**
    @brief Permet à un ordinateur de choisir la carte qu'il veut poser.
    @param entier, caractere (initial d'une couleur)
    @return entier

    Example code block
    @code
    Monde m;
    m.choisiCarteOrdinateur(1,'j');
    @endcode
    */
    int choisiCarteOrdinateur(int k,char &c);

    //10 pour inversé, 13 pour les bobs et 14 pou
    /**
    @brief inverse le sens du jeu.
    @param entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserChangerSens(2);
    @endcode
    */
    void poserChangerSens(int &k);

    //11 pour bloque
    /**
    @brief Saute le tour d'un joueur.
    @param entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPasseTour(1);
    @endcode
    */
    void poserPasseTour(int &k);

    /**
    @brief Pose les cartes + pour l'ordinateur.
    @param entier, entier, entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusOrdi(1,2,3);
    @endcode
    */
    //12 pour + 2
    void poserPlusDeuxOrdi(int &k,unsigned int nbDeCarteAPiocher);

    /**
    @brief Pose les cartes + pour le joueur.
    @param entier, entier, entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusJoueur(1,2,2);
    @endcode
    */
    void poserPlusDeuxJoueur(int &k,unsigned int nbDeCarteAPiocher);

    /**
    @brief Pose une carte +2.
    @param entier, entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusDeux(1,2);
    @endcode
    */
    void poserPlusDeux(int &k,unsigned int nbDeCarteAPiocher);
    //13 pour Bob

    /**
    @brief Retourne la couleur que le joueur choisit.
    @param none
    @return caractere

    Example code block
    @code
    Monde m;
    m.demanderCouleurJoueur();
    @endcode
    */
    char demanderCouleurJoueur();

    /**
    @brief Retourne la couleur que l'ordinateur choisit
    @param entier
    @return caractere

    Example code block
    @code
    Monde m;
    m.demanderCouleurOrdi(2);
    @endcode
    */
    char demanderCouleurOrdi(int k);

    /**
    @brief Pose une carte bob.
    @param entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserBob(3);
    @endcode
    */
    void poserBob(int &k, char &couleur);

    /**
    @brief Pose une carte +4.
    @param entier, entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusQuatre(2,4);
    @endcode
    */
    //14 pour +4
    void poserPlusQuatreOrdi(int &k,unsigned int nbDeCarteAPiocher, char c);

    /**
    @brief Pose une carte.
    @param entier, caractere (initial d'une couleur)
    @return none

    Example code block
    @code
    Monde m;
    m.poserCarte(1,'v');
    @endcode
    */
    void poserCarte(int &k,char &c);

    /**
    @brief Le joueur pose un +4.
    @param entier, entier, caractere (initial d'une couleur)
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusQuatreJoueur(1,2,'v');
    @endcode
    */
    void poserPlusQuatreJoueur(int &k,unsigned int &nbDeCarteAPiocher, char couleur);

    /**
    @brief Le joueur pose un +4.
    @param entier, entier
    @return none

    Example code block
    @code
    Monde m;
    m.poserPlusQuatreJoueur(1,2);
    @endcode
    */
    void poserPlusQuatre(int &k, unsigned int nbDeCarteAPiocher, char &couleur);

    /**
    @brief Joue une partie.
    @param none
    @return none

    Example code block
    @code
    Monde m;
    m.jouer();
    @endcode
    */
    void jouer();

    /**
    @brief Passe le tour au joueur suivant.
    @param entier
    @return none

    Example code block
    @code
    Monde m;
    m.passerAuJoueurSuivant(2);
    @endcode
    */
    void passerAuJoueurSuivant(int &k);

    /**
    @brief Affiche la carte du milieu et le joueur qui joue.
    @param entier
    @return none

    Example code block
    @code
    Monde m;
    m.afficher(2);
    @endcode
    */
    const void afficher(unsigned int k);

    /**
    @brief Détermine le gagnant d'une partie.
    @param booléen
    @return booléen

    Example code block
    @code
    Monde m;
    bool q;
    m.gagner(q);
    @endcode
    */
    bool gagner(bool &quitter);

    /**
    @brief Vérifie qu'un joueur ne possède qu'une carte.
    @param none
    @return bool

    Example code block
    @code
    Monde m;
    m.uno();
    @endcode
    */
    bool uno();

    /**
    @brief Vérifie qu'un joueur puisse dire 'contre uno !'.
    @param entier
    @return bool

    Example code block
    @code
    Monde m;
    m.contreUno(2);
    @endcode
    */
    bool contreUno(int& jc);

    /**
    @brief Teste les fonctionnalités du Monde.
    @param none
    @return none

    Example code block
    @code
    Monde m;
    m.TestMonde();
    @endcode
    */
    void TestMonde();
};

#endif // MONDE_H
