#pragma once
#include "Regles.h"

using namespace std;

/**
 * Rewriting rule X -> XX[-X+X+X].
 *
 * The class name spells the production: Co is '[', Cf is ']',
 * Plus is '+' and Moins is '-'.
 */
class RegleX_XXCoMoinsXPlusXPlusXCf : public  Regles
{
public:

	RegleX_XXCoMoinsXPlusXPlusXCf(string nom,Regles* suivant) :Regles(nom,suivant) {

	}

    bool saitResoudre(Symbole* s) {
        return s->nom == "X";
    }

	bool resoudre1(Symbole* s, vector<Symbole*>& symboles) {
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleX());

        symboles.push_back(new SymboleCo());
        symboles.push_back(new SymboleMoins());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleCf());

        return true;
    }
};