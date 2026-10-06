#include "OutilsCreationImage.h"

/*static*/ const unsigned long OutilsCreationImage::TAILLE_HEADER = 14;
/*static*/ const unsigned long OutilsCreationImage::TAILLE_DIB = 56; // BITMAPV3INFOHEADER
/*static*/ const unsigned long OutilsCreationImage::BI_CHAMPS_BITS = 3; // BI_BITFIELDS: no compression, pixels are 32 bits

//--------------------------------------------------------------------------------------------------------

/**
 * Writes the 56-byte DIB header.
 *
 * largeurEnPixels      : image width, in pixels
 * hauteurEnPixels      : image height, in pixels
 * tailleTableauPixels  : size of the pixel array, in bytes
 * densiteHorizontale   : in pixels/m
 * densiteVerticale     : in pixels/m
 */
/*static*/ void OutilsCreationImage::creeBMPDIBHeader(iostream & f,
							 const unsigned long largeurEnPixels,
							 const unsigned long hauteurEnPixels,
							 const unsigned long tailleTableauPixels,
							 const unsigned long densiteHorizontale,
							 const unsigned long densiteVerticale)
{
ecritLittleEndian(f,TAILLE_DIB);

ecritLittleEndian(f,largeurEnPixels);

ecritLittleEndian(f,hauteurEnPixels);

const unsigned short nombrePlansCouleur = 1;
ecritLittleEndian(f,nombrePlansCouleur);

const unsigned short profondeurPixel = 32; // 32 bits per pixel
ecritLittleEndian(f,profondeurPixel);

const unsigned long methodeCompression = BI_CHAMPS_BITS; // no compression, depth is 32
ecritLittleEndian(f,methodeCompression);

ecritLittleEndian(f, tailleTableauPixels);

ecritLittleEndian(f,densiteHorizontale);
ecritLittleEndian(f,densiteVerticale);

const unsigned long vide = 0;

ecritLittleEndian(f,vide);  // number of colours in the palette
ecritLittleEndian(f,vide);  // every colour is important

//-------------- R G B A channel masks, in the order fixed by BI_BITFIELDS --------------

const int L = 4;
int m = L-1;
const unsigned long masquesRGBA[L] = { 0xFF000000,
									   0x00FF0000,
									   0x0000FF00,
									   0x000000FF};

const unsigned long * p;

int i;

for ( i = 0, p = masquesRGBA; i <= m; ++i, ++p) ecritLittleEndian(f,*p);

}
