#include "funcs.h"

int main() {
    char archivosTxt[100][256];
    int numArchivos;

    crearDirectorios();

    listarArchivosTxt(archivosTxt, &numArchivos);

    for (int i = 0; i < numArchivos; i++) {
        //eficiente
        //resolver_sopa2(archivosTxt[i]);
        
        //ineficiente
        resolver_sopa(archivosTxt[i]);
    }

    return 0;
}