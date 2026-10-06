#include "../GrosseImage.h"
#include "../Forme/Rectangle.h"
using namespace std;

/**
 * Sierpinski carpet.
 *
 * Each square is divided into a 3x3 grid and the construction recurses on the
 * eight tiles around the edge, leaving the centre one out. As with the
 * triangle, levels are painted over one another rather than erased.
 */

const unsigned long LARGEUR = 1000;
const unsigned long HAUTEUR = 1000;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

void sierpinskiTapis(Point pointSuperieurGauche,double cote, int depth,unsigned long color, GrosseImage& im) {

    if (depth != 0){
        Rectangle r(color,pointSuperieurGauche,Point(pointSuperieurGauche.x,pointSuperieurGauche.y+cote)
                                              ,Point(pointSuperieurGauche.x+cote,pointSuperieurGauche.y)
                                              ,Point(pointSuperieurGauche.x+cote,pointSuperieurGauche.y+cote));
        r.dessine(im);

        cote=cote/3;
        sierpinskiTapis(pointSuperieurGauche-2*cote, cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x-2*cote,pointSuperieurGauche.y+cote), cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x-2*cote,pointSuperieurGauche.y+4*cote), cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x+cote,pointSuperieurGauche.y-2*cote), cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x+4*cote,pointSuperieurGauche.y-2*cote), cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x+4*cote,pointSuperieurGauche.y+cote), cote, depth - 1, color,im);
        sierpinskiTapis(pointSuperieurGauche+4*cote, cote, depth - 1, color,im);
        sierpinskiTapis(Point(pointSuperieurGauche.x+cote,pointSuperieurGauche.y+4*cote), cote, depth - 1, color,im);
    }
}

int main()
{
string nomFichier =  "../Images/SierpinskiTapis.bmp";

GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0x00000000);

Rectangle r(0xFFFFFF00,Point(m/4,n/4),Point(m/4,3*n/4),Point(3*m/4,n/4),Point(3*m/4,3*n/4));
sierpinskiTapis(r.p1,(n/2),5+1, r.color,grosseImage);

printf("image creee\n");

return 0;
}
