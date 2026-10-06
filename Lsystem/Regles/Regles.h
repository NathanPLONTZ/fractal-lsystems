#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "../Symbole/Symbole.h"
#include "../Symbole/SymboleX.h"
#include "../Symbole/SymboleY.h"
#include "../Symbole/SymboleF.h"
#include "../Symbole/SymboleCo.h"
#include "../Symbole/SymboleCf.h"
#include "../Symbole/SymboleMoins.h"
#include "../Symbole/SymbolePlus.h"
using namespace std;

/**
 * One rewriting rule of an L-system, and a link in the chain of them.
 *
 * The rules form a chain of responsibility: resoudre() asks this rule whether
 * it knows the symbol, and hands it over to the next one if not. A symbol that
 * no rule claims is a constant and is copied through unchanged, which is how
 * '+', '-', '[' and ']' survive the rewriting.
 *
 * Subclasses are named after the production they apply, so RegleX_XX is X -> XX.
 */
class Regles {
    public:
        string nom;
        Regles *suivant;

        Regles() : suivant(NULL) {
        }

        Regles(string n,Regles* suivant){
            nom = n;
            this->suivant = suivant;
        }

        void setSuivant(Regles *s) {
            suivant = s;
        }

        Regles* getSuivant() {
            return suivant;
        }

        bool aUnsuivant() {
            return suivant != NULL;
        }

        /** True when this rule is the one that rewrites `s`. */
        virtual bool saitResoudre(Symbole* s)=0;

        /** Appends the right-hand side of the production to `symboles`. */
        virtual bool resoudre1(Symbole* s, vector<Symbole*>& symboles)=0;

        /**
         * Rewrites `s` into `symboles`, walking down the chain until a rule
         * claims it. Returns false, and copies `s` through unchanged, when none
         * does.
         */
        bool resoudre(Symbole* s, vector<Symbole*>& symboles){
            if (saitResoudre(s)){
                return resoudre1(s,symboles);
            }
            else{
                if (this->suivant != NULL)
                    return this->suivant->resoudre(s,symboles);

                else {
                    symboles.push_back(s);
                    return false;
                }
             }
        }

        void affiche() {
            cout << nom;
        }
};
