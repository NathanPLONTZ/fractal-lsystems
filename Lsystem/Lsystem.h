#pragma once
#include "Regles/Regles.h"
#include "../Point.h"
#include "../Constantes.h"
#include "../Forme/Segment.h"
#include <vector>
#include <cstdio>

/**
 * Base of every L-system (Lindenmayer system).
 *
 * An L-system is the quadruple {V, S, w, P}: an alphabet V, a set of constants
 * S, a start axiom w and a set of rewriting rules P. What sets it apart from a
 * formal grammar is that every symbol of the word is rewritten at each step,
 * not just one of them.
 *
 * Here the word is `symboles`, the axiom is its first element, and P is the
 * chain of `Regles` reachable from `regles`. `profondeur` is how many rewriting
 * steps to apply before drawing.
 *
 * Each concrete subclass carries the turtle state (cursor, branch stack, angle)
 * and its own turning convention; the derivation and drawing loop itself is the
 * same for all of them and lives in derive() below.
 */
class Lsystem {
    public:

    Symbole& axiome;
    Regles* regles;
    vector<Symbole*> symboles;
    int profondeur;

    Lsystem(Symbole* a, int p) : axiome(*a), profondeur(p) {
        symboles.push_back(&axiome);
    }

    virtual void dessine(GrosseImage& im)=0;

    /** Prints the current word on the standard output. */
    void afficher();

    protected:

    /**
     * Rewrites the word `profondeur` times, then draws it.
     *
     * Every subclass' dessine() used to be a verbatim copy of this loop, so it
     * is written once here. It stays a template rather than a plain method
     * because applying a symbol means calling Symbole::action overloaded on the
     * concrete L-system type (the visitor pattern), which needs the static type
     * of the system; `self` carries it.
     */
    template <typename TLsystem>
    void derive(GrosseImage& im, TLsystem& self) {
        vector<Symbole*> tmp;
        while(profondeur>0){
            for(vector<Symbole*>::iterator it = symboles.begin(); it != symboles.end(); ++it){
                this->regles->resoudre(*it,tmp);
            }
            afficher();
            printf("\n");
            symboles.clear();
            symboles.swap(tmp);
            profondeur--;
        }

        afficher();
        for(vector<Symbole*>::iterator it = symboles.begin(); it != symboles.end(); ++it){
                (*it)->action(im,self);
        }
    }
};
