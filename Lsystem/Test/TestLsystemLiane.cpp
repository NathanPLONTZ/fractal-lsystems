#include <string>
#include "../Regles/RegleX_XXCoPlusXMoinsMoinsXCfCoMoinsXPlusPlusXCfMoinsMoinsXPlusPlusX.h"
#include "../LsystemLiane.h"

using namespace std;

/**
 * Draws the Vine L-system into Images/LsystemLiane.bmp.
 *
 * Axiom: X
 * Rules: X -> XX[+X--X][-X++X]--X++X
 * Depth: 5
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemLiane l(new SymboleX(), 5);
    RegleX_XXCoPlusXMoinsMoinsXCfCoMoinsXPlusPlusXCfMoinsMoinsXPlusPlusX r1("X_XX[+X--X][-X++X]--X++X", NULL);
    l.regles = &r1;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1800),Point(1997,1800));

    string nomFichier =  "../Images/LsystemLiane.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
