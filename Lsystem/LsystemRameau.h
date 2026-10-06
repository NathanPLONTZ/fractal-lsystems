#pragma once
#include "Lsystem.h"

/**
 * Branchlet L-system.
 *
 * Axiom: X
 * Rules: X -> XX[-X+X+X][+X-X-X]
 *
 * Rendered by Lsystem/Test/TestLsystemRameau.cpp at depth 4.
 *
 * Invented for this project rather than taken from the L-system literature,
 * and named after what it resembles. It is the shape whose fractal dimension
 * is measured; see BoxCounting.h.
 */
class LsystemRameau : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=2;
    double angle=M_PI/3;
    int cpt=0;

    LsystemRameau(Symbole* a, int p) : Lsystem(a,p) {
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
