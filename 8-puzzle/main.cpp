#include <iostream>
#include "estado.h"

using namespace std;

int main()
{
    int fichitas[FILAS * FILAS] = {7, 2, 4, 5, 0, 6, 8, 3, 1};
    estado e;

    e.setFichas(fichitas);
    if(!e.tieneSolucion()){
        cout<<"No tiene solución"<<endl;
        return -1;
    }
    e.printEstado();

    cout<<e.distanciaManhattan();
    return 0;
}
