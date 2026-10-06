#ifndef OUTILSCREATIONIMAGE_H_
#define OUTILSCREATIONIMAGE_H_

#include <iostream>
#include <fstream>

using namespace std;

/**
 * Writes BMP images where every pixel is 4 bytes RGBA.
 *
 * All integers are unsigned and written little-endian, as the BMP format
 * requires. The DIB header used is BITMAPV3INFOHEADER, the first one to carry
 * an alpha channel; the compression field says BI_BITFIELDS, which means no
 * compression, since 32-bit pixels are stored as they are.
 */
class OutilsCreationImage
{
public:
static const unsigned long TAILLE_HEADER ; // bytes = 14
static const unsigned long TAILLE_DIB;     // bytes = 56, for BITMAPV3INFOHEADER
static const unsigned long BI_CHAMPS_BITS; // = 3, BI_BITFIELDS: no compression

//-------------------------------------------------------------------------------------------

/**
 * Writes x to f in little-endian order.
 *
 * f must be open for writing in binary mode; T is an unsigned integer type.
 */
template <class T>
static void ecritLittleEndian( iostream & f, const T & x, const int nombreOctets = sizeof(T))
{
const char * s = (const char *)&x;
f.write(s, nombreOctets);
}

//-------------------------------------------------------------------------------------------

/**
 * Writes the 14-byte BMP file header.
 *
 * tailleFichierCompletNombreOctets is the size of the whole file, in bytes.
 */
static void creeBMPFileHeader(iostream & f, const unsigned long tailleFichierCompletNombreOctets)
{
const char * nom = "BM";
f.write(nom,2);

ecritLittleEndian(f,tailleFichierCompletNombreOctets);

const unsigned long vide = 0;
ecritLittleEndian(f,vide);

// where the pixel array starts, counted from the beginning of the file
unsigned long offsetTableauPixel = TAILLE_HEADER + TAILLE_DIB;

ecritLittleEndian(f,offsetTableauPixel);
}

//-------------------------------------------------------------------------------------------

/**
 * Writes the 56-byte DIB header.
 *
 * largeurEnPixels      : image width, in pixels
 * hauteurEnPixels      : image height, in pixels
 * tailleTableauPixels  : size of the pixel array, in bytes
 * densiteHorizontale   : in pixels/m
 * densiteVerticale     : in pixels/m
 */
static void creeBMPDIBHeader(iostream & f,
							 const unsigned long largeurEnPixels,
							 const unsigned long hauteurEnPixels,
							 const unsigned long tailleTableauPixels,
							 const unsigned long densiteHorizontale = 100,
							 const unsigned long densiteVerticale = 100);

//-------------------------------------------------------------------------------------------

/**
 * Writes both headers, leaving the cursor of f ready for the pixel array.
 *
 * nombreColonnes : image width, in pixels
 * nombreLignes   : image height, in pixels
 *
 * A density of 100 pixels/m on both axes makes a pixel one centimetre square.
 */
inline static void creeBMPFileHeaderEtBMPDIBHeader( iostream & f,
		               const unsigned long nombreColonnes, const unsigned long nombreLignes,
		               const unsigned long densiteHorizontale = 100, const unsigned long densiteVerticale = 100)
{
unsigned long tailleTableauOctets = nombreLignes*nombreColonnes*sizeof(long);
unsigned long tailleTotaleFichierOctets = TAILLE_HEADER + TAILLE_DIB + tailleTableauOctets;

creeBMPFileHeader( f, tailleTotaleFichierOctets);

creeBMPDIBHeader( f, nombreColonnes, nombreLignes, tailleTableauOctets, densiteHorizontale, densiteVerticale);
}

};

#endif /* OUTILSCREATIONIMAGE_H_ */
