#include "SymboleCo.h"
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
 * [: save the turtle state, opening a branch.
 */

void SymboleCo::action(GrosseImage& im, LsystemArbreSimple& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemBrindille& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemFleche& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemAlgue& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemHerbe& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemRameau& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemSavane& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemDragon& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemLiane& ls){
    ls.empileEtat();
}

void SymboleCo::action(GrosseImage& im, LsystemTriangle& ls){
    ls.empileEtat();
}
