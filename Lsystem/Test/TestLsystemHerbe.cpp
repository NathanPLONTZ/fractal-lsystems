#include <string>
#include "../Regles/RegleY_XMoinsCoCoYCfPlusYCfPlusXCoPlusXYCfMoinsY.h"
#include "../Regles/RegleX_XX.h"
#include "../LsystemHerbe.h"

using namespace std;

/**
 * Draws the Grass L-system into Images/LsystemHerbe.bmp.
 *
 * Axiom: Y
 * Rules: Y -> X-[[Y]+Y]+X[+XY]-Y
 *        X -> XX
 * Depth: 7
 *
 * The rules are chained in reverse: the last one built is the head of the
 * chain, and each rule holds the next (see Regles).
 */
int main () {
    LsystemHerbe l(new SymboleY(), 7);
    RegleY_XMoinsCoCoYCfPlusYCfPlusXCoPlusXYCfMoinsY r1("Y_X-[[Y]+Y]+X[+XY]-Y", NULL);
    RegleX_XX r2("X_XX", &r1);
    l.regles = &r2;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1000),Point(1995,1000));

    string nomFichier =  "../Images/LsystemHerbe.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);
    return 0;
}
