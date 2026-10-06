#pragma once
#include "Symbole.h"

using namespace std;

/**
 * Turn left by the system's angle.
 */
class SymboleMoins : public Symbole
{
public:
	SymboleMoins() : Symbole("-") {
    }

    void action(GrosseImage& im, LsystemArbreSimple& ls) override;
    void action(GrosseImage& im, LsystemBrindille& ls) override;
    void action(GrosseImage& im, LsystemFleche& ls) override;
    void action(GrosseImage& im, LsystemAlgue& ls) override;
    void action(GrosseImage& im, LsystemHerbe& ls) override;
    void action(GrosseImage& im, LsystemRameau& ls) override;
    void action(GrosseImage& im, LsystemSavane& ls) override;
    void action(GrosseImage& im, LsystemDragon& ls) override;
    void action(GrosseImage& im, LsystemLiane& ls) override;
    void action(GrosseImage& im, LsystemTriangle& ls) override;
};
