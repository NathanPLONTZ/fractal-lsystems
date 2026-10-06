#pragma once
#include "../../GrosseImage.h"
#include <string>
#include <iostream>
using namespace std;

class LsystemArbreSimple;
class LsystemBrindille;
class LsystemFleche;
class LsystemAlgue;
class LsystemHerbe;
class LsystemRameau;
class LsystemSavane;
class LsystemDragon;
class LsystemLiane;
class LsystemTriangle;

/**
 * One symbol of an L-system word.
 *
 * A symbol is both a letter of the alphabet, used by the rewriting rules, and
 * an instruction of the turtle interpretation, used when the final word is
 * drawn. The drawing side is a visitor: action() is overloaded once per
 * concrete L-system, so each symbol can read and update that system's own
 * turtle state. Adding an L-system therefore means adding one overload here
 * and one in every symbol.
 */
class Symbole {
    public:
        string nom;

        Symbole(string n) : nom(n) {}

        virtual void action(GrosseImage& im, LsystemArbreSimple& ls)=0;
        virtual void action(GrosseImage& im, LsystemBrindille& ls)=0;
        virtual void action(GrosseImage& im, LsystemFleche& ls)=0;
        virtual void action(GrosseImage& im, LsystemAlgue& ls)=0;
        virtual void action(GrosseImage& im, LsystemHerbe& ls)=0;
        virtual void action(GrosseImage& im, LsystemRameau& ls)=0;
        virtual void action(GrosseImage& im, LsystemSavane& ls)=0;
        virtual void action(GrosseImage& im, LsystemDragon& ls)=0;
        virtual void action(GrosseImage& im, LsystemLiane& ls)=0;
        virtual void action(GrosseImage& im, LsystemTriangle& ls)=0;

        void affiche() {
            cout << nom;
        }
};
