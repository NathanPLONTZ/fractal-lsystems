#include <iostream>
#include <string>
#include "../GrosseImage.h"
#include "../Forme/Cercle.h"
using namespace std;

/**
 * Smoke test: draws a single filled circle on a 50x50 image.
 *
 * Small and fast, so it is the quickest way to check that the toolchain builds
 * and that the BMP writer produces a readable file.
 */
int main()
{
    string nomFichierImage  = "../Images/test.bmp";

    const unsigned long LARGEUR = 50;
    const unsigned long HAUTEUR = 50;

    unsigned long couleurFondRGBAHexa = 0x00000000;

    GrosseImage grosseImage( nomFichierImage, LARGEUR, HAUTEUR, couleurFondRGBAHexa);
    Point p1(25,25);

    Cercle cercle(0x00FF0000, p1, 10);
    cercle.dessine(grosseImage);
    cout <<"image creee" << endl;

    return 0;
}
