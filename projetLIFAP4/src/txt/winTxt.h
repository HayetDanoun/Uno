#ifndef WINTXT_H
#define WINTXT_H

//! \brief une fen�tre texte est un tableau 2D de caract�res
class WinTXT
{
private:

    int dimx;       //!< \brief largeur
    int dimy;       //!< \brief hauteur
    char* win;      //!< \brief stocke le contenu de la fen�tre dans un tableau 1D mais on y accede en 2D

public:

    /**
    @brief Constructeur : initialise les dimensions fenêtre à dx et dy.
    @param entier, entier

    Example code block
    @code
    WinTXT w(100,200);
    @endcode
    */
    WinTXT (int dx, int dy);

    /**
    @brief Déconstructeur : déallocation de la mémoire du tableau des dimensions et mise à jour des dimensions à 0.
    */
    ~WinTXT ();

    /**
    @brief Ecrit un caractere sur toute la dimension de la fenetre.
    @param caractere
    @return none

    Example code block
    @code
    WinTXT w;
    w.clear('#');
    @endcode
    */
    void clear (char c=' ');

    /**
    @brief Ecrit un caractere au point (x,y);
    @param entier, entier, caractere
    @return none

    Example code block
    @code
    WinTXT w;
    w.print(2,3,'a');
    @endcode
    */
    void print (int x, int y, char c);

    /**
    @brief Ecrit un tableau de caractere au point (x,y).
    @param entier, entier, caractere
    @return none

    Example code block
    @code
    WinTXT w;
    w.print(4,5,'bonjour');
    @endcode
    */
    void print (int x, int y, char* c);

    /**
    @brief Dessine sur la fenetre au point (x,y);
    @param entier, entier
    @return none

    Example code block
    @code
    WinTXT w;
    w.darw(0,0);
    @endcode
    */
    void draw (int x=0, int y=0);

    /**
    @brief Affiche 'appuyez sur une touche' sur la fenetre.
    @param none
    @return none

    Example code block
    @code
    WinTXT w;
    w.pause();
    @endcode
    */
    void pause();

    /**
    @brief Lis un caractere si une touche a été pressée.
    @param none
    @return caractere

    Example code block
    @code
    WinTXT w;
    w.getCh();
    @endcode
    */
    char getCh();

};

void termClear ();

#endif
