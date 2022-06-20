#include <iostream>
#include "estado.h"
#include "nodo.h"

using namespace std;

int main()
{
    int fichitas[FILAS * FILAS] = {7, 2, 4, 5, 0, 6, 8, 3, 1};
    nodo n;
    nodo n1;
    nodo n2;

    n.setFichas(fichitas);
    if(!n.e.tieneSolucion()){
        cout<<"No tiene solución"<<endl;
        return -1;
    }
    //n.fichas.printEstado();

    //cout<<n.fichas.distanciaManhattan();

    //Pruebas de la función --Luego de comprobar su funcionamiento, por favor, borrar--
    int fichitas2[FILAS * FILAS] = {7, 2, 4, 5, 6, 0, 8, 3, 1};
    n1.setFichas(fichitas2);

    int fichitas3[FILAS * FILAS] = {7, 2, 0, 5, 6, 4, 8, 3, 1};
    n2.setFichas(fichitas3);

    n.padre = &n1;
    n1.padre = &n2;

    n.imprimirRecorrido();
    return 0;
}
