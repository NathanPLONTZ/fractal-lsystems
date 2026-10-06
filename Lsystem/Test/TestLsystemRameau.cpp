#include <fstream>
#include <string>
#include "../Regles/RegleX_XXCoMoinsXPlusXPlusXCfCoPlusXMoinsXMoinsXCf.h"
#include "../../BoxCounting.h"
#include "../LsystemRameau.h"

using namespace std;

/**
 * Draws the Branchlet L-system into Images/LsystemRameau.bmp, and measures its
 * fractal dimension.
 *
 * Axiom: X
 * Rules: X -> XX[-X+X+X][+X-X-X]
 * Depth: 4
 *
 * This L-system was invented for this project, not taken from the literature,
 * and it is the shape the reported dimension estimate is for. Because no
 * published value exists to check it against, the method -- box counting -- was
 * validated first on the Koch snowflake, whose dimension is known analytically;
 * see Fractales/FloconDeKoch.cpp and BoxCounting.h.
 */

/**
 * Draws the same L-system at a series of step sizes and records (log s, log N)
 * for each, where N is the number of pixels covered.
 *
 * Not called by default: uncomment the call in main() to regenerate the data
 * that Lsystem/Test/regressionLineaire.R reads back.
 */
void enregistrementData(){
    ofstream fichierX("../Lsystem/Test/dataXRameau.txt");
    ofstream fichierY("../Lsystem/Test/dataYRameau.txt");
    int constante =4000;
    int cpt=0;
    int longueur = 2;
    int scale=0;
    int tmp;
    while(cpt<=5){
        if(scale!=0)
            tmp=constante-longueur*scale;
        else
            tmp=constante-longueur;
        LsystemRameau l(new SymboleX(), 4);
        RegleX_XXCoMoinsXPlusXPlusXCfCoPlusXMoinsXMoinsXCf r1("X_XX[-X+X+X][+X-X-X]", NULL);
        l.regles = &r1;
        l.curseur=Segment(0xFFFFFF00,Point(4000,2000),Point(tmp,2000));
        string nomFichier =  "../Images/TestDimension.bmp";
        GrosseImage grosseImage(nomFichier, 4001, 4001, 0x00000000);
        l.dessine(grosseImage);
        ecritEchantillon(fichierX, fichierY, scale, compteurCase(grosseImage, 0x00000000));
        if(cpt==0)
            scale++;
        scale=scale*2;
        cpt++;
    }

    fichierX.close();
    fichierY.close();
}

int main () {

    LsystemRameau l(new SymboleX(), 4);
    RegleX_XXCoMoinsXPlusXPlusXCfCoPlusXMoinsXMoinsXCf r1("X_XX[-X+X+X][+X-X-X]", NULL);
    l.regles = &r1;

    // starting cursor: its length is the step size and its direction the
    // initial heading of the turtle
    l.curseur=Segment(0xFFFFFF00,Point(2000,1000),Point(1964,1000));

    string nomFichier =  "../Images/LsystemRameau.bmp";
    GrosseImage grosseImage(nomFichier, 2001, 2001, 0x00000000);
    l.dessine(grosseImage);

    //enregistrementData();
    return 0;
}
