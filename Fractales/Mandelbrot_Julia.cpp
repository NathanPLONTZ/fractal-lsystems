#include <cstdio>
#include <cstring>
#include <string>
#include <complex>
#include <sstream>
#include <iomanip>
#include "../GrosseImage.h"
using namespace std;

/**
 * Mandelbrot and Julia sets.
 *
 * Both are escape-time fractals: a point of the complex plane is coloured by
 * how many iterations of z -> z^2 + c it survives before |z| passes 2, which is
 * the radius beyond which the sequence is certain to diverge. The two differ
 * only in what c is. For Mandelbrot, c is the point being tested, so the image
 * maps which c keep the orbit of 0 bounded; for Julia, c is a fixed constant
 * and the point being tested is the starting z.
 *
 * Run with no argument for the Mandelbrot set, or with "julia" for the Julia
 * set of c = -0.54 + 0.54i.
 */

const unsigned long LARGEUR = 800;
const unsigned long HAUTEUR = 500;

unsigned long m = HAUTEUR-1;
unsigned long n = LARGEUR-1;

/** Packs three 0-255 channels into one opaque RGBA colour. */
unsigned long couleurEntierToCouleurHexa(int r, int g, int b){
    ostringstream colorStream;
    colorStream << hex << setw(2) << setfill('0') << r
    << setw(2) << setfill('0') << g
    << setw(2) << setfill('0') << b;

    string hexColor = colorStream.str();

    // append the alpha channel, fully opaque
    hexColor = "0x" + hexColor + "FF";

    unsigned long finalColor = stoul(hexColor, nullptr, 16);

    return finalColor;
}

/** Escape time of z0 under z -> z^2 + c, for the fixed c of the Julia set. */
int julia(const complex<double> z0, const int max_iterations) {
    complex<double> z = z0;
	complex<double> c(-0.54,0.54);
    for (int i = 0; i < max_iterations; ++i) {
        if (abs(z) > 2.0) {
            return i;
        }
        z = z * z + c;
    }
    // still bounded after max_iterations: treat the point as inside the set
    return 0;
}

/** Escape time of 0 under z -> z^2 + z0, which is the Mandelbrot test. */
int mandelbrot(const complex<double> z0, const int max_iterations) {
    complex<double> z = z0;
    for (int i = 0; i < max_iterations; ++i) {
        if (abs(z) > 2.0) {
            return i;
        }
        z = z * z + z0;
    }
    // still bounded after max_iterations: treat the point as inside the set
    return 0;
}

int main(int argc, char** argv)
{
bool ensembleJulia = (argc > 1 && strcmp(argv[1], "julia") == 0);

string nomFichier = ensembleJulia ? "../Images/Julia.bmp" : "../Images/Mandelbrot.bmp";

const int MAX_ITERATIONS = 1000;
const double MIN_X = -2.0;
const double MAX_X = 2.0;
const double MIN_Y = -1.125;
const double MAX_Y = 1.125;

int i,j;

GrosseImage grosseImage(nomFichier, LARGEUR, HAUTEUR, 0x00000000);

for ( i = 0; i <= m ; ++i)
for ( j = 0; j <= n ; ++j)
{
	double real = MIN_X + (MAX_X - MIN_X) * j / (LARGEUR - 1);
    double imag = MIN_Y + (MAX_Y - MIN_Y) * i / (HAUTEUR - 1);
    complex<double> c(real, imag);
    int value = ensembleJulia ? julia(c, MAX_ITERATIONS) : mandelbrot(c, MAX_ITERATIONS);

	int r = (value * 10) % 256;
    int g = (value) % 256;
    int b = (value) % 256;

    unsigned long finalColor = couleurEntierToCouleurHexa(r,g,b);

	grosseImage.set(i,j,finalColor);
}

printf("image creee\n");

return 0;
}
