#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <list>
#include <climits>

using namespace std;

bool casilla_valida(const vector<vector<bool>>& mapa, const vector<vector<bool>>& visitado, int x, int y) {
    int n = mapa.size();
    return (x >= 0 && x < n && y >= 0 && y < n && mapa[x][y] && !visitado[x][y]);
}

pair<bool, list<pair<int, int>>> buscarSalidaBranchAndBound(vector<vector<bool>>& mapa) {
    int n = mapa.size();
    vector<pair<int, int>> movimientos = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<bool>> visitado(n, vector<bool>(n, false));
    priority_queue<tuple<int, int, int, list<pair<int, int>>>> cola;  // (costo, x, y, camino)
    cola.push(make_tuple(0, 0, 0, list<pair<int, int>>()));
    
    int mejor_solucion = INT_MAX;
    list<pair<int, int>> mejor_camino;

    while (!cola.empty()) {
        auto [costo, x, y, camino] = cola.top();
        cola.pop();

        if (costo >= mejor_solucion) {
            continue;  // Poda
        }

        visitado[x][y] = true;
        camino.push_back(make_pair(x, y));

        if (x == n - 1 && y == n - 1) {
            if (costo < mejor_solucion) {
                mejor_solucion = costo;
                mejor_camino = camino;
            }
            continue;
        }

        for (const auto& movimiento : movimientos) {
            int nx = x + movimiento.first;
            int ny = y + movimiento.second;

            if (casilla_valida(mapa, visitado, nx, ny)) {
                visitado[nx][ny] = true;
                cola.push(make_tuple(costo + 1, nx, ny, camino));
                visitado[nx][ny] = false;
            }
        }

        visitado[x][y] = false;
    }

    if (mejor_solucion == INT_MAX) {
        return {false, list<pair<int, int>>()};  // No se encontró camino
    } else {
        return {true, mejor_camino};
    }
}

int main(int argc, char **argv) {
    vector<vector<bool>> mapa;
    vector<bool> auxi;
    int n;

    if (argc != 2) {
        cerr << "Formato incorrecto, se escribe ./Bound tamaño_en_int_del_laberinto_nXn(el mapa esta preparado para un 4x4 :) )" << endl;
        exit(1);
    }
    n = atoi(argv[1]);

    auxi.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if ((i != 0 or j != 3) and (i != 1 or j != 2) and (i != 2 or j != 0) and (i != 3 or j != 0))
                auxi[j] = true;
            else
                auxi[j] = false;
        }
        mapa.push_back(auxi);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mapa[i][j])
                cout << "T   ";
            else
                cout << "F   ";
        }
        cout << endl;
    }

    auto r = buscarSalidaBranchAndBound(mapa);

    pair<int, int> aux;
    if (r.first) {
        for (const auto& p : r.second) {
            cout << "( " << p.first << " , " << p.second << " ), ";
        }
    }
    cout << endl;

    return 0;
}

