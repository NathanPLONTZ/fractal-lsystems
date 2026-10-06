#include "SymboleF.h"
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
 * F: move one step forward.
 *
 * Only the dragon curve draws on F; the other systems use it as a pure
 * rewriting symbol with no turtle meaning.
 */

void SymboleF::action(GrosseImage& im, LsystemArbreSimple& ls){
}

void SymboleF::action(GrosseImage& im, LsystemBrindille& ls){
}

void SymboleF::action(GrosseImage& im, LsystemFleche& ls){
}

void SymboleF::action(GrosseImage& im, LsystemAlgue& ls){
}

void SymboleF::action(GrosseImage& im, LsystemHerbe& ls){
}

void SymboleF::action(GrosseImage& im, LsystemRameau& ls){
}

void SymboleF::action(GrosseImage& im, LsystemSavane& ls){
}

void SymboleF::action(GrosseImage& im, LsystemDragon& ls){
    avance(im, ls);
}

void SymboleF::action(GrosseImage& im, LsystemLiane& ls){
}

void SymboleF::action(GrosseImage& im, LsystemTriangle& ls){
}
