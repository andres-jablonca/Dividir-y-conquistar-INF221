#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>  
#include <ctime> 
#include <numeric>
#include <chrono>
using namespace std;

// Funcion merge que recibe dos vectores ordenados y los mezcla en un vector resultante
vector<int> merge(vector<int> izq, vector<int> der) {
    vector<int> nuevo;
    int i = 0, j = 0;
    
    // Recorrer IZQ y DER a la vez e ir agregando el menor entre ellos al vector resultante
    while (i < izq.size() && j < der.size()) {
        if (izq[i] > der[j]) {
            nuevo.push_back(der[j]);
            j++;
        } else {
            nuevo.push_back(izq[i]);
            i++;
        }
    }
    // En caso de haber recorrido DER, agrega todos los elementos restantes de IZQ
    while (i < izq.size()) {
        nuevo.push_back(izq[i]);
        i++;
    }
    // En caso de haber recorrido IZQ, agrega todos los elementos restantes de DER
    while (j < der.size()) {
        nuevo.push_back(der[j]);
        j++;
    }

    return nuevo;
}

// Funcion de mergeSort
vector<int> mergeSort(vector<int> v) {
    // Si el vector es de largo 1 o menor, lo retorna
    if (v.size() <= 1) return v;
    
    // Dividir el vector en dos mitades
    int mid = v.size() / 2;
    vector<int> izq(v.begin(), v.begin() + mid);
    vector<int> der(v.begin() + mid, v.end());
    
    // Llamadas recursivas para cada mitad
    izq = mergeSort(izq);
    der = mergeSort(der);

    // Retornar cada sub-vector ya mezclado y ordenado
    return merge(izq, der);
}
