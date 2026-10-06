#ifndef GROSSES_IMAGES_GROSSEIMAGE_H_
#define GROSSES_IMAGES_GROSSEIMAGE_H_

#include <fstream>
#include <string>

#include "OutilsCreationImage.h"
#include "OutilsChargementImage.h"
#include "GGrosseImage.h"

using namespace std;

/**
 * A BMP image built directly on disk, pixel by pixel.
 *
 * The image is never held in RAM: the constructor writes the headers and a
 * background-coloured pixel array to the file, and set() then overwrites
 * individual pixels in place. That is what makes images of several thousand
 * pixels a side possible without allocating them, at the cost of a seek and a
 * flush per pixel.
 *
 * Coordinates are (i,j) = (row, column), with row 0 at the top. BMP stores rows
 * bottom-up, and deplaceVers() hides that.
 *
 * Note that set() does not bounds-check: writing outside the image seeks to an
 * offset that is not the pixel asked for, and lands wherever that offset falls.
 */
class GrosseImage : public GGrosseImage
{
fstream f;
fstream fluxLecture;
unsigned long largeurOctets; // width of one stored row, in bytes

streampos debutPixels; // offset where the pixel array starts, just after the DIB header

const unsigned long nombreColonnes;
const unsigned long nombreLignes;

public:

unsigned long getNombreColonnes() const { return this->nombreColonnes; }
unsigned long getNombreLignes () const { return this->nombreLignes; }

//---------------------------------------------------------------------------------------------------------

/** Bytes per pixel. */
virtual int getProfondeur () const { return 4; }

//--------------------------------------------------------------------------------------------------------------

/**
 * Writes both headers to f and returns the offset where the pixel array
 * starts, so that the member can be initialised from it.
 */
static streampos init( fstream & f, const unsigned long  nombreColonnes,
	                                 const unsigned long  nombreLignes,
	                                 const unsigned long  densiteHorizontale = 100,
	                                 const unsigned long  densiteVerticale = 100)
{
OutilsCreationImage::creeBMPFileHeaderEtBMPDIBHeader( f, nombreColonnes, nombreLignes, densiteHorizontale, densiteVerticale);
return f.tellp();
}

//--------------------------------------------------------------------------------------------------------------

/** Fills the pixel array with couleurFondRGBAHexa, given as 4 bytes RGBA. */
static void remplitFond( fstream & f,
						 const streampos debutPixels,
						 const unsigned long  nombreColonnes,
						 const unsigned long  nombreLignes,
						 const unsigned long  couleurFondRGBAHexa);

//--------------------------------------------------------------------------------------------------------------

/**
 * Creates the BMP file and fills it with a background colour.
 *
 * nomFichierImage     : file to write, must end in .bmp
 * nombreColonnes      : image width, in pixels
 * nombreLignes        : image height, in pixels
 * couleurFondRGBAHexa : background colour, 4 bytes RGBA in hexadecimal
 * densiteHorizontale  : in pixels/m
 * densiteVerticale    : in pixels/m
 */
GrosseImage( const string & nomFichierImage,
		     const unsigned long  nombreColonnes,
		     const unsigned long  nombreLignes,
		     const unsigned long  couleurFondRGBAHexa,
		     const unsigned long  densiteHorizontale = 100, const unsigned long  densiteVerticale = 100):
		     f(nomFichierImage,ios::out|ios::binary),
		     fluxLecture(nomFichierImage,ios::in|ios::binary),
		     largeurOctets(nombreColonnes*sizeof(long)),
		     debutPixels(init( f, nombreColonnes, nombreLignes, densiteHorizontale, densiteVerticale)),
		     nombreColonnes(nombreColonnes),
		     nombreLignes(nombreLignes)

{
remplitFond(f,debutPixels, nombreColonnes, nombreLignes, couleurFondRGBAHexa);
}

//--------------------------------------------------------------------------------------------------------------

/** Byte offset of pixel (i,j) in the file. Used by get() and set(). */
streampos deplaceVers(const unsigned long int i, const unsigned long j)
{
return OutilsChargementImage:: deplaceVersPixel( this->debutPixels,
					   	   	    	   	   	   	 this->nombreLignes,
					   	   	    	   	   	   	 this->largeurOctets,
					   	   	    	   	   	   	 sizeof(long),
					   	   	    	   	   	   	 i, j);
}

//----------------------------------------------------------------------------------------

/**
 * Writes couleurRGBAHexa into pixel (i,j), overwriting whatever was there,
 * background included.
 *
 * i : row, j : column, couleurRGBAHexa : 4 bytes RGBA in hexadecimal.
 */
void set(const unsigned long int i, const unsigned long j, const unsigned long couleurRGBAHexa)
{
this->f.seekp(deplaceVers(i,j));
OutilsCreationImage::ecritLittleEndian(this->f,couleurRGBAHexa);
this->f.flush();
}

//--------------------------------------------------------------------------------------------------------------

/**
 * Reads back the colour of pixel (i,j), as 4 bytes RGBA in hexadecimal.
 *
 * This is what box counting uses to tell drawing from background.
 */
unsigned long get(const unsigned long int i, const unsigned long j)
{
this->fluxLecture.seekp(deplaceVers(i,j));
return OutilsChargementImage::litLittleEndian<unsigned long>(this->fluxLecture);
}

//--------------------------------------------------------------------------------------------------------------

~GrosseImage(){ f.close(); fluxLecture.close(); }

};

#endif /* GROSSES_IMAGES_GROSSEIMAGE_H_ */
