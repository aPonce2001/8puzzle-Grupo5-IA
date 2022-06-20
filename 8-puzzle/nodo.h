#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
#include <iostream>
#include "estado.h"
class nodo{
public:

    nodo* padre;
    nodo** hijos;
    int profundidad;
    int factorRamificacion;
    int costoRecorrido; //g(n)
    estado e;

    nodo(){
        padre = NULL;
        hijos = NULL;
        factorRamificacion = 0;
        costoRecorrido = 0;
    }

    void funcionSucesor(){

    }

    void setFichas(estado e){
        this->e = e;
    }

    void setFichas(int e[FILAS * FILAS]){
        this->e.setFichas(e);
    }

    //Función evaluación de A estrella f(n) = g(n) + h(n)
    int funcionEvaluacion(){
        return costoRecorrido + e.distanciaManhattan();
    }

    //Imprimir el recorrido total de un nodo seleccionando sus padres
    void imprimirRecorrido(){
        /*if(this == NULL){
            cout<<"El problema no tiene solución.";
            return;
        }*/

        //Se almacenan los nodos en un arreglo dinámico
        nodo* aux = this;
        nodo** solucion = new nodo*[22];
        int i;
        for(i = 0; aux->padre != NULL; i++){
            solucion[i] = aux;
            aux = aux->padre;
        }
        solucion[i] = aux;

        //Se imprime desde el último hasta el primer (padre == NULL)
        for(int j = i; j > -1; j--){
            solucion[j]->e.printEstado();
            cout<<endl;
        }
    }
};

#endif // NODO_H_INCLUDED
