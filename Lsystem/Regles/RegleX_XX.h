#pragma once
#include "Regles.h"

using namespace std;

/**
 * Rewriting rule X -> XX.
 *
 * The class name spells the production: Co is '[', Cf is ']',
 * Plus is '+' and Moins is '-'.
 */
class RegleX_XX : public  Regles
{
public: 
    RegleX_XX() :Regles() {

	}
	RegleX_XX(string nom,Regles* suivant) :Regles(nom,suivant) {

	}

    bool saitResoudre(Symbole* s) {
        return s->nom == "X";
    }

	bool resoudre1(Symbole* s, vector<Symbole*>& symboles) {
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleX());
        return true;
    }
};