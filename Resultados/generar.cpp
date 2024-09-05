#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>
using namespace std;

void generarSemi(vector<int>& vec, int tamano) {
    srand(static_cast<unsigned int>(time(nullptr))); // Semilla para números aleatorios
    vec.resize(tamano); // Ajusta el tamaño del vector
    // Genera números aleatorios para la primera mitad del vector
    generate(vec.begin(), vec.begin() + tamano / 2, rand);
    // Genera una secuencia ordenada para la segunda mitad del vector
    iota(vec.begin() + tamano / 2, vec.end(), 1);
}

// Función para generar números aleatorios
void generarAleatorio(vector<int>& vec, int tamano) {
    srand(static_cast<unsigned int>(time(nullptr)));
    vec.resize(tamano);
    generate(vec.begin(), vec.end(), rand);
}

// Función para generar números ordenados
void generarOrdenado(vector<int>& vec, int tamano) {
    vec.resize(tamano);
    iota(vec.begin(), vec.end(), 1);
}

// Función para generar números invertidos
void generarInvertido(vector<int>& vec, int tamano) {
    vec.resize(tamano);
    iota(vec.begin(), vec.end(), 1);
    reverse(vec.begin(), vec.end());
}

// Función para generar números iguales
void generarIguales(vector<int>& vec, int tamano, int valor) {
    vec.resize(tamano);
    fill(vec.begin(), vec.end(), valor);
}

// Función para guardar los datos en un archivo binario
void guardarEnBinario(const vector<int>& vec, ofstream& archivo) {
    // Guardar el tamaño del vector como un entero
    size_t tamano = vec.size();
    archivo.write(reinterpret_cast<const char*>(&tamano), sizeof(tamano));
    
    // Guardar los datos del vector
    archivo.write(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(int));
}

// Función para generar y guardar datos
void generarYGuardarDatos(const vector<int>& tamaños) {
    vector<int> vec;

    // Abrir todos los archivos para escritura en binario
    ofstream archivoAleatorio("aleatorio.bin", ios::binary);
    ofstream archivoOrdenado("ordenado.bin", ios::binary);
    ofstream archivoInvertido("invertido.bin", ios::binary);
    ofstream archivoIguales("iguales.bin", ios::binary);
    ofstream archivoSemi("semiordenado.bin", ios::binary);

    if (!archivoAleatorio || !archivoOrdenado || !archivoInvertido || !archivoIguales || !archivoSemi) {
        cerr << "No se pudo abrir uno o más archivos para escritura." << endl;
        return;
    }

    for (int tamano : tamaños) {
        // Generar y guardar datos semi ordenados
        generarSemi(vec, tamano);
        guardarEnBinario(vec, archivoSemi);
        // Generar y guardar datos aleatorios
        generarAleatorio(vec, tamano);
        guardarEnBinario(vec, archivoAleatorio);

        // Generar y guardar datos ordenados
        generarOrdenado(vec, tamano);
        guardarEnBinario(vec, archivoOrdenado);

        // Generar y guardar datos invertidos
        generarInvertido(vec, tamano);
        guardarEnBinario(vec, archivoInvertido);

        // Generar y guardar datos iguales
        generarIguales(vec, tamano, 7);
        guardarEnBinario(vec, archivoIguales);
    }

    // Cerrar todos los archivos
    archivoSemi.close();
    archivoAleatorio.close();
    archivoOrdenado.close();
    archivoInvertido.close();
    archivoIguales.close();
}

int main() {
    vector<int> tamaños = {1000, 10000, 30000, 100000, 500000, 1000000, 3000000};

    generarYGuardarDatos(tamaños);
    cout << "Generados!"<<endl;
    return 0;
}
