#include <vector>
#include <iostream>
using namespace std;

// https://github.com/psakoglou/Strassen-algorithm-Simulation-and-asymptotic-Efficiency-cPP

// Función para crear una matriz de n x n
vector<vector<int>> crearMatriz(int n) {
    return vector<vector<int>>(n, vector<int>(n, 0));
}

// Función para sumar dos matrices
vector<vector<int>> sumarMatrices(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    vector<vector<int>> c = crearMatriz(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    return c;
}

// Función para restar dos matrices
vector<vector<int>> restarMatrices(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    vector<vector<int>> c = crearMatriz(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    return c;
}


// Función de Strassen para multiplicar matrices
vector<vector<int>> strassen(const vector<vector<int>>& a, const vector<vector<int>>& b) {
    int n = a.size();
    if (n == 1) {
        vector<vector<int>> c = crearMatriz(1);
        c[0][0] = a[0][0] * b[0][0];
        return c;
    }

    int k = n / 2;
    // Crear las sub-matrices de tamano n/2
    vector<vector<int>> a11 = crearMatriz(k), a12 = crearMatriz(k);
    vector<vector<int>> a21 = crearMatriz(k), a22 = crearMatriz(k);
    vector<vector<int>> b11 = crearMatriz(k), b12 = crearMatriz(k);
    vector<vector<int>> b21 = crearMatriz(k), b22 = crearMatriz(k);

    // Poblar las matrices segun corresponda
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][k + j];
            a21[i][j] = a[k + i][j];
            a22[i][j] = a[k + i][k + j];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][k + j];
            b21[i][j] = b[k + i][j];
            b22[i][j] = b[k + i][k + j];
        }
    }

    // Calcular las matrices S
    vector<vector<int>> S1 = restarMatrices(b12, b22);
    vector<vector<int>> S2 = sumarMatrices(a11, a12);
    vector<vector<int>> S3 = sumarMatrices(a21, a22);
    vector<vector<int>> S4 = restarMatrices(b21, b11);
    vector<vector<int>> S5 = sumarMatrices(a11, a22);
    vector<vector<int>> S6 = sumarMatrices(b11, b22);
    vector<vector<int>> S7 = restarMatrices(a12, a22);
    vector<vector<int>> S8 = sumarMatrices(b21, b22);
    vector<vector<int>> S9 = restarMatrices(a11, a21);
    vector<vector<int>> S10 = sumarMatrices(b11, b12);

    // Calcular las matrices P
    vector<vector<int>> P1 = strassen(a11, S1);
    vector<vector<int>> P2 = strassen(S2, b22);
    vector<vector<int>> P3 = strassen(S3, b11);
    vector<vector<int>> P4 = strassen(a22, S4);
    vector<vector<int>> P5 = strassen(S5, S6);
    vector<vector<int>> P6 = strassen(S7, S8);
    vector<vector<int>> P7 = strassen(S9, S10);

    // Calcular las sub-matrices c
    // C11 = P5 + P4 - P2 + P6
    // C12 = P1 + P2
    // C21 = P3 + P4
    // C22 = P1 + P5 - P3 - P7
    vector<vector<int>> c11 = restarMatrices(sumarMatrices(sumarMatrices(P5, P4), P6), P2); 
    vector<vector<int>> c12 = sumarMatrices(P1, P2);
    vector<vector<int>> c21 = sumarMatrices(P3, P4);
    vector<vector<int>> c22 = restarMatrices(restarMatrices(sumarMatrices(P5, P1), P3), P7);

    // Crear la matriz resultado c
    vector<vector<int>> c = crearMatriz(n);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            c[i][j] = c11[i][j];
            c[i][j + k] = c12[i][j];
            c[k + i][j] = c21[i][j];
            c[k + i][k + j] = c22[i][j];
        }
    }
    return c;
}

