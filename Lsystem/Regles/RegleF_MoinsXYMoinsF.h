#pragma once
#include "Regles.h"

using namespace std;

/**
 * Rewriting rule F -> -XY-F.
 *
 * The class name spells the production: Co is '[', Cf is ']',
 * Plus is '+' and Moins is '-'.
 */
class RegleF_MoinsXYMoinsF: public  Regles
{
public:

	RegleF_MoinsXYMoinsF(string nom,Regles* suivant) :Regles(nom,suivant) {

	}

    bool saitResoudre(Symbole* s) {
        return s->nom == "F";
    }

	bool resoudre1(Symbole* s, vector<Symbole*>& symboles) {
        symboles.push_back(new SymboleMoins());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleY());
        symboles.push_back(new SymboleMoins());
        symboles.push_back(new SymboleF());
        return true;
    }
};