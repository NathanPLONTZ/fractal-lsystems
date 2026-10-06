#pragma once
#include "Lsystem.h"

/**
 * Twig L-system.
 *
 * Axiom: Y
 * Rules: Y -> X[-Y]X[-Y]+Y
 *        X -> XX
 *
 * Rendered by Lsystem/Test/TestLsystemBrindille.cpp at depth 7.
 */
class LsystemBrindille : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    int orientation=2;
    double angle=M_PI/3;
    int cpt=0;

    LsystemBrindille(Symbole* a, int p) : Lsystem(a,p) {
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
