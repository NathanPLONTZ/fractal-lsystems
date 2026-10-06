#pragma once
#include <cmath>
using namespace std;

/**
 * Complex number a + bi.
 *
 * Only what the Apollonian gasket needs: the complex form of Descartes' circle
 * theorem treats each centre as a complex number, so centres have to be added,
 * multiplied and square-rooted. std::complex would do, but Cercle stores plain
 * doubles and this keeps the conversion trivial.
 */
class Complexe {

public:
    double a;
    double b;

    Complexe(){
        a = 0;
        b = 0;
    }

    Complexe(double aCoord, double bCoord) {
        a = aCoord;
        b = bCoord;
    }

    Complexe copie() {
        return Complexe(this->a, this->b);
    }

    Complexe operator +(Complexe v) const{
        return Complexe(this->a + v.a, this->b + v.b);
    }

    Complexe operator *(Complexe v) const{
        return Complexe(this->a * v.a - this->b * v.b, this->a * v.b + this->b * v.a);
    }

    Complexe  operator-() const{
        return Complexe(-a, -b);
    }

    Complexe operator *(double a) const{
        return Complexe(this->a * a, this->b * a);
    }

    /** Principal square root, taken in polar form: sqrt(r) * e^(i*theta/2). */
    Complexe racineCarre() const{
        double r = sqrt(a*a + b*b);
        double angle = atan2(b, a);
        r = sqrt(r);
        angle=angle/2;
        return Complexe(r * cos(angle), r * sin(angle));
    }
};
