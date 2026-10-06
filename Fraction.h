#pragma once
#include <sstream>
#include <string>

using namespace std;

/**
 * Rational number, always kept in lowest terms with a positive denominator.
 *
 * Used by the Ford circles: every Ford circle corresponds to a rational p/q,
 * and the circle nested between two of them is indexed by their mediant, which
 * suiteDeFarey() computes.
 */
class Fraction {
    public:
        int numerateur;
        int denominateur;

        int pgcd(int a, int b) {
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

    public:

        Fraction() : numerateur(0), denominateur(1) {}

        Fraction(int numerateur, int denominateur) : numerateur(numerateur), denominateur(denominateur) {
            simplifier();
        }

        void simplifier() {
            int diviseur = pgcd(numerateur, denominateur);
            numerateur /= diviseur;
            denominateur /= diviseur;

            if (denominateur < 0) {
                numerateur = -numerateur;
                denominateur = -denominateur;
            }
        }

        Fraction operator+(Fraction other){
            return Fraction(numerateur * other.denominateur + other.numerateur * denominateur, denominateur * other.denominateur);
        }

        Fraction operator-(Fraction other){
            return Fraction(numerateur * other.denominateur - other.numerateur * denominateur, denominateur * other.denominateur);
        }

        Fraction operator*(Fraction other){
            return Fraction(numerateur * other.numerateur, denominateur * other.denominateur);
        }

        Fraction operator/(Fraction other){
            return Fraction(numerateur * other.denominateur, denominateur * other.numerateur);
        }

        bool operator==(Fraction other){
            return (numerateur == other.numerateur) && (denominateur == other.denominateur);
        }

        bool operator!=(Fraction other){
            return !(*this == other);
        }

        /**
         * Mediant of two fractions, (p1+p2)/(q1+q2): the term the Farey sequence
         * inserts between them, and the index of the Ford circle nested in the
         * gap they leave.
         */
        static Fraction suiteDeFarey(Fraction f1, Fraction f2){
            return Fraction(f1.numerateur+f2.numerateur,f1.denominateur+f2.denominateur);
        }

        operator std::string() const {
            std::ostringstream os;
            os <<"Fraction:" << numerateur << "/" << denominateur;
            return os.str();
        }
};
