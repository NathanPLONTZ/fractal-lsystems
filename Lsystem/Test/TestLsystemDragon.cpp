#include <string>
#include "../Regles/RegleF_MoinsXYMoinsF.h"
#include "../Regles/RegleY_YPlusFXPlus.h"
#include "../LsystemDragon.h"

using namespace std;

/**
 * Draws the Dragon curve L-system into Images/LsystemDragon.bmp.
 *
 * Axiom: XY
 * Rules: F -> -XY-F
 *        Y -> Y+FX+
 * Depth: 14
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemDragon l(new SymboleX(), 14);
    l.symboles.push_back(new SymboleY());
    RegleF_MoinsXYMoinsF r1("F_-XY-F", NULL);
    RegleY_YPlusFXPlus r2("Y_Y+FX+", &r1);
    l.regles = &r2;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(1200,650),Point(1204,650));

    string nomFichier =  "../Images/LsystemDragon.bmp";
    GrosseImage grosseImage(nomFichier, 2000, 2000, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
