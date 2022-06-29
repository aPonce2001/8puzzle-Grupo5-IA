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

    //Constructor
    nodo(){
        padre = NULL;
        hijos = NULL;
        factorRamificacion = 0;
        costoRecorrido = 0;
    }

    //Implementación de la función sucesor
    void funcionSucesor(){
        int movimientosTotales = 4; //Existen 4 movimientos totales, izquierda, derecha, arriba y abajo.
        int numeroHijos = 0; //Contador de los hijos a ingresar
        int posicionHueco = e.obtenerPosicionHueco(); //Posición en forma de array del hueco del puzzle

        //Posiciones en forma matricial del hueco del array. Sirven para comprobar que al mover la ficha, no se salga del rango filas y columnas: [0; N)
        int filaHueco = posicionHueco / FILAS;
        int columnaHueco = posicionHueco % FILAS;

        //Lista de las posibles acciones con las posiciones matriciales
        int acciones[4][2] = {
            {1, 0},//Traer la ficha debajo del hueco
            {-1, 0},//Traer la ficha arriba del hueco
            {0, 1},//Traer la ficha de la derecha del hueco
            {0, -1}//Traer la ficha de la izquierda del hueco
        };

        //Se inician los hijos del nodo actual
        hijos = new nodo*[movimientosTotales];

        //Para todos los movimientos actuales
        for(int i = 0; i < movimientosTotales; i++){
            //Se verifica que las casillas movidas no salgan del rango del puzzle. Si lo hace, se pasa al siguiente paso.
            if(filaHueco + acciones[i][0] < 0 || filaHueco + acciones[i][0] > FILAS - 1 || columnaHueco + acciones[i][1] < 0 || columnaHueco + acciones[i][1] > FILAS - 1){
                continue;
            }

            //Se inicia un nuevo hijo para el nodo actual con el estado que tiene el padre
            hijos[numeroHijos] = new nodo();
            hijos[numeroHijos] -> padre = this;
            hijos[numeroHijos] -> profundidad = this -> profundidad + 1;
            hijos[numeroHijos] -> costoRecorrido = this -> costoRecorrido + 1;
            hijos[numeroHijos] -> e = this -> e;

            //Se halla la posición unidimensional de la siguiente posición para realizar el intercambio, es decir, mover la ficha al hueco.
            int siguientePosicion = ((filaHueco + acciones[i][0]) * FILAS) + columnaHueco + acciones[i][1];

            //Se realiza el intercambio entre la posición del hueco y la ficha disponible
            hijos[numeroHijos] -> e.intercambiarFichas(posicionHueco, siguientePosicion);

            //Se aumenta el contador de hijos
            numeroHijos++;
        }

        //Se configura el factor de ramificación de acuerdo al número de hijos que se obtuvo
        this -> factorRamificacion = numeroHijos;
    }

    //Función evaluación de A estrella f(n) = g(n) + h(n)
    int funcionEvaluacion(){
        return costoRecorrido + e.distanciaManhattan();
    }

    //Imprimir el recorrido total de un nodo seleccionando sus padres
    void imprimirRecorrido(){
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
            solucion[j]->e.imprimirEstado();
            cout << "Costo recorrido: " << solucion[j] -> costoRecorrido << endl << endl;
        }
    }
};

#endif // NODO_H_INCLUDED
