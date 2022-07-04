#include <iostream>
#include "estado.h"
#include "nodo.h"
void Solve_Problem(nodo *);
bool ASTAR(nodo *);

using namespace std;

int main()
{
    int fichitas[FILAS * FILAS] = {7, 2, 4, 5, 0, 6, 8, 3, 1};      //Creación del estado inicial
    nodo nr;                                                        //Creación del nodo raiz
    nodo *pnr = nr.autoApuntador();                                 //Puntero al nodo raiz
    nr.e.setFichas(fichitas);                                       //Se pasa al nodo raiz el estado inicial
    Solve_Problem(pnr);                                             //Busca una solución al problema
    return 0;
}

//Función que resuelve el problema
void Solve_Problem(nodo *na){
    if (ASTAR(na)==false){
        cout<<"No tiene solucion\n";
    }else{
        cout<<"****** Solucion encontrada ******\n";
    }
};

bool ASTAR(nodo *n){
    //Creación de una frontera y un apuntador a la frontera
    frontera fronter;
    frontera *pfrontera=NULL;
    pfrontera=fronter.autoApuntadorFront();
    //Creación de una lista de nodos con los estados visitados y un puntero a esa lista
    frontera visitado;
    frontera *pvisitado=visitado.autoApuntadorFront();

    pfrontera->nuevoElemento(n);                        //Se ingresa el nodo raiz a la frontera
    nodo *na;
        do{
                na=pfrontera->extraerMejorF();          //Extrae el nodo con mejor f(n), sabiendo que A* -> f(n)=g(n)+h(n)
                pvisitado->nuevoElemento(na);           //El nodo se ingresa a la lista de visitados
                if((na->e.testObjetivo()) ){            // Test objetivo para saber si el nodo actual es el nodo objetivo
                        cout<<"\nEXISTE UNA SOLUCION: \nSE DESCRIBE LOS PASOS A REALIZAR: "<<endl;
                        na->imprimirRecorrido();        //Imprime el recorrido desde la raiz hasta el nodo actual
                        return true;
                }else{                                  //Si no es el objetivo entonces:
                    na->funcionSucesor();               //Se expande el nodo creando los hijos
                    for(int i=0; i<na->factorRamificacion;i++){         //Para cada hijo
                        if(!pvisitado->fueVisitado(na->hijos[i])){      //Si el estado del hijo no ha sido visitado
                          pfrontera->nuevoElemento(na->hijos[i]);       //El hijo se agrega a la frontera
                        }
                    }
                    pfrontera->eliminarElemento(na);    //Elimina el nodo analizado de la frontera
                }
        }while(pfrontera->fronteraVacia()==false);  //Bucle mientras existan elementos en la frontera
        return false;
};

