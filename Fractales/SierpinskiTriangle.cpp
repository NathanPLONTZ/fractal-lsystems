#include "../GrosseImage.h"
#include "../Forme/Triangle.h"
using namespace std;

/**
 * Sierpinski triangle.
 *
 * At each level the triangle is split into four by joining the midpoints of its
 * sides, and the construction recurses on the three corner triangles, leaving
 * the central one out. Rather than erasing the middle, each level is painted
 * over the previous one in an alternating colour, which draws the holes.
 */

const unsigned long LARGEUR = 1000;
const unsigned long HAUTEUR = 1000;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

void sierpinskiTriangle(Triangle t, int depth,int c,GrosseImage& im) {

    if (depth != 0){
        t.dessine(im);

        Point milieu1 = t.p1.milieu(t.p2);
        Point milieu2 = t.p1.milieu(t.p3);
        Point milieu3 = t.p2.milieu(t.p3);
        unsigned long color = 0xFFFFFF00;
        if(c%2==1)
            color = 0x000000FF;
        c++;
        Triangle t1(color,t.p1,milieu1,milieu2);
        Triangle t2(color,milieu1,t.p2,milieu3);
        Triangle t3(color,milieu2,milieu3,t.p3);
        sierpinskiTriangle(t1, depth - 1,c,im);
        sierpinskiTriangle(t2, depth - 1,c,im);
        sierpinskiTriangle(t3, depth - 1,c,im);
    }
}

int main()
{
string nomFichier =  "../Images/SierpinskiTriangle.bmp";

GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0x00000000);
// alternating colours, so each level shows against the one below it
int c=0;
Triangle t(0x00000000,Point(m,0),Point(m,n),Point(0,n/2));
sierpinskiTriangle(t,9,c,grosseImage);

printf("image creee\n");

return 0;
}
