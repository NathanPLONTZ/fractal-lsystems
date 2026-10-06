#pragma once
#include "Lsystem.h"

/**
 * Alga L-system.
 *
 * Axiom: X
 * Rules: X -> X[+X]X[-X]+X
 *
 * Rendered by Lsystem/Test/TestLsystemAlgue.cpp at depth 6.
 */
class LsystemAlgue : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=2;
    double angle=M_PI/3;
    int cpt=0;

    LsystemAlgue(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /** Rotation for the pending turn: '-' turns left, '+' turns right, otherwise carry on. */
    double rotation() const {
        if (orientation == 0)      return M_PI - angle;
        else if (orientation == 1) return angle;
        else                       return M_PI / 2;
    }

    /** After a step the turn is spent, so the heading goes back to "straight". */
    void reinitialiseOrientation() { orientation = 2; }

    void tourneAGauche() { orientation = 0; }
    void tourneADroite() { orientation = 1; }

    /** '[' saves the turtle state so a branch can be drawn and backed out of. */
    void empileEtat() { sauvegarde.push_back(curseur.copie()); }

    /** ']' restores the state saved by the matching '['. */
    void depileEtat() {
        curseur = sauvegarde.at(sauvegarde.size() - 1);
        sauvegarde.pop_back();
    }
};
