#include "quickSort.hpp"
#include "mergeSort.hpp"
#include "selectionSort.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm> 
#include <chrono>

using namespace std;
using namespace std::chrono;

void leer(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    while (archivo.peek() != EOF) {
        // Leer el tamaño del vector
        size_t tamano;
        archivo.read(reinterpret_cast<char*>(&tamano), sizeof(tamano));

        // Verificar si el tamaño leído es válido
        if (tamano == 0) {
            cerr << "Tamaño del vector no válido" << endl;
            continue;
        }

        // Leer los datos del vector
        vector<int> vec(tamano);
        archivo.read(reinterpret_cast<char*>(vec.data()), tamano * sizeof(int));

        // Asegurarse de que los datos se leyeron correctamente
        if (archivo.gcount() != tamano * sizeof(int)) {
            cerr << "Error al leer los datos del archivo" << endl;
            continue;
        }

        vector<int> selec = vec, merg = vec, quick = vec, estandar = vec;

        cout << "Para tamaño " << tamano << ":\n\n";

        // SELECTION SORT
        if (tamano <= 100000){
            auto start = high_resolution_clock::now();
            selectionSort(selec);
            auto end = high_resolution_clock::now();
            duration<double> tiempo = end - start;
            cout << "SELECTION SORT: " << tiempo.count() << " segundos" << endl;
        } else {
            cout << "SELECTION SORT: Ya tarda demasiado como para medir" << endl;
        }

        // MERGE SORT
        auto start = high_resolution_clock::now();
        merg = mergeSort(merg);
        auto end = high_resolution_clock::now();
        duration<double> tiempo = end - start;
        cout << "MERGE SORT: " << tiempo.count() << " segundos" << endl;

        // QUICK SORT
        if ((nombreArchivo == "ordenado.bin" || nombreArchivo == "invertido.bin" || nombreArchivo == "iguales.bin" || nombreArchivo == "semiordenado.bin") && tamano >= 100000){
            cout << "QUICK SORT: No soporta" << endl;
        } else {
            start = high_resolution_clock::now();
            quickSort(quick, 0, quick.size() - 1);
            end = high_resolution_clock::now();
            tiempo = end - start;
            cout << "QUICK SORT: " << tiempo.count() << " segundos" << endl;
        }

        // SORT ESTÁNDAR
        start = high_resolution_clock::now();
        sort(estandar.begin(), estandar.end());
        end = high_resolution_clock::now();
        tiempo = end - start;
        cout << "SORT ESTANDAR: " << tiempo.count() << " segundos" << endl;

        cout << endl;
    }

    archivo.close();
}


int main() {
    
    // Es necesario que todos los archivos bin se encuentren en el mismo directorio que main y los headers

    cout << "\nVectores desordenados:\n";
    leer("aleatorio.bin");

    cout << "\nVectores ordenados:\n";
    leer("ordenado.bin");

    cout << "\nVectores semiordenados:\n";
    leer("semiordenado.bin");

    cout << "\nVectores ordenados inversamente:\n";
    leer("invertido.bin");

    cout << "\nVectores con todos sus elementos iguales:\n";
    leer("iguales.bin");
    
    return 0;
}
