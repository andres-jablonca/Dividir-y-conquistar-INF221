#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

// Función para particionar vector
int particion(vector<int> &vec, int low, int high) {
    // Elegir el último elemento como el pivote
    int pivote = vec[high];

    // i será el índice del menor elemento
    int i = (low - 1);

    // Recorrer subvector desde low hasta high - 1
    for (int j = low; j <= high - 1; j++) {
        // Si el elemento actual es menor o igual al pivote, se incrementa i y se swapea el elemento i con el elemento j
        if (vec[j] <= pivote) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Colocar el pivote en su posición final (entre los menores y mayores)
    swap(vec[i + 1], vec[high]);

    // Devolver el índice donde el pivote quedó finalmente
    return (i + 1);
}

// Función de QuickSort
void quickSort(vector<int> &vec, int low, int high) {
    // Solo si hay mas de un elemento
    if (low < high) {
        // Obtener el índice de partición
        int part = particion(vec, low, high);

        // Ordenar los elementos a la izquierda y a la derecha de la particion
        quickSort(vec, low, part - 1);
        quickSort(vec, part + 1, high);
    }
}
