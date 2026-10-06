#ifndef GROSSES_IMAGES_GGROSSEIMAGE_H_
#define GROSSES_IMAGES_GGROSSEIMAGE_H_

/**
 * Read-only interface of a large image.
 *
 * Keeping this separate lets code depend on "an image one can measure and
 * sample" without depending on the fact that it is backed by a file on disk.
 */
class GGrosseImage
{
public:

/** Image width, in pixels. */
virtual unsigned long getNombreColonnes() const = 0;

/** Image height, in pixels. */
virtual unsigned long getNombreLignes () const = 0;

/** Bytes per pixel: 1, 2, 3 or 4. */
virtual int getProfondeur () const = 0;

/**
 * Colour of pixel (i,j), as 4 bytes RGBA in hexadecimal, where i is the row
 * and j the column. Not const, because reading may move a file cursor.
 *
 * Examples: opaque red is 0xFF0000FF, opaque green 0x00FF00FF,
 * transparent blue 0x0000FF00, opaque blue 0x0000FFFF.
 */
virtual unsigned long get(const unsigned long int i, const unsigned long j) = 0;

};

#endif /* GROSSES_IMAGES_GGROSSEIMAGE_H_ */
