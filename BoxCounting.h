#pragma once
#include <cmath>
#include <fstream>
#include <string>
#include "GrosseImage.h"

/**
 * Box-counting (Minkowski-Bouligand) support.
 *
 * The fractal dimension is estimated by covering the drawing with a grid and
 * counting how many cells it touches, then repeating at several scale factors.
 * Since every program draws at one pixel per cell, one "box" is one pixel and
 * counting boxes means counting the pixels that are not background.
 *
 * N ~ c * s^d  =>  log(N) ~ log(c) + d * log(s)
 *
 * so the slope of log(N) against log(s) estimates the dimension d.
 */

/**
 * Counts the pixels of `im` whose colour differs from `couleurFond`.
 *
 * `couleurFond` is the background the image was created with: Koch draws black
 * on white, the L-systems draw white on black, so the caller passes its own.
 */
inline int compteurCase(GrosseImage& im, unsigned long couleurFond)
{
    int cpt = 0;
    for (int i = 0; i < im.getNombreLignes(); i++) {
        for (int j = 0; j < im.getNombreColonnes(); j++) {
            if (im.get(i, j) != couleurFond) {
                cpt++;
            }
        }
    }
    return cpt;
}

/**
 * Appends one (log(s), log(N)) sample to the two data files read back by
 * Lsystem/Test/regressionLineaire.R.
 */
inline void ecritEchantillon(std::ofstream& fichierX, std::ofstream& fichierY,
                             int facteurEchelle, int nombreCases)
{
    fichierX << log(facteurEchelle) << std::endl;
    fichierY << log(nombreCases) << std::endl;
}
