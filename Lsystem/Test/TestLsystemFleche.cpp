#include <string>
#include "../Regles/RegleY_XCoPlusYCfCoMoinsYCfXY.h"
#include "../Regles/RegleX_XX.h"
#include "../LsystemFleche.h"

using namespace std;

/**
 * Draws the Arrow L-system into Images/LsystemFleche.bmp.
 *
 * Axiom: Y
 * Rules: Y -> X[+Y][-Y]XY
 *        X -> XX
 * Depth: 7
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemFleche l(new SymboleY(), 7);
    RegleY_XCoPlusYCfCoMoinsYCfXY r1("Y_X[+Y][-Y]XY", NULL);
    RegleX_XX r2("X_XX", &r1);
    l.regles = &r2;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1000),Point(1993,1000));

    string nomFichier =  "../Images/LsystemFleche.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
