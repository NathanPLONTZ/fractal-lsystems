#include "LsystemFleche.h"

void LsystemFleche::dessine(GrosseImage& im){
    this->derive(im, *this);
}
