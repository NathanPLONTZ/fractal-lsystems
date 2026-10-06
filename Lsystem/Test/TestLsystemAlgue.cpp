#include <string>
#include "../Regles/RegleX_XCoPlusXCfXCoMoinsXCfX.h"
#include "../LsystemAlgue.h"

using namespace std;

/**
 * Draws the Alga L-system into Images/LsystemAlgue.bmp.
 *
 * Axiom: X
 * Rules: X -> X[+X]X[-X]+X
 * Depth: 6
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemAlgue l(new SymboleX(), 6);
    RegleX_XCoPlusXCfXCoMoinsXCfX r1("X_X[+X]X[-X]+X", NULL);
    l.regles = &r1;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1000),Point(1998,1000));

    string nomFichier =  "../Images/LsystemAlgue.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
