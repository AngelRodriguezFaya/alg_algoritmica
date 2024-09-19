
/**
 * @file: ej4_p5_algoritmica.cpp
 * 
 * @brief: Solución al problema 4 de la práctica 5 de algorítmica.
 * 
 * Autores: 
 * - Miguel Martinez Azor
 * - Ángel Rodríguez Faya
 * - Alejandro Botaro Crespo
 * - Alberto Parejo Bellido
 * - Alejandro Ocaña Sánchez 
 * 
 * ALGORÍTMICA CURSO 2023/2024
 * 2o de Ingeniería Informática
 * Universidad de Granada
 * 
 * Compilar con:
 * g++ -std=c++11 -o ej4_p5_algoritmica ej4_p5_algoritmica.cpp
 * 
 * Ejecutar con:
 * ./ej4_p5_algoritmica
*/


#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> // Para std::min

using namespace std;

// Función para encontrar el mínimo costo de ascenso
vector<vector<int>> encontrar_minimo_costo(vector<vector<int>>& montana, int m, int n) {
    // Inicializar la matriz de dificultad mínima con infinito
    vector<vector<int>> T(m, vector<int>(n, INT_MAX));
    
    // Caso base: la última fila es igual a los costos de la última fila de la montaña
    for (int j = 0; j < n; ++j) {
        T[m-1][j] = montana[m-1][j];
    }
    
    // Rellenar la matriz T con los valores mínimos de dificultad acumulada
    for (int i = m-2; i >= 0; --i) {
        for (int j = 0; j < n; ++j) {

            // Si estamos en la primera columna, no podemos ir a la izquierda
            int izquierda = (j-1 >= 0) ? T[i+1][j-1] : INT_MAX;
            
            int arriba = T[i+1][j];
            
            // Si estamos en la última columna, no podemos ir a la derecha
            int derecha = (j+1 < n) ? T[i+1][j+1] : INT_MAX;

            T[i][j] = montana[i][j] + min({izquierda, arriba, derecha});
        }
    }
    
    return T;
}

// Función para recuperar el camino con el mínimo costo
vector<int> recuperar_camino(const vector<vector<int>>& T, int pos_min_dificultad) {
    int m = T.size();
    int n = T[0].size();
    vector<int> camino(m);
    int j = pos_min_dificultad;
    
    camino[0] = j;
    
    for (int i = 0; i < m-1; ++i) {
        int izquierda = (j-1 >= 0) ? T[i+1][j-1] : INT_MAX;
        int arriba = T[i+1][j];
        int derecha = (j+1 < n) ? T[i+1][j+1] : INT_MAX;
        
        if (izquierda <= arriba && izquierda <= derecha) {
            j -= 1;
        } else if (derecha <= arriba && derecha <= izquierda) {
            j += 1;
        }
        
        camino[i+1] = j;
    }
    
    return camino;
}

int main() {
    vector<vector<int>> montana = {
        {2, 8, 9, 5, 8},
        {4, 4, 6, 2, 3},
        {5, 7, 5, 6, 1},
        {3, 2, 5, 4, 8}
    };

    int m = 4, n = 5;

    vector<vector<int>> T = encontrar_minimo_costo(montana, m, n);

    // Encontrar el costo mínimo en la primera fila
    int min_dificultad = INT_MAX;
    int pos_min_dificultad = -1;
    for (int j = 0; j < T[0].size(); ++j) {
        if (T[0][j] < min_dificultad) {
            min_dificultad = T[0][j];
            pos_min_dificultad = j;
        }
    }

    vector<int> camino = recuperar_camino(T, pos_min_dificultad);

    cout << "Dificultad mínima: " << min_dificultad << endl;
    cout << "Camino: ";
    for (int i = camino.size()-1; i >= 0; --i) {
        cout << camino[i] << " ";
    }
    cout << endl;

    return 0;
}
