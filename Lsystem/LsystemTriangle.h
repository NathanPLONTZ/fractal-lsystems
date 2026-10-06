#pragma once
#include "Lsystem.h"

/**
 * Triangle L-system.
 *
 * Axiom: X
 * Rules: X -> Y-X-Y
 *        Y -> X+Y+X
 *
 * Rendered by Lsystem/Test/TestLsystemTriangle.cpp at depth 8.
 */
class LsystemTriangle : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=2;
    double angle=M_PI/6;
    int cpt=0;

    LsystemTriangle(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /** Rotation for the pending turn: '-' turns left, '+' turns right, otherwise carry on. */
    double rotation() const {
        if (orientation == 0)      return M_PI - angle;
        else if (orientation == 1) return angle;
        else                       return M_PI / 2;
    }

    /** The turn stays set until the next '+' or '-', so nothing to reset. */
    void reinitialiseOrientation() {}

    void tourneAGauche() { orientation = 0; }
    void tourneADroite() { orientation = 1; }

    /** This system draws a single unbranched path, so '[' and ']' do nothing. */
    void empileEtat() {}
    void depileEtat() {}
};
