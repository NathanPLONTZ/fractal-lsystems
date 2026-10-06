#include "LsystemArbreSimple.h"

void LsystemArbreSimple::dessine(GrosseImage& im){
    this->derive(im, *this);
}
