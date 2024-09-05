#include <iostream>
#include <vector>
using namespace std;

// Funcion de Selection Sort
void selectionSort(vector<int>& vec){
    // Recorrer el vector
    int n = vec.size();
    for (int i = 0; i < n - 1; i++){
        // Se almacena elemento en posicion i como el "menor"
        int min = i;
        // Buscar el verdader menor elemento
        for (int j = i + 1; j < n; j++) { // Se recorre desde i hasta n
            if (vec[j] < vec[min]) // Comparar elemento en la posicion j con el "menor" elemento
                min = j; // Actualizar la posicion del menor elemento
        }
        // Intercambiar el menor elemento encontrado con el elemento i
        if (min != i) swap(vec[min], vec[i]); 
    }
}