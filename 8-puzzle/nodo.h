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
        profundidad=0;
    };

    nodo* autoApuntador() { //Retorna un puntero a si mismo
        return this;
    };


    //Implementación de la función sucesor (Crea los hijos de un estado con los movimientos válidos)
    void funcionSucesor(){           //
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

        //Arreglo de hijos
        hijos = new nodo*[movimientosTotales];

        //Para todos los movimientos actuales
        for(int i = 0; i < movimientosTotales; i++){
            //Se verifica que las casillas movidas no salgan del rango del puzzle. Si lo hace, se pasa al siguiente paso.
            if(filaHueco + acciones[i][0] < 0 || filaHueco + acciones[i][0] > FILAS - 1 || columnaHueco + acciones[i][1] < 0 || columnaHueco + acciones[i][1] > FILAS - 1){
                continue;
            }
            hijos[numeroHijos] = new nodo();
            hijos[numeroHijos] -> padre = this;
            hijos[numeroHijos] -> profundidad = this -> profundidad + 1;
            hijos[numeroHijos] -> costoRecorrido = this -> costoRecorrido + 1;
            hijos[numeroHijos] -> e = this -> e;

            //Se halla la posición unidimensional de la siguiente posición para realizar el intercambio, es decir, mover la ficha al hueco.
            int siguientePosicion = ((filaHueco + acciones[i][0]) * FILAS) + columnaHueco + acciones[i][1];

            //Se realiza el intercambio entre la posición del hueco y la ficha disponible
            hijos[numeroHijos] -> e.intercambiarFichas(posicionHueco, siguientePosicion);

            numeroHijos++;
        }

        //Se configura el factor de ramificación de acuerdo al número de hijos que se obtuvo
        this -> factorRamificacion = numeroHijos;
    };

    //Función evaluación de A estrella f(n) = g(n) + h(n)
    int funcionEvaluacion(){
        return costoRecorrido + e.distanciaManhattan();
    };

    //Imprimir el recorrido total de un nodo seleccionando sus padres
    void imprimirRecorrido(){
        //Se almacenan los nodos en un arreglo dinámico
        nodo* aux = this;
        nodo** solucion = new nodo*[30];
        int i;
        for(i = 0; aux->padre != NULL; i++){
            solucion[i] = aux;
            aux = aux->padre;
        }
        solucion[i] = aux;

        //Se imprime desde el último hasta el primer (padre == NULL)
        for(int j = i; j > -1; j--){
            solucion[j]->e.imprimirEstado();
            cout << "Costo recorrido: " << solucion[j] -> costoRecorrido<< endl;
            cout << "Profundidad: " << solucion[j] ->profundidad << endl << endl;

        }
    }
};

class frontera{
public:
    nodo **f;
    int nEf;

    frontera(){
        f=NULL;
        nEf=0;
    }
    frontera * autoApuntadorFront(){
        return this;
    }
    bool fronteraVacia(){
        if(f==NULL){
                //cout<<"SE VACIO LA FRONTERA"<<endl;
            return true;
        }else{
            //cout<<"LA FRONTERA TODAVIA TIENE ELEMENTOS"<<endl;
            return false;
        }
    };

    void nuevoElemento (nodo *n){
        nodo **aux;                 //Arreglo temporal de punteros a nodos
        aux=new nodo* [nEf+1];      //Asigno dinamicamente nEf+1 elementos en ATPN (uno mas de lo que hay en f)
        for(int i=0;i<nEf;i++){
            aux[i]=f[i];            //ATPN igual a frontera APN (Arreglo de punteros a nodo)
            f[i]=NULL;              //Una vez respaldado apunto a nulo cada puntero de frontera
        }
        aux[nEf]=n;                 //Ingreso el nuevo elemento al final de la frontera
        if(nEf>0)
            delete[] f;             //Borro el espacio de memoria del arreglo de punteros de f
        f=NULL;                     //
        f=aux;                      //f toma lo que se tiene en auxx
        nEf++;                      //Aumento e numero de elementos de frontera
    };

    nodo * extraerMejorF(){
        int menorValor=f[0]->funcionEvaluacion();
        int aux, posMenVal=0;
        if(nEf<1){
            return f[0];
        }else{
            for(int i=1;i<nEf;i++){
                aux = f[i]->funcionEvaluacion();
                if(aux<menorValor){
                    menorValor=aux;
                    posMenVal=i;
                }
            }
        }
        return f[posMenVal];
    };

    bool eliminarElemento(nodo *n){
        bool resultado = false;
        nodo **aux;
        aux= new nodo*[nEf-1];
        int pos=-1;
        for(int i=0;i<nEf;i++){
            if(n==f[i]){
                pos=i;
                resultado=true;
                break;
            }
        }
        if(pos!=-1){
            for(int i=0;i<pos;i++){
                aux[i]=f[i];
                f[i]=NULL;
            }
            f[pos]=NULL;
            for(int i=pos;i<nEf-1;i++){
                aux[i]=f[i+1];
                f[i+1]=NULL;
            }

            delete[] f;
            f=NULL;
            f=aux;
            nEf--;
        }else{
            for(int i=0;i<nEf-1;i++){
                aux[i]=NULL;
            }
            delete[]aux;
            aux=NULL;
        }
        return resultado;
    };

    bool fueVisitado(nodo *n){
        bool resultado = false;
        for(int i=0;i<nEf;i++){
            if(n->e.estadoIgual(f[i]->e)){
                return true;
            }
        }
        return false;
    };

};

#endif // NODO_H_INCLUDED
