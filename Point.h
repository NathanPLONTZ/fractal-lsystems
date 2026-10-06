#pragma once
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

class Triangle ;
class Rectangle ;
class Cercle ;

/**
 * Point of the plane, in image coordinates: x is the row, y the column.
 *
 * Beyond the usual vector arithmetic it carries the few constructions the
 * fractals need: thirds of a segment for Koch, midpoints for Sierpinski, and
 * rotation for the L-system turtle.
 */
class Point {
public:
    double x;
    double y;

    Point(){
        x = 0;
        y = 0;
    }

    Point(double xCoord, double yCoord) {
        x = xCoord;
        y = yCoord;
    }

    Point copie() {
        return Point(this->x, this->y);
    }

	Point operator +(Point v) const{
		return Point(this->x + v.x, this->y + v.y);
	}

	Point operator *(double a) const{
		return Point(this->x * a, this->y * a);
	}

	Point  operator-() const{
		return Point(-x, -y);
	}

    Point  operator-(double a) const{
		return Point(x-a, y-a);
	}

     Point  operator+(double a) const{
		return Point(x+a, y+a);
	}

	bool operator==(Point o) const{
		return (x==o.x)&&(y==o.y);
	}

    Point milieu(Point p){
        return Point((this->x+p.x)/2,(this->y+p.y)/2);
    }

    /** Point one third of the way from this point to p. */
    Point tiersPoint(Point p){
        return Point((2*this->x+p.x)/3,(2*this->y+p.y)/3);
    }

    /** Point two thirds of the way from this point to p. */
    Point deuxTiersPoint(Point p){
        return Point((this->x+2*p.x)/3,(this->y+2*p.y)/3);
    }

    double distance (Point p){
        return sqrt(pow(p.x-this->x,2)+pow(p.y-this->y,2));
    }

    /**
     * Third corner of the right isosceles triangle on AB, where A is this point
     * and B is p2: BC has the same length as AB and is turned a quarter turn
     * clockwise from it. The turtle pivots around this corner.
     */
    Point pointAngleDroit(Point p2) {
        Point A = *this;
        Point B = p2;

        double vecAB_x = B.x - A.x;
        double vecAB_y = B.y - A.y;

        double vecBC_x = vecAB_y;
        double vecBC_y = -vecAB_x;

        double lengthAB = std::sqrt(vecAB_x * vecAB_x + vecAB_y * vecAB_y);
        double lengthBC = lengthAB;

        double C_x = B.x + (vecBC_x / lengthAB) * lengthBC;
        double C_y = B.y + (vecBC_y / lengthAB) * lengthBC;

        return Point(C_x, C_y);
    }

    /** This point rotated by `beta` around pO, clockwise in image coordinates. */
    Point rotatePoint(Point pO, double beta) {
        beta=-beta;
        double cosBeta = cos(beta);
        double sinBeta = sin(beta);

        double xC = (this->x - pO.x) * cosBeta + (this->y - pO.y) * sinBeta + pO.x;
        double yC = - (this->x - pO.x) * sinBeta + (this->y - pO.y) * cosBeta + pO.y;

        return Point(xC, yC);
    }

    operator string (){
        ostringstream os;
        os << "(" << x << ", " << y << ")";
        return os.str();
	}

    bool pointDansTriangle(Triangle t);
    bool pointDansRectangle(Rectangle r);
    bool pointDansCercle(Cercle r);
};
