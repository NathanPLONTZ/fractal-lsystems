#include <cstdlib>
#include <ctime>

#include "../GrosseImage.h"
#include "../Forme/Cercle.h"

using namespace std;

/**
 * Apollonian gasket.
 *
 * Three mutually tangent circles admit exactly two further circles tangent to
 * all three, given by Descartes' circle theorem; taking each new circle with
 * two of its parents gives three new triples, and the construction repeats.
 * The geometry lives in Cercle::apolloniusNouveauxCercles, which returns all
 * four candidate solutions, and Cercle::valideCercleApollonius, which keeps the
 * ones that are genuinely tangent, large enough to draw, and not duplicates.
 *
 * The outer circle is given a negative curvature, which is how Descartes'
 * theorem expresses a circle that contains the others rather than touching them
 * from outside.
 *
 * The two inner circles are sized at random, so each run gives a different
 * gasket; the image is written as CercleApolloniusAleatoire.bmp. Fixing rA
 * below makes the output reproducible.
 */

const unsigned long LARGEUR = 2001;
const unsigned long HAUTEUR = 2001;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

/**
 * Grows the gasket breadth-first: `queue` holds the triples still to be filled,
 * and each accepted circle spawns three new triples for the next level.
 */
void CercleApollonius(GrosseImage& im,Cercle c1,Cercle c2,Cercle c3,int profondeur){
    vector<Cercle> tousCercles;
    tousCercles.push_back(c1);
    tousCercles.push_back(c2);
    tousCercles.push_back(c3);
    vector<vector<Cercle>> queue;
    vector<Cercle> initTriplet;
    initTriplet.push_back(c1);
    initTriplet.push_back(c2);
    initTriplet.push_back(c3);
    queue.push_back(initTriplet);
    for(int i=0; i<profondeur;i++){
        vector<vector<Cercle>> nextQueue;

        for(vector<Cercle> triplet : queue){
            Cercle t1 = triplet[0];
            Cercle t2 = triplet[1];
            Cercle t3 = triplet[2];
            vector<Cercle> nouveauxCercles = Cercle::apolloniusNouveauxCercles(t1,t2,t3);

            for(Cercle c : nouveauxCercles){
                if(c.valideCercleApollonius(tousCercles,t1,t2,t3)){
                    tousCercles.push_back(c);
                    vector<Cercle> nouveauTriplet1;
                    nouveauTriplet1.push_back(t1);
                    nouveauTriplet1.push_back(t2);
                    nouveauTriplet1.push_back(c);

                    vector<Cercle> nouveauTriplet2;
                    nouveauTriplet2.push_back(t1);
                    nouveauTriplet2.push_back(t3);
                    nouveauTriplet2.push_back(c);

                    vector<Cercle> nouveauTriplet3;
                    nouveauTriplet3.push_back(t2);
                    nouveauTriplet3.push_back(t3);
                    nouveauTriplet3.push_back(c);

                    nextQueue.push_back(nouveauTriplet1);
                    nextQueue.push_back(nouveauTriplet2);
                    nextQueue.push_back(nouveauTriplet3);
                }
            }
        }
        queue=nextQueue;
    }

    for(Cercle c : tousCercles){
        c.dessine(im);
    }
}

int main()
{
    string nomFichier =  "../Images/CercleApolloniusAleatoire.bmp";
    GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0xFFFFFF00);
    srand(time(nullptr));

    unsigned long c1=0x00000000;

    // the enclosing circle: negative curvature, since it contains the others
    Cercle o(c1,Point(m/2,n/2),n/2,false);
    o.courbure=-o.courbure;

    // two circles tangent to each other and to o, splitting its diameter
    int rA= rand() % ((int)o.rayon/2 - 100 + 1) + 100;
    int rB=abs(o.rayon-rA);
    Point centreA = Point((m/2),rA);
    Point centreB = Point((m/2),2*rA+rB);
    Cercle A(c1,centreA,rA,false);
    Cercle B(c1,centreB,rB,false);

    CercleApollonius(grosseImage,o,A,B,14);
    printf("image creee\n");
    return 0;
}
