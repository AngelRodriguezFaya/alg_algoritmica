#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <list>
#include <limits>

using namespace std;

// Constante para representar infinito
const int INF = numeric_limits<int>::max();

// Algoritmo de Floyd con tiempos de espera en escalas
void floydAviones(int n, vector<vector<int>>& T, vector<int>& E, vector<vector<int>>& dist, vector<vector<int>>& sig) {
    // Inicializar la matriz de distancias y la matriz de recuperación
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
                sig[i][j] = -1;
            } else if (T[i][j] != 0) {
                dist[i][j] = T[i][j];
                sig[i][j] = j;
            } else {
                dist[i][j] = INF;
                sig[i][j] = -1;
            }
        }
    }

    // Floyd-Warshall con tiempos de espera en escalas
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j] + E[k]) {
                    dist[i][j] = dist[i][k] + dist[k][j] + E[k];
                    sig[i][j] = sig[i][k];
                }
            }
        }
    }
}

// Algoritmo de recuperación de la ruta óptima
vector<int> recupera(vector<vector<int>>& sig, int i, int j) {
    vector<int> camino;
    if (sig[i][j] == -1) {
        return camino; // No hay ruta disponible
    }
    int current = i;
    while (current != j) {
        camino.push_back(current);
        current = sig[current][j];
    }
    camino.push_back(j);
    return camino;
}

int main() {
    // Número de ciudades
    int n = 4;

    // Matriz de tiempos de vuelo directos (0 si no hay vuelo directo)
    vector<vector<int>> T = {
        {0, 2, 1, 3},
        {7, 0, 9, 2},
        {2, 2, 0, 1},
        {3, 4, 8, 0}
    };

    // Tiempo de espera en cada ciudad (escalas)
    vector<int> E = {1, 1, 1, 1};

    // Matriz de distancias y matriz de recuperación
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> sig(n, vector<int>(n, -1));

    // Ejecutar el algoritmo de Floyd-Warshall
    floydAviones(n, T, E, dist, sig);

    // Imprimir la matriz de tiempos mínimos entre todas las ciudades
    cout << "La matriz de tiempos mínimos entre todas las ciudades es:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }

    // Recuperar y mostrar la ruta óptima entre dos ciudades específicas
    int ciudadInicio = 0;
    int ciudadDestino = 2;
    vector<int> ruta = recupera(sig, ciudadInicio, ciudadDestino);

    if (ruta.empty()) {
        cout << "No hay ruta disponible de " << ciudadInicio << " a " << ciudadDestino << endl;
    } else {
        cout << "La ruta óptima de " << ciudadInicio << " a " << ciudadDestino << " es: ";
        for (int ciudad : ruta) {
            cout << ciudad << " ";
        }
        cout << endl;
    }

    return 0;
}

