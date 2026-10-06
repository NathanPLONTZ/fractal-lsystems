#pragma once
#include "Lsystem.h"

/**
 * Vine L-system.
 *
 * Axiom: X
 * Rules: X -> XX[+X--X][-X++X]--X++X
 *
 * Rendered by Lsystem/Test/TestLsystemLiane.cpp at depth 5.
 *
 * Repeated turns in the same direction divide the angle instead of
 * adding up, which is what makes the branches curl.
 */
class LsystemLiane : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=2;
    double angle=M_PI/3;
    int cpt=0;

    LsystemLiane(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /**
     * Rotation for the pending turn. Unlike the other systems the accumulated
     * balance divides the angle rather than selecting one, so two '+' in a row
     * bend half as much as one.
     */
    double rotation() const {
        if (orientation < 0)      return M_PI - (angle / -orientation);
        else if (orientation > 0) return angle / orientation;
        else                      return M_PI / 2;
    }

    /** After a step the accumulated turn is spent. */
    void reinitialiseOrientation() { orientation = 0; }

    void tourneAGauche() { orientation--; }
    void tourneADroite() { orientation++; }

    /** '[' saves the turtle state so a branch can be drawn and backed out of. */
    void empileEtat() { sauvegarde.push_back(curseur.copie()); }

    /** ']' restores the state saved by the matching '['. */
    void depileEtat() {
        curseur = sauvegarde.at(sauvegarde.size() - 1);
        sauvegarde.pop_back();
    }
};
