#pragma once
#include "../Point.h"
#include "../GrosseImage.h"
#include <string>
#include <iostream>
#include <sstream>

/**
 * Base of every drawable shape.
 *
 * A shape knows its colour and how to rasterise itself onto an image. Colours
 * are 4 bytes in RGBA hexadecimal, matching what GrosseImage writes to the BMP.
 */
class Forme
{
public:
	unsigned long color;

	Forme(unsigned long col) {
        color=col;
	}

	virtual void dessine (GrosseImage& im)= 0;
};
