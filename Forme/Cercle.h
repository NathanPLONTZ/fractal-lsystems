#pragma once
#include "Forme.h"
#include "../Complexe.h"
#include <vector>
using namespace std;

/**
 * Circle, rasterised with the midpoint (Bresenham) circle algorithm.
 *
 * Besides drawing, this class carries the geometry of the two circle fractals:
 * Ford circles (calculRayonFord / calculXFord) and the Apollonian gasket
 * (apolloniusRayon / apolloniusNouveauxCercles), both of which are stated more
 * naturally in terms of curvature k = 1/r than of radius, which is why
 * `courbure` is kept alongside `rayon`.
 */
class Cercle : public Forme
{
public:
	Point centre;
    double rayon;
    bool plein;
    double courbure;
public:

    Cercle(unsigned long color,Point centre, double rayon) : Forme(color) {
		this->centre=centre;
        this->rayon=rayon;
        this->courbure=1/rayon;
        this->plein=true;
	}

	Cercle(unsigned long color,Point centre, double rayon,bool plein) : Forme(color) {
		this->centre=centre;
        this->rayon=rayon;
        this->courbure=1/rayon;
        this->plein=plein;
	}

    double distance(Cercle c){
        return this->centre.distance(c.centre);
    }

    /**
     * True when the two circles touch, externally (distance == r1 + r2) or
     * internally (distance == |r1 - r2|), within `epsilon` pixels.
     */
    bool estTangente(Cercle c,double epsilon=0.1){
        bool a = abs(this->distance(c)-(this->rayon+c.rayon))<epsilon;
        bool b = abs(this->distance(c)-abs(c.rayon-this->rayon))<epsilon;
        return a || b;
    }

    /**
     * Accepts a candidate of the Apollonian gasket: it must be big enough to be
     * worth drawing, must not duplicate a circle already placed, and must be
     * tangent to all three parents.
     */
    bool valideCercleApollonius(vector<Cercle> tousCercles,Cercle c1,Cercle c2,Cercle c3,double epsilon=0.1){
        if(this->rayon<2)
            return false;

        for(Cercle c : tousCercles){
            double d = this->distance(c);
            double diffRayon = abs(this->rayon-c.rayon);
            if(d<epsilon && diffRayon<epsilon)
                return false;
        }

        if(!this->estTangente(c1,epsilon) || !this->estTangente(c2,epsilon) || !this->estTangente(c3,epsilon))
            return false;

        return true;
    }

    void dessine(GrosseImage& im){
        if(this->plein){
            for(int i=0; i<=im.getNombreLignes()-1;i++)
                for(int j=0; j<=im.getNombreColonnes()-1;j++)
                    if(Point(i,j).pointDansCercle(*this))
                        im.set(i,j,this->color);
        }
        int x=0;
        int y=rayon;
        int e=5-4*rayon;

        while(y>=x){
            im.set(centre.x+x,centre.y+y,this->color);
            im.set(centre.x-x,centre.y+y,this->color);
            im.set(centre.x-x,centre.y-y,this->color);
            im.set(centre.x+x,centre.y-y,this->color);

            im.set(centre.x-y,centre.y+x,this->color);
            im.set(centre.x-y,centre.y-x,this->color);
            im.set(centre.x+y,centre.y+x,this->color);
            im.set(centre.x+y,centre.y-x,this->color);
            e=e+8*x+4;
            x++;
            if (e>0){
                y--;
                e=e-8*y;
            }
        }
    }

    /**
     * Radius of the Ford circle tangent to both c1 and c2 and to the same line.
     * Descartes' theorem for two circles and a line (curvature 0) reduces to
     * k3 = k1 + k2 + 2*sqrt(k1*k2).
     */
    static double calculRayonFord(Cercle c1,Cercle c2){
        double courbure = 1/c1.rayon+1/c2.rayon+2*sqrt((1/c1.rayon)*(1/c2.rayon));
        return 1/courbure;
    }

    /** Abscissa of that Ford circle, given either parent and the radius above. */
    static double calculXFord(Cercle c,double rayonDeFord){
        return c.centre.x+c.rayon-rayonDeFord;
    }

    private :

    /**
     * The two curvatures solving Descartes' circle theorem for three mutually
     * tangent circles: k4 = k1 + k2 + k3 +/- 2*sqrt(k1*k2 + k2*k3 + k1*k3).
     * The caller owns the returned array.
     */
    static double * apolloniusCourbure(Cercle c1,Cercle c2, Cercle c3){
        double * tab = new double[2];
        double k1 = c1.courbure;
        double k2 = c2.courbure;
        double k3 = c3.courbure;
        tab[0]=(k1+k2+k3+2*sqrt(k1*k2+k2*k3+k1*k3));
        tab[1]=(k1+k2+k3-2*sqrt(k1*k2+k2*k3+k1*k3));
        return tab;
    }

    public:

    /** The two radii matching apolloniusCourbure(). The caller owns the array. */
    static double * apolloniusRayon(Cercle c1,Cercle c2, Cercle c3){
        double * tab = apolloniusCourbure(c1,c2,c3);
        tab[0]=1/tab[0];
        tab[1]=1/tab[1];
        return tab;
    }

    /**
     * The circles tangent to c1, c2 and c3, from the complex form of Descartes'
     * theorem: z4*k4 = z1*k1 + z2*k2 + z3*k3 +/- 2*sqrt(z1*k1*z2*k2 + ...),
     * where each centre is read as a complex number. The four combinations of
     * the two signs and the two curvatures are all returned; the caller filters
     * them with valideCercleApollonius().
     */
    static vector<Cercle> apolloniusNouveauxCercles(Cercle c1,Cercle c2, Cercle c3){
        vector<Cercle>nouveauxCercles;
        double k1 = c1.courbure;
        double k2 = c2.courbure;
        double k3 = c3.courbure;
        double *k4 = apolloniusCourbure(c1,c2,c3);
        Complexe z1 = Complexe(c1.centre.x,c1.centre.y);
        Complexe z2 = Complexe(c2.centre.x,c2.centre.y);
        Complexe z3 = Complexe(c3.centre.x,c3.centre.y);

        Complexe zk1 = z1 * k1;
        Complexe zk2 = z2 * k2;
        Complexe zk3 = z3 * k3;

        Complexe sum = zk1 + zk2 + zk3;

        Complexe root=zk1*zk2+zk2*zk3+zk1*zk3;
        root=root.racineCarre()*2;

        Complexe res1 = sum + root;
        Complexe res2 = sum +(-root);
        res1=res1*(1/k4[0]);
        res2=res2*(1/k4[1]);

        Complexe res3 = sum + root;
        Complexe res4 = sum +(-root);
        res3=res3*(1/k4[1]);
        res4=res4*(1/k4[0]);

        nouveauxCercles.push_back(Cercle(0x00000000,Point(res1.a,res1.b),1/k4[0],false));
        nouveauxCercles.push_back(Cercle(0x00000000,Point(res2.a,res2.b),1/k4[1],false));
        nouveauxCercles.push_back(Cercle(0x00000000,Point(res3.a,res3.b),1/k4[1],false));
        nouveauxCercles.push_back(Cercle(0x00000000,Point(res4.a,res4.b),1/k4[0],false));
        delete[] k4;
        return nouveauxCercles;
    }

    operator string() {
        ostringstream os;
        os << "Cercle: centre=" << string(centre) << ", rayon= " << rayon ;
        return os.str();
    }
};
