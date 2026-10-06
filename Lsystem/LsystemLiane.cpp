#include "LsystemLiane.h"

void LsystemLiane::dessine(GrosseImage& im){
    this->derive(im, *this);
}
