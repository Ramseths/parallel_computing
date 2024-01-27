// Tarea 1. Programación de una solución paralela
#include <iostream>
#include <omp.h>
#include <random>
#include <time.h>

#define N 50000 // Cantidad de elementos en los arreglos
#define chunk 250 // Cantidad de elementos para cada hilo
#define elements 5 // Elementos que se mostrarán

void showArrayValues(int* d);

int main()
{
    std::cout << "Suma de dos arreglos con programación paralela\n";

    // Semilla para números aleatorios
    srand(time(NULL));

    int arrUno[N], arrDos[N], arrRes[N];

    // Se generan valores aleatorios
    for (int i = 0; i < N; ++i) {
        arrUno[i] = rand() % 10;
        arrDos[i] = rand() % 10;
    }

    int batchSize = chunk;
    int i;

#pragma omp parallel for \
    shared(arrUno, arrDos, arrRes, batchSize) private (i) \
    schedule(static, batchSize)
    for (i = 0; i < N; i++) {
        arrRes[i] = arrUno[i] + arrDos[i];
    }

    // Mostrar mensajes en consola
    std::cout << "Mostrando los primeros 10 valores del arreglo uno" << std::endl;
    showArrayValues(arrUno);
    std::cout << "\nMostrando los primeros 10 valores del arreglo dos" << std::endl;
    showArrayValues(arrDos);
    std::cout << "\nMostrando los primeros 10 resultados de la suma de los arreglos" << std::endl;
    showArrayValues(arrRes);
}

void showArrayValues(int* d) {
    for (int i = 0; i < 10; i++) {
        std::cout << d[i] << " | ";
    }
    std::cout << std::endl;
}

