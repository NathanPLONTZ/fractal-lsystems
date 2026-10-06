#include <fstream>
#include "../GrosseImage.h"
#include "../Constantes.h"
#include "../BoxCounting.h"
#include "../Forme/Segment.h"
using namespace std;

/**
 * Koch snowflake, and the box-counting measurement of its dimension.
 *
 * Each segment is replaced by four segments of a third of its length: the first
 * third, two sides of an equilateral bump over the middle third, and the last
 * third. Three such curves on the sides of a triangle make the snowflake.
 *
 * The construction cannot simply recurse on endpoints, because rasterising a
 * third of a segment does not give the same pixels as the matching third of the
 * whole; see Segment::segmentFloconDeKoch().
 *
 * Its dimension is known to be log(4)/log(3) ~ 1.2619, which makes it the right
 * shape to check the box-counting code against before trusting it on an
 * L-system. enregistrementData() writes the samples the R script reads back.
 */

const unsigned long LARGEUR = 3000;
const unsigned long HAUTEUR = 3000;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

void FloconDeKoch(Segment s,int depth,GrosseImage& im) {
    if(depth!=0){

        vector<Point>points=s.segmentFloconDeKoch(im);
        if(depth!=1){
            Segment::blancDeuxiemeTiers(im,points);
        }
        Point tiers= points[round(points.size()/3)];
        Point deuxTiers= points[round(2*(points.size()/3))];
        Point rotation=tiers.rotatePoint(deuxTiers,M_PI/3);

        Segment s1(0x00000000);
        vector<Point> premierTiers;
        for(unsigned long i=0;i<round(points.size()/3);i++){
                premierTiers.push_back(points[i]);
        }
        s1.setPoints(premierTiers);

        Segment s2(0x00000000);
        vector<Point> troisiemeTiers;
        for(unsigned long i=round(2*(points.size()/3));i<points.size();i++){
                troisiemeTiers.push_back(points[i]);
        }
        s2.setPoints(troisiemeTiers);

        Segment s3(0x00000000,tiers,rotation);
        Segment s4(0x00000000,rotation,deuxTiers);

        FloconDeKoch(s1,depth-1,im);
        FloconDeKoch(s2,depth-1,im);
        FloconDeKoch(s3,depth-1,im);
        FloconDeKoch(s4,depth-1,im);
    }
}

/**
 * Draws the Koch curve at a series of scales and records (log s, log N) for
 * each, which is the raw data of the dimension estimate.
 *
 * Not called by default: uncomment the call in main() to regenerate the data.
 */
void enregistrementData(){
    ofstream fichierX("../Lsystem/Test/dataXFlocon.txt");
    ofstream fichierY("../Lsystem/Test/dataYFlocon.txt");
    int tmp1 =1000;
    int tmp2 =1000;
    int longueur=20;
    int cpt=0;
    int scale=0;
    while(cpt<=4){
        tmp1=tmp1+longueur;
        tmp2=tmp2-longueur;
        string nomFichier =  "../Images/TestDimension2.bmp";
        GrosseImage grosseImage(nomFichier, 2001, 2001, 0xFFFFFF00);
        Segment s(0x00000000,Point(1000,tmp1),Point(1000,tmp2));
        FloconDeKoch(s,5,grosseImage);
        ecritEchantillon(fichierX, fichierY, scale, compteurCase(grosseImage, 0xFFFFFF00));
        longueur=longueur*2;
        if(cpt==0)
            scale++;
        scale=scale*2;
        cpt++;
    }
    fichierX.close();
    fichierY.close();
}

int main()
{
string nomFichier =  "../Images/FloconDeKoch.bmp";
GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0xFFFFFF00);
Segment s(0x00000000,Point(m/3,n),Point(m/3,0));
Segment s1(0x00000000,Point(m/3,0),Point(m,n/2));
Segment s2(0x00000000,Point(m,n/2),Point(m/3,n));

FloconDeKoch(s,7,grosseImage);
FloconDeKoch(s1,7,grosseImage);
FloconDeKoch(s2,7,grosseImage);

//enregistrementData();
printf("image creee\n");

return 0;
}
