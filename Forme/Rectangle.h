#pragma once
#include "Forme.h"

using namespace std;

/**
 * Axis-aligned rectangle given by its four corners.
 *
 * Filled by testing every pixel of the image for membership, which is what
 * SierpinskiTapis.cpp relies on to punch the central square out of each tile.
 */
class Rectangle : public Forme
{
public:
	Point p1;
    Point p2;
    Point p3;
    Point p4;
public:
	Rectangle (unsigned long color,Point p1, Point p2,Point p3, Point p4) : Forme(color) {
		this->p1 = p1;
		this->p2 = p2;
        this->p3 = p3;
        this->p4 = p4;
	}

    double getCote(){
        return abs(p1.y-p2.y);
    }

    void dessine(GrosseImage& im){
        for(int i=0; i<=im.getNombreLignes()-1;i++)
            for(int j=0; j<=im.getNombreColonnes()-1;j++)
                if(Point(i,j).pointDansRectangle(*this))
                    im.set(i,j,this->color);
    }

    operator string() {
        ostringstream os;
        os << "Rectangle:P1=" << string(p1) << ", P2=" << string(p2)  << ", P3=" << string(p3) << ", P4=" << string(p4) ;
        return os.str();
    }
};
