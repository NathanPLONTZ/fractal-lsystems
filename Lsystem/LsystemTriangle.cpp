#include "LsystemTriangle.h"

void LsystemTriangle::dessine(GrosseImage& im){
    this->derive(im, *this);
}
