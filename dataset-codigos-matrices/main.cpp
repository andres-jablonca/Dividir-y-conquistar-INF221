#include "iterativoCubico.hpp"
#include "strassen.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;



// Función para llenar la matriz con valores aleatorios en el rango [-7, 7]
// Como cada algoritmo de multiplicacion implementado no depende de las características de las matrices y solo depende del tamano de estas, da igual su contenido, por eso se rellena aleatoriamente.
void rellenarmatriz(vector<vector<int>>& m) {
    int n = m.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            m[i][j] = rand() % 51 - 7;
        }
    }
}

// Función para leer el archivo binario con los tamanos y generar matrices
void generatematricesFromFile(const char* nombreArchivo) {
    // Abrir el archivo binario en modo de lectura
    ifstream arch(nombreArchivo, ios::binary);
    if (!arch) {
        cerr << "Error al abrir el archivo para lectura." << endl;
        return;
    }

    srand(time(0)); // Inicializar la semilla para números aleatorios

    while (!arch.eof()) {
        int n;
        arch.read(reinterpret_cast<char*>(&n), sizeof(n)); // Leer el tamaño de la matriz
        if (arch.eof()) break; // Salir del ciclo si se llega al final del archivo

        vector<vector<int>> a, b, b_t, d;
        a = crearMatriz(n);
        rellenarmatriz(a);
        b = crearMatriz(n);
        rellenarmatriz(b);
        b_t = b;

        cout<<"Para matrices de tamano " << n << " x "<< n << ": \n";

        auto start = high_resolution_clock::now();  // Medir tiempo inicio
        mult(n, a, b);  // Multiplicar A x B
        auto end = high_resolution_clock::now(); // Medir tiempo fin
        duration<double> tiempo = end - start;
        cout << "Iterativo cubico tradicional: " << tiempo.count() << " segundos" << endl;

        trasponer(n, b_t); // Trasponer B
        start = high_resolution_clock::now(); // Medir tiempo inicio
        mult_traspuesta(n, a, b_t); // Multiplicar A x B_traspuesta
        end = high_resolution_clock::now(); // Medir tiempo fin
        tiempo = end - start;
        cout << "Iterativo cubico trasponiendo: " << tiempo.count() << " segundos" << endl;
        
        start = high_resolution_clock::now(); // Medir tiempo inicio
        d = strassen(a, b); // Multiplicar A x B usando Strassen
        end = high_resolution_clock::now(); // Medir tiempo fin
        tiempo = end - start;
        cout << "Strassen: " << tiempo.count() << " segundos\n" << endl;
    }

    arch.close();
}

int main() {
    // Es necesario que el archivo se encuentre en el mismo directorio que main y los headers
    generatematricesFromFile("tamanos.bin");

    return 0;
}

