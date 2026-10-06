#pragma once
#include "Regles.h"

using namespace std;

/**
 * Rewriting rule Y -> Y+FX+.
 *
 * The class name spells the production: Co is '[', Cf is ']',
 * Plus is '+' and Moins is '-'.
 */
class RegleY_YPlusFXPlus: public  Regles
{
public:

	RegleY_YPlusFXPlus(string nom,Regles* suivant) :Regles(nom,suivant) {

	}

    bool saitResoudre(Symbole* s) {
        return s->nom == "Y";
    }

	bool resoudre1(Symbole* s, vector<Symbole*>& symboles) {
        symboles.push_back(new SymboleY());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleF());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymbolePlus());
        return true;
    }
};