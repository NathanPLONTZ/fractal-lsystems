#pragma once
#include "Forme.h"
#include "../Constantes.h"
#include <vector>
#include <cmath>

using namespace std;

/**
 * Line segment, rasterised with Bresenham's algorithm.
 *
 * `points` is only used by the Koch snowflake: see segmentFloconDeKoch().
 */
class Segment : public Forme
{
public:
	Point p1;
    Point p2;
    vector<Point> points;
public:

    Segment(unsigned long color) : Forme(color) {
	}

    Segment() : Forme(0x00000000) {
        Point p1(0,0);
        Point p2(0,0);
        this->p1 = p1;
        this->p2 = p2;
	}

	Segment(unsigned long color,Point p1, Point p2) : Forme(color) {
		this->p1 = p1;
		this->p2 = p2;
	}

    Segment copie(){
        return Segment(this->color,this->p1,this->p2);
    }

    void setPoints(vector<Point> points){
        this->points=points;
    }

    /** First third of the segment. */
    Segment segmentUnTiers(){
        Segment ss(this->color,this->p1,this->p1.tiersPoint(this->p2));
        return ss;
    }

    /** Middle third of the segment: the part Koch replaces with a bump. */
    Segment segmentDeuxTiers(){
        Segment ss(this->color,this->p1.tiersPoint(this->p2),this->p1.deuxTiersPoint(this->p2));
        return ss;
    }

    /** Last third of the segment. */
    Segment segmentTroisTiers(){
        Segment ss(this->color,this->p1.deuxTiersPoint(this->p2),this->p2);
        return ss;
    }

    Segment pivoteSegment(double beta){
        return Segment(this->color,this->p1,this->p1.rotatePoint(this->p2,beta));
    }

    double taille(){
        return this->p1.distance(this->p2);
    }

    void dessine(GrosseImage& im){
        double ex=abs(p2.x-p1.x);
        double ey=abs(p2.y-p1.y);
        double Dx=ex;
        double Dy=ey;
        int i=0;
        int Xincr=1;
        int Yincr=1;
        if(p1.x>p2.x)
            Xincr=-1;
        if(p1.y>p2.y)
            Yincr=-1;

        Point p1Copie=p1.copie();

        if(Dx>=Dy){
            while(i<=Dx){
                im.set(p1Copie.x,p1Copie.y,color);
                i++;
                p1Copie.x+=Xincr;
                ex-=Dy;
                if(ex<0){
                    p1Copie.y+=Yincr;
                    ex+=Dx;
                }
            }
        }

        if(Dy>Dx){
            while(i<=Dy){
                im.set(p1Copie.x,p1Copie.y,color);
                i++;
                p1Copie.y+=Yincr;
                ey-=Dx;
                if(ey<0){
                    p1Copie.x+=Xincr;
                    ey+=Dy;
                }
            }
        }
    }

    /**
     * Draws the segment and returns the pixels it covered.
     *
     * Bresenham is not self-similar: rasterising a third of a segment does not
     * give the same pixels as the corresponding third of the whole segment, so
     * the Koch construction cannot just recurse on endpoints. It keeps the
     * actual pixel list instead and slices it. When `points` is already filled
     * the slice is simply redrawn.
     */
    vector<Point> segmentFloconDeKoch(GrosseImage& im) {
        if(this->points.size()!=0){
            for(unsigned long i=0;i<this->points.size();i++){
                im.set(this->points[i].x,this->points[i].y,color);
            }
            return this->points;
        }
        vector<Point> points;
        double ex=abs(p2.x-p1.x);
        double ey=abs(p2.y-p1.y);
        double Dx=ex;
        double Dy=ey;
        int i=0;
        int Xincr=1;
        int Yincr=1;
        if(p1.x>p2.x)
            Xincr=-1;
        if(p1.y>p2.y)
            Yincr=-1;

        Point p1Copie=p1.copie();

        if(Dx>=Dy){
            while(i<=Dx){
                Point copie = p1Copie.copie();
                points.push_back(copie);
                im.set(p1Copie.x,p1Copie.y,color);
                i++;
                p1Copie.x+=Xincr;
                ex-=Dy;
                if(ex<0){
                    p1Copie.y+=Yincr;
                    ex+=Dx;
                }
            }
        }

        if(Dy>Dx){
            while(i<=Dy){
                Point copie = p1Copie.copie();
                points.push_back(copie);

                im.set(p1Copie.x,p1Copie.y,color);
                i++;
                p1Copie.y+=Yincr;
                ey-=Dx;
                if(ey<0){
                    p1Copie.x+=Xincr;
                    ey+=Dy;
                }
            }
        }
        return points;
    }

    /** Erases the middle third, the step that turns a segment into a Koch bump. */
    static void blancDeuxiemeTiers(GrosseImage& im,vector<Point>& points){
        for(unsigned long i=0;i<points.size();i++){
            if(i>=round(points.size()/3) && i<=round(2*points.size()/3)){
                im.set(points[i].x,points[i].y,0xFFFFFF00);
            }
        }
    }

    operator string() {
        ostringstream os;
        os << "Segment:P1=" << string(p1) << ", P2=" << string(p2);
        return os.str();
    }
};
