#pragma once
#include "Lsystem.h"

/**
 * Grass L-system.
 *
 * Axiom: Y
 * Rules: Y -> X-[[Y]+Y]+X[+XY]-Y
 *        X -> XX
 *
 * Rendered by Lsystem/Test/TestLsystemHerbe.cpp at depth 7.
 *
 * Turns accumulate here, so '[' and ']' save and restore the heading
 * along with the cursor.
 */
class LsystemHerbe : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegardeSegment;
    vector<int> sauvegardeAngle;
    int orientation=0;
    double angle=M_PI/3;
    int cpt=0;

    LsystemHerbe(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /** Rotation for the pending turn, from the accumulated left/right balance. */
    double rotation() const {
        if (orientation == -1)     return M_PI - angle;
        else if (orientation == 1) return angle;
        else                       return M_PI / 2;
    }

    /** After a step the accumulated turn is spent. */
    void reinitialiseOrientation() { orientation = 0; }

    void tourneAGauche() { orientation = orientation - 1; }
    void tourneADroite() { orientation = orientation + 1; }

    /** '[' saves the cursor and the heading it was reached with. */
    void empileEtat() {
        sauvegardeSegment.push_back(curseur.copie());
        sauvegardeAngle.push_back(orientation);
    }

    /** ']' restores both, folding the saved heading back into the current one. */
    void depileEtat() {
        curseur = sauvegardeSegment.at(sauvegardeSegment.size() - 1);
        sauvegardeSegment.pop_back();

        orientation = sauvegardeAngle.at(sauvegardeAngle.size() - 1) + orientation;
        sauvegardeAngle.pop_back();
    }
};
