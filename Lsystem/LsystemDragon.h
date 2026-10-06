#pragma once
#include "Lsystem.h"

/**
 * Dragon curve L-system.
 *
 * Axiom: XY
 * Rules: F -> -XY-F
 *        Y -> Y+FX+
 *
 * Rendered by Lsystem/Test/TestLsystemDragon.cpp at depth 14.
 *
 * angle is 0 here, so a turn is a straight reversal and the quarter
 * turn comes from the "carry on" branch of rotation().
 */
class LsystemDragon : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=0;
    double angle=0;
    int cpt=0;

    LsystemDragon(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /** Rotation for the pending turn, from the accumulated left/right balance. */
    double rotation() const {
        if (orientation < 0)      return M_PI - angle;
        else if (orientation > 0) return angle;
        else                      return M_PI / 2;
    }

    /** After a step the accumulated turn is spent. */
    void reinitialiseOrientation() { orientation = 0; }

    void tourneAGauche() { orientation--; }
    void tourneADroite() { orientation++; }

    /** This system draws a single unbranched path, so '[' and ']' do nothing. */
    void empileEtat() {}
    void depileEtat() {}
};
