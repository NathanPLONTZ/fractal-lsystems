#include "SymboleY.h"
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
 * Y: move one step forward.
 *
 * Y is a plain forward step everywhere except in Triangle, where it is the
 * axiom and so skips its first turn, and in Liane, which never draws on Y.
 */

void SymboleY::action(GrosseImage& im, LsystemArbreSimple& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemBrindille& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemFleche& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemAlgue& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemHerbe& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemRameau& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemSavane& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemDragon& ls){
    avance(im, ls);
}

void SymboleY::action(GrosseImage& im, LsystemLiane& ls){
}

void SymboleY::action(GrosseImage& im, LsystemTriangle& ls){
    avanceDepuisAxe(im, ls);
}
