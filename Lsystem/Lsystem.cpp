#include "Lsystem.h"
#include "./Symbole/Symbole.h"

void Lsystem::afficher() {
    for(vector<Symbole*>::iterator it = symboles.begin(); it != symboles.end(); ++it){
        (*it)->affiche();
    }
}
