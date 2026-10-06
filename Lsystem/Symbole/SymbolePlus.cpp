#include "SymbolePlus.h"
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
 * +: turn right by the system's angle on the next step.
 */

void SymbolePlus::action(GrosseImage& im, LsystemArbreSimple& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemBrindille& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemFleche& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemAlgue& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemHerbe& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemRameau& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemSavane& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemDragon& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemLiane& ls){
    ls.tourneADroite();
}

void SymbolePlus::action(GrosseImage& im, LsystemTriangle& ls){
    ls.tourneADroite();
}
