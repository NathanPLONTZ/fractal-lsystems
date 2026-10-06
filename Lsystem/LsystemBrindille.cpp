#include "LsystemBrindille.h"

void LsystemBrindille::dessine(GrosseImage& im){
    this->derive(im, *this);
}
