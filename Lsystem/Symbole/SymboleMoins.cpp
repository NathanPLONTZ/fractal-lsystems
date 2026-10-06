#include "SymboleMoins.h"
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
 * -: turn left by the system's angle on the next step.
 */

void SymboleMoins::action(GrosseImage& im, LsystemArbreSimple& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemBrindille& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemFleche& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemAlgue& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemHerbe& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemRameau& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemSavane& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemDragon& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemLiane& ls){
    ls.tourneAGauche();
}

void SymboleMoins::action(GrosseImage& im, LsystemTriangle& ls){
    ls.tourneAGauche();
}
