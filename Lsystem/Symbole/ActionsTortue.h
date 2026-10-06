#pragma once
#include "../../Forme/Segment.h"
#include "../../Constantes.h"

/**
 * Turtle primitives shared by every symbol.
 *
 * The drawing model is the classic turtle interpretation: the L-system keeps a
 * `curseur` segment that is both the turtle's position (its tip p2) and its
 * heading (p1 -> p2). Moving forward means pivoting that segment around its own
 * tip by some angle and drawing the result.
 *
 * Only two things vary from one L-system to the next:
 *   - how its `orientation` state maps to a rotation angle, which each system
 *     answers through rotation();
 *   - what that state becomes once a step has been drawn, which each system
 *     answers through reinitialiseOrientation().
 *
 * Everything else is identical, which is why it lives here instead of being
 * repeated once per (symbol, L-system) pair.
 */

/**
 * Pivots the cursor around its tip by `rotation` and makes the result the new
 * cursor. The pivot goes through the point at a right angle to the current
 * heading, so a rotation of M_PI/2 carries straight on.
 */
template <typename TLsystem>
inline void pivoteCurseur(TLsystem& ls, double rotation)
{
    Segment tmp = ls.curseur;
    Point c = tmp.p1.pointAngleDroit(tmp.p2);
    ls.curseur = Segment(0xFFFFFF00, tmp.p2, c.rotatePoint(tmp.p2, rotation));
}

/**
 * Turns, then draws one step.
 */
template <typename TLsystem>
inline void avance(GrosseImage& im, TLsystem& ls)
{
    pivoteCurseur(ls, ls.rotation());
    ls.curseur.dessine(im);
    ls.reinitialiseOrientation();
}

/**
 * Same as avance(), but leaves the very first step unturned: the initial cursor
 * set by the caller already carries the starting heading, so turning on step 0
 * would throw it away. `cpt` counts the steps drawn so far.
 */
template <typename TLsystem>
inline void avanceDepuisAxe(GrosseImage& im, TLsystem& ls)
{
    if (ls.cpt != 0) {
        pivoteCurseur(ls, ls.rotation());
    }
    ls.cpt = ls.cpt + 1;
    ls.curseur.dessine(im);
    ls.reinitialiseOrientation();
}
