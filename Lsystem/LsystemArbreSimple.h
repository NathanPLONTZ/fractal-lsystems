#pragma once
#include "Lsystem.h"

/**
 * Simple binary tree L-system.
 *
 * Axiom: Y
 * Rules: Y -> X[-Y][+Y]
 *
 * Rendered by Lsystem/Test/TestLsystemArbreSimple.cpp at depth 8.
 */
class LsystemArbreSimple : public Lsystem {
    public:

    Segment curseur;
    vector<Segment> sauvegarde;
    bool gauche=true;
    double angle=M_PI/3;
    int cpt=0;

    LsystemArbreSimple(Symbole* a, int p) : Lsystem(a,p) {
    }

    void dessine(GrosseImage& im);

    /** Rotation for the pending turn: this system only tracks a left/right flag. */
    double rotation() const { return gauche ? M_PI - angle : angle; }

    /** The flag stays until the next '+' or '-', so nothing to reset. */
    void reinitialiseOrientation() {}

    void tourneAGauche() { gauche = true; }
    void tourneADroite() { gauche = false; }

    /** '[' saves the turtle state so a branch can be drawn and backed out of. */
    void empileEtat() { sauvegarde.push_back(curseur.copie()); }

    /** ']' restores the state saved by the matching '['. */
    void depileEtat() {
        curseur = sauvegarde.at(sauvegarde.size() - 1);
        sauvegarde.pop_back();
    }
};
