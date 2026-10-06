#include <string>
#include "../Regles/RegleX_YMoinsXMoinsY.h"
#include "../Regles/RegleY_XPlusYPlusX.h"
#include "../LsystemTriangle.h"

using namespace std;

/**
 * Draws the Triangle L-system into Images/LsystemTriangle.bmp.
 *
 * Axiom: X
 * Rules: X -> Y-X-Y
 *        Y -> X+Y+X
 * Depth: 8
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemTriangle l(new SymboleX(), 8);
    RegleX_YMoinsXMoinsY r1("X_Y-X-Y", NULL);
    RegleY_XPlusYPlusX r2("Y_X+Y+X", &r1);
    l.regles = &r2;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(1900,300),Point(1893,300));

    string nomFichier =  "../Images/LsystemTriangle.bmp";
    GrosseImage grosseImage(nomFichier, 2000, 2000, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
