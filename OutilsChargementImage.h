#ifndef OUTILS_CHARGEMENT_IMAGE_H_
#define OUTILS_CHARGEMENT_IMAGE_H_

#include <iostream>
#include <cstring>

using namespace std;

/**
 * Reading side of the bitmap format: locating and decoding pixels in a file
 * written by OutilsCreationImage.
 */
class OutilsChargementImage
{
public:

//-------------------------------------------------------------------------------------------

/**
 * Reads one little-endian value of type T from f.
 *
 * f must be open for reading in binary mode; T is an unsigned integer type.
 */
template <class T>
static T litLittleEndian( istream & f,  const int nombreOctets = sizeof(T))
{
T x;
f.read((char *)&x, nombreOctets);
return x;
}

//--------------------------------------------------------------------------

/**
 * Byte offset of pixel (i,j) in the file.
 *
 * BMP stores rows bottom-up, so row i of the image is row (nombreLignes-1-i)
 * of the file.
 *
 * debutPixel         : offset where the pixel array starts
 * nombreLignes       : image height, in pixels
 * largeurOctets      : width of one stored row, in bytes
 * profondeurEnOctets : bytes per pixel
 */
static unsigned long deplaceVersPixel( const int debutPixel,
					   	   	    	   const int nombreLignes,
					   	   	    	   const int largeurOctets,
					   	   	    	   const int profondeurEnOctets,
					   	   	    	   const int i, const int j)
{
return (unsigned long) ( debutPixel + (nombreLignes-1-i)*largeurOctets + j*profondeurEnOctets );
}

};

#endif /* OUTILS_CHARGEMENT_IMAGE_H_ */
