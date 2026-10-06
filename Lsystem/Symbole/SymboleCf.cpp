#include "SymboleCf.h"
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
 * ]: restore the turtle state saved by the matching '[', closing a branch.
 */

void SymboleCf::action(GrosseImage& im, LsystemArbreSimple& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemBrindille& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemFleche& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemAlgue& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemHerbe& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemRameau& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemSavane& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemDragon& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemLiane& ls){
    ls.depileEtat();
}

void SymboleCf::action(GrosseImage& im, LsystemTriangle& ls){
    ls.depileEtat();
}
