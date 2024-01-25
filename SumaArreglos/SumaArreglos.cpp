// Tarea 1. Programación de una solución paralela
#include <iostream>
#include <omp.h>
#include <random>
#include <stdlib.h>
#include <time.h>

#define N 5000 // Cantidad de elementos en los arreglos
#define chunk 250 // Cantidad de elementos para cada hilo
#define elements 10 // Elementos que se mostrarán

void showArrayValues(int* d);

int main()
{
    std::cout << "Suma de dos arreglos con programación paralela\n";

    // Semilla para números aleatorios
    srand(time(NULL));

    int a[N], b[N], c[N];

    // Se generan valores aleatorios
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    int batchSize = chunk;
    int i;

#pragma omp parallel for \
    shared(a, b, c, batchSize) private (i) \
    schedule(static, batchSize)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Mostrar mensajes en consola
    std::cout << "Mostrando los primeros 10 valores del arreglo a" << std::endl;
    showArrayValues(a);
    std::cout << "\nMostrando los primeros 10 valores del arreglo b" << std::endl;
    showArrayValues(b);
    std::cout << "\nMostrando los primeros 10 resultados de la suma de los arreglos en c" << std::endl;
    showArrayValues(c);
}

void showArrayValues(int* d) {
    for (int i = 0; i < 10; i++) {
        std::cout << d[i] << " | ";
    }
    std::cout << std::endl;
}

