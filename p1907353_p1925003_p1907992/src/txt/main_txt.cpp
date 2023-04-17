#include <iostream>
#include "winTxt.h"
#include "txtJeu.h"

using namespace std;

int main ( int argc, char** argv ) {
    
	/*termClear();
	Monde monde;
	txtBoucle(monde);
    termClear();
	return 0;*/
	
	//cout<<"je m'appelle main_txt"<<endl;

    /*HWND hwnd;

    hwnd = CreateWindow("MaWinClass", "Titre", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
                                                   NULL, NULL, hinstance, NULL);*/

	
	termClear();
	Jeu j;
	txtBoucle(j);
    termClear();

	return 0;
}
