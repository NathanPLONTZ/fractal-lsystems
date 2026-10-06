#include "../GrosseImage.h"
#include "../Forme/Cercle.h"
#include "../Forme/Segment.h"
#include "../Fraction.h"

using namespace std;

/**
 * Ford circles.
 *
 * Every rational p/q has a Ford circle tangent to the same line, and two Ford
 * circles are tangent exactly when their fractions are Farey neighbours. So the
 * construction starts from two circles, inserts the one indexed by their
 * mediant (Fraction::suiteDeFarey) in the gap between them, and recurses on the
 * two new gaps. Radius and position come from Descartes' theorem, in
 * Cercle::calculRayonFord and Cercle::calculXFord.
 *
 * Each inserted circle is coloured by blending its two parents, so the nesting
 * is visible as a gradient.
 */

const unsigned long LARGEUR = 1000;
const unsigned long HAUTEUR = 1000;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

/** Channel-wise average of two RGBA colours. */
unsigned long melangerCouleurs(unsigned long couleur1, unsigned long couleur2) {
    unsigned char rouge1 = (couleur1 >> 16) & 0xFF;
    unsigned char vert1 = (couleur1 >> 8) & 0xFF;
    unsigned char bleu1 = couleur1 & 0xFF;

    unsigned char rouge2 = (couleur2 >> 16) & 0xFF;
    unsigned char vert2 = (couleur2 >> 8) & 0xFF;
    unsigned char bleu2 = couleur2 & 0xFF;

    unsigned char rougeMelange = (rouge1 + rouge2) / 2;
    unsigned char vertMelange = (vert1 + vert2) / 2;
    unsigned char bleuMelange = (bleu1 + bleu2) / 2;

    unsigned long couleurMelangee = (rougeMelange << 16) | (vertMelange << 8) | bleuMelange;

    return couleurMelangee;
}

/**
 * Inserts the Ford circle between c1 and c2, then recurses into the two gaps it
 * leaves. f0 and f1 are the fractions indexing c1 and c2; s is the line the
 * centres are placed along.
 */
void CercleDeFord(Cercle c1,Cercle c2,Fraction f0,Fraction f1,Segment s,int depth, GrosseImage& im) {
    if(depth != 0){
        double r = Cercle::calculRayonFord(c1,c2);
        double x = Cercle::calculXFord(c1,r);
        Fraction farey=Fraction::suiteDeFarey(f0,f1);
        double y = s.p1.y+(s.p2.y-s.p1.y)*(farey.numerateur/static_cast<double>(farey.denominateur));
        Cercle c3(melangerCouleurs(c1.color,c2.color),Point(x,y),r);
        c3.dessine(im);

        CercleDeFord(c1,c3,f0,farey,s,depth-1,im);
        CercleDeFord(c3,c2,farey,f1,s,depth-1,im);
    }
}

int main()
{
    string nomFichier =  "../Images/CercleDeFord.bmp";

    double x0=m/2;
    double y0=n/4;
    double y1=3*n/4;
    double rayon=250;
    unsigned long c1=0xFFFFFF00;
    unsigned long c2=0x0000FF00;
    Cercle A(c1,Point(x0,y0),rayon);
    Cercle B(c2,Point(x0,y1),rayon);
    GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0x00000000);
    A.dessine(grosseImage);
    B.dessine(grosseImage);
    CercleDeFord(A,B,Fraction(0,1),Fraction(1,1),Segment(0x00000000,Point(A.centre.x,A.centre.y),Point(B.centre.x,B.centre.y)),7,grosseImage);

    printf("image creee\n");
    return 0;
}
