#include <iostream>
#include "estado.h"
#include "nodo.h"

using namespace std;

int main()
{
    int fichitas[FILAS * FILAS] = {7, 2, 4, 5, 0, 6, 8, 3, 1};
    nodo n;

    n.e.setFichas(fichitas);
    if(!n.e.tieneSolucion()){
        cout<<"No tiene solución"<<endl;
        return -1;
    }

    //Pruebas de la función sucesor. Borren antes de crear el programa.
    n.funcionSucesor();
    n.hijos[0] -> funcionSucesor();
    n.hijos[0]->hijos[2]->funcionSucesor();

    n.hijos[0]->hijos[2]->hijos[0] -> imprimirRecorrido();
    n.hijos[0]->hijos[2]->hijos[1] -> imprimirRecorrido();

    return 0;
}
