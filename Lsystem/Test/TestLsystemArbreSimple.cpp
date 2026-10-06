#include <string>
#include "../Regles/RegleY_XCoMoinsYCfCoPlusYCf.h"
#include "../LsystemArbreSimple.h"

using namespace std;

/**
 * Draws the Simple binary tree L-system into Images/LsystemArbreSimple.bmp.
 *
 * Axiom: Y
 * Rules: Y -> X[-Y][+Y]
 * Depth: 8
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemArbreSimple l(new SymboleY(), 8);
    RegleY_XCoMoinsYCfCoPlusYCf r1("Y_X[-Y][+Y]", NULL);
    l.regles = &r1;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(1500,1000),Point(1400,1000));

    string nomFichier =  "../Images/LsystemArbreSimple.bmp";
    GrosseImage grosseImage(nomFichier, 2000, 2000, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
