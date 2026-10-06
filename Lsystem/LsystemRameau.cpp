#include "LsystemRameau.h"

void LsystemRameau::dessine(GrosseImage& im){
    this->derive(im, *this);
}
