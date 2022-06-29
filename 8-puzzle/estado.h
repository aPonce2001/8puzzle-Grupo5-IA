#ifndef ESTADO_H_INCLUDED
#define ESTADO_H_INCLUDED
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
#define FILAS 3 //Número de filas y columnas del puzzle

class estado{
public:

    int fichas[FILAS*FILAS];//Representación del (N²-1)-puzzle en un arreglo de FILAS² posiciones

    estado(){

    };

    void setFichas(int fichas[FILAS * FILAS]){
        /*Función memcpy: Copia los valores de un arreglo en la variable fichas del estado.
         *Se declara el destino, origen y tamaño en bytes a copiar*/
        memcpy(this->fichas, fichas, FILAS * FILAS * sizeof(int));
    }

    //Función para imprimir en una matriz una representación del (N²-1)-puzzle
    void imprimirEstado(){
        for(int i = 0; i < FILAS; i++){
            for(int j = 0; j < FILAS - 1; j++){
                cout<<fichas[(FILAS * i) + j]<<"\t";
            }
            cout<<fichas[(FILAS * i) + (FILAS - 1)]<<endl;
        }
    }

    //Cálculo de la distancia de Manhattan total como una heurística donde:
    int distanciaManhattan(){
        int aux = 0;//Variable para aumentar los valores
        for(int i = 0; i < FILAS * FILAS; i++){//Se recorre todo el arreglo
            if(fichas[i] != 0){//No se cuenta a la ficha 0, que representa a la ficha vacía

                /*La función de Manhattan es igual a |xf-x0| + |yf-y0|. Donde xf representa a la columna donde se debe encontrar el
                 *valor consultado, yf a la fila donde se debe encontrar el valor. x0 y y0 son las coordenadas [columna][fila] donde se
                 *encuentra el valor actual.
                 *
                 *Como se está utilizando un arreglo, las posiciones serán entre 0 a FILAS²-1, por lo cual, no se tiene coordenadas de x.
                 *Esto se puede solucionar al saber que, una posición t se puede dividir en componentes de filas y columnas de acuerdo a:
                 *
                 *  FILA = t / (numero_total_columnas) en entero.   COLUMNA = Módulo entre t y número_total_columnas.
                 *
                 *En el (N²-1)-puzzle se tiene que numero_total_columans = FILAS, al tratarse de una matriz cuadrada.
                 *
                 *Por cómo está estructurada la resolución del problema, el valor t correspondiente al número de ficha se espera tener en
                 *la posición = t del arreglo, así que con ello, se obtendrá la posición esperada, con respecto a su valor de ficha.
                 *
                 *  Ejemplo: Ficha 1 está en posición 3 del arreglo fichas[]. La posición 3 será igual a: FILA = 3 / FILAS = 3/3 = 1.
                 *                                                                                        COLUMNA = 3 MOD 3 = 0.
                 *                                                            Posición 3 del arreglo corresponde a (1; 0) de una matriz.
                 *
                 *  Ahora Ficha 1 debería estar en t = 1. Así que, la posición esperada es: FILA = 1 / FILAS = 1 / 3 = 0.
                 *                                                                          COLUMNA = 1 MOD 3 = 1.
                 *                                                      Posición esperada de t = 1: (0; 1).
                 *
                 *En definitiva se tiene que la distancia de Manhattan de una ficha es igual a: |(fichas[t]/FILAS)-(t/FILAS)|+|(fichas[t] MOD FILAS)-(t MOD FILAS)|
                 */
                aux += abs((fichas[i]/FILAS) - (i/FILAS)) + abs((fichas[i]%FILAS) - (i%FILAS));
            }
        }
        return aux;
    }

    //Función que permite la determinación de si un estado del puzzle es resoluble o no. Para ello se guía en el número de inversiones que tiene el arreglo.
    bool tieneSolucion(){
        int inversiones = 0;
        //Se recorre el arreglo comparando con los elementos de al frente
        for(int i = 0; i < (FILAS * FILAS) - 1; i++){
            for(int j = i + 1; j < FILAS * FILAS; j++){
                //Si encuentra un valor menor por adelante, el contador de inversiones aumenta,
                //Se excluye a las casillas con valor 0 para la contabilización de inversiones
                if(fichas[i] > fichas[j] && fichas[i] != 0 && fichas[j] != 0){
                   inversiones++;
                }
            }
        }
        //Si el número de inversiones es par, entonces el problema será soluble
        return inversiones%2 == 0;
    }

    //Se cumple que un estado es solución si su distancia Manhattan es igual a 0
    bool testObjetivo(){
        return this->distanciaManhattan() == 0;
    }

    //Función que devuelve la posición del hueco del puzzle, es decir, donde el valor sea 0.
    int obtenerPosicionHueco(){
        for(int i = 0; i < FILAS * FILAS; i++){
            if(fichas[i] == 0){
                return i;
            }
        }
        return -1;
    }

    //Función que realiza los movimientos de las fichas realizando un intercambio directo
    void intercambiarFichas(int posicionA, int posicionB){
        int aux = fichas[posicionA];
        fichas[posicionA] = fichas[posicionB];
        fichas[posicionB] = aux;
    }
};

#endif // ESTADO_H_INCLUDED
