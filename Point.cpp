#include "Point.h"
#include "./Forme/Triangle.h"
#include "./Forme/Rectangle.h"
#include "./Forme/Cercle.h"

/**
 * Membership tests, defined here rather than in the header because they need
 * the shape classes, which themselves need Point.
 */

/** Barycentric test: the point is inside when all three coordinates are in (0,1). */
bool Point::pointDansTriangle(Triangle t){
        double i = this->x;
        double j = this->y;
        double x1 =t.p1.x;
        double y1 =t.p1.y;
        double x2 =t.p2.x;
        double y2 =t.p2.y;
        double x3 =t.p3.x;
        double y3 =t.p3.y;
        double detT = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
        double alpha = ((y2 - y3) * (i - x3) + (x3 - x2) * (j - y3)) / detT;
        double beta = ((y3 - y1) * (i - x3) + (x1 - x3) * (j - y3)) / detT;
        double gamma = 1 - alpha - beta;

        return alpha > 0 && beta > 0 && gamma > 0 && alpha < 1 && beta < 1 && gamma < 1;
}

bool Point::pointDansRectangle(Rectangle r) {
    double x = this->x;
    double y = this->y;
    double coinSuperieurGaucheX = r.p1.x;
    double coinSuperieurGaucheY = r.p1.y;
    double largeur = abs (r.p2.y-r.p1.y);
    double hauteur = abs (r.p3.x-r.p1.x);

    double xMin = coinSuperieurGaucheX + largeur;
    double yMin = coinSuperieurGaucheY + hauteur;

    if (x >= coinSuperieurGaucheX && x <= xMin && y >= coinSuperieurGaucheY && y <= yMin) {
        return true;
    } else {
        return false;
    }
}

bool Point::pointDansCercle(Cercle c) {
    if(this->distance(c.centre)<c.rayon)
        return true;
    else
        return false;
}
