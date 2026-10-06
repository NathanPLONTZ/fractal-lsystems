#include "SymboleX.h"
#include "ActionsTortue.h"
#include "../LsystemArbreSimple.h"
#include "../LsystemBrindille.h"
#include "../LsystemFleche.h"
#include "../LsystemAlgue.h"
#include "../LsystemHerbe.h"
#include "../LsystemRameau.h"
#include "../LsystemSavane.h"
#include "../LsystemDragon.h"
#include "../LsystemLiane.h"
#include "../LsystemTriangle.h"

/**
 * X: move one step forward.
 *
 * X is the axiom of most of these systems, so its first occurrence carries the
 * starting heading and must not turn; avanceDepuisAxe() handles that.
 */

void SymboleX::action(GrosseImage& im, LsystemArbreSimple& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemBrindille& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemFleche& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemAlgue& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemHerbe& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemRameau& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemSavane& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemDragon& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemLiane& ls){
    avanceDepuisAxe(im, ls);
}

void SymboleX::action(GrosseImage& im, LsystemTriangle& ls){
    avanceDepuisAxe(im, ls);
}
