#pragma once
#include "Regles.h"

using namespace std;

/**
 * Rewriting rule Y -> X-[[Y]+Y]+X[+XY]-Y.
 *
 * The class name spells the production: Co is '[', Cf is ']',
 * Plus is '+' and Moins is '-'.
 */
class RegleY_XMoinsCoCoYCfPlusYCfPlusXCoPlusXYCfMoinsY : public  Regles
{
public:

	RegleY_XMoinsCoCoYCfPlusYCfPlusXCoPlusXYCfMoinsY (string nom,Regles* suivant) :Regles(nom,suivant) {

	}

    bool saitResoudre(Symbole* s) {
        return s->nom == "Y";
    }

	bool resoudre1(Symbole* s, vector<Symbole*>& symboles) {
        symboles.push_back(new SymboleX());
        
        symboles.push_back(new SymboleMoins());
        symboles.push_back(new SymboleCo());
        symboles.push_back(new SymboleCo());
        symboles.push_back(new SymboleY());
        symboles.push_back(new SymboleCf());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleY());
        symboles.push_back(new SymboleCf());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleCo());
        symboles.push_back(new SymbolePlus());
        symboles.push_back(new SymboleX());
        symboles.push_back(new SymboleY());
        symboles.push_back(new SymboleCf());
        symboles.push_back(new SymboleMoins());
        symboles.push_back(new SymboleY());
        
        return true;
    }
};