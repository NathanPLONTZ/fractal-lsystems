#include <string>
#include "../Regles/RegleX_XXCoMoinsXPlusXPlusXCf.h"
#include "../LsystemSavane.h"

using namespace std;

/**
 * Draws the Jungle L-system into Images/LsystemSavane.bmp.
 *
 * Axiom: X
 * Rules: X -> XX[-X+X+X]
 * Depth: 6
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemSavane l(new SymboleX(), 6);
    RegleX_XXCoMoinsXPlusXPlusXCf r1("X_XX[-X+X+X]", NULL);
    l.regles = &r1;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1000),Point(1992,1000));

    string nomFichier =  "../Images/LsystemSavane.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
