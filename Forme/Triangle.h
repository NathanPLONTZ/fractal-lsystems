#pragma once
#include "Forme.h"

using namespace std;

/**
 * Triangle given by its three corners.
 *
 * Filled by testing every pixel of the image for membership, which is what
 * SierpinskiTriangle.cpp relies on to paint alternating colours over the
 * previous subdivision.
 */
class Triangle : public Forme
{
public:
	Point p1;
    Point p2;
    Point p3;
public:
	Triangle(unsigned long color,Point p1, Point p2,Point p3) : Forme(color) {
		this->p1 = p1;
		this->p2 = p2;
        this->p3 = p3;
	}

    void dessine(GrosseImage& im){
        for(int i=0; i<=im.getNombreLignes()-1;i++)
            for(int j=0; j<=im.getNombreLignes()-1;j++)
                if(Point(i,j).pointDansTriangle(*this))
                    im.set(i,j,this->color);
    }

    operator string() {
        ostringstream os;
        os << "Triangle: P1=" << string(p1) << ", P2=" << string(p2)  << ", P3=" << string(p3) ;
        return os.str();
    }
};
