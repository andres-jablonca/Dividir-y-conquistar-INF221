#include <iostream>
#include <vector>
using namespace std;

// Funcion para imprimir matriz
void mostrar(int n, vector<vector<int>> m){
    for (int i = 0; i< n; i++){
        for (int j = 0; j < n; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

// Funcion que realiza la multiplicacion tradicional de matrices mediante triple for anidado
void mult(int n, const vector<vector<int>>& a, const vector<vector<int>>& b){
    vector<vector<int>> result(n, vector<int>(n));
    int sum;
    for (int i=0; i < n; i++){
        for (int j = 0; j < n; j++){
            sum = 0;
            for (int k = 0; k < n; k++){
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    //mostrar(n, result);
}

// Funcion que realiza la multiplicacion de matrices mediante triple for anidado pero teniendo en cuenta que la segunda matriz esta traspuesta
void mult_traspuesta(int n, const vector<vector<int>>& a, const vector<vector<int>>& bt){
    vector<vector<int>> result(n, vector<int>(n));
    int sum;
    for (int i=0; i < n; i++){
        for (int j = 0; j < n; j++){
            sum = 0;
            for (int k = 0; k < n; k++){
                sum += a[i][k] * bt[j][k];
            }
            result[i][j] = sum;
        }
    }
    //mostrar(n, result);
}

// Funcion que traspone una matriz
void trasponer(int n, vector<vector<int>>& m){
    vector<vector<int>> nueva(n, vector<int>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            nueva[i][j] = m[j][i];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            m[i][j] = nueva [i][j];
        }
    }
}
