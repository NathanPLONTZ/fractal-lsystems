#include "GrosseImage.h"

/**
 * Fills the pixel array with couleurFondRGBAHexa, given as 4 bytes RGBA.
 *
 * f            : the image file being built
 * debutPixels  : offset where the pixel array starts
 * nombreColonnes, nombreLignes : image size, in pixels
 */
/*static*/ void GrosseImage::remplitFond( fstream & f,
						 const streampos debutPixels,
						 const unsigned long  nombreColonnes,
						 const unsigned long  nombreLignes,
						 const unsigned long  couleurFondRGBAHexa)
{
f.seekp(debutPixels);

unsigned long i, j;

for ( i = 0 ; i < nombreLignes ; ++i)
for ( j = 0 ; j < nombreColonnes ; ++j)
	OutilsCreationImage::ecritLittleEndian(f, couleurFondRGBAHexa);

}
