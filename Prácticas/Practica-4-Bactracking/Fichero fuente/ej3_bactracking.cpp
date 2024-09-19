#include <iostream>
#include <vector>

using namespace std;

const int n = 7;
int contador = 0;

enum tipoCasilla { libre, ocupada, prohibida };
tipoCasilla tablero[n][n] = {
    {prohibida, prohibida, ocupada, ocupada, ocupada, prohibida, prohibida},
    {prohibida, prohibida, ocupada, ocupada, ocupada, prohibida, prohibida},
    {ocupada, ocupada, ocupada, ocupada, ocupada, ocupada, ocupada},
    {ocupada, ocupada, ocupada, libre, ocupada, ocupada, ocupada},
    {ocupada, ocupada, ocupada, ocupada, ocupada, ocupada, ocupada},
    {prohibida, prohibida, ocupada, ocupada, ocupada, prohibida, prohibida},
    {prohibida, prohibida, ocupada, ocupada, ocupada, prohibida, prohibida}
};

void imprimirTablero() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            switch (tablero[i][j]) {
                case libre:
                    cout << " ";
                    break;
                case ocupada:
                    cout << "o";
                    break;
                case prohibida:
                    cout << "x";
                    break;
            }
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

bool fin(){
    int cont = 0, posx = 0, posy = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(tablero[i][j] == ocupada){
                cont++;
                posx = i;
                posy = j;
            }
        }
    }

    // Sólo hay una posición ocupada y es la del centro
    return (cont == 1 && posx == 3 && posy == 3); 
}

bool esMovimientoValido(int i, int j, int ni, int nj) {
    int mid_i = (i + ni) / 2;
    int mid_j = (j + nj) / 2;
    return (ni >= 0 && ni < n && nj >= 0 && nj < n && tablero[ni][nj] == libre && mid_i >= 0 && mid_i < n && mid_j >= 0 && mid_j < n && tablero[mid_i][mid_j] == ocupada);
}

void hacerMovimiento(int i, int j, int ni, int nj) {
    tablero[i][j] = libre;
    tablero[(i + ni) / 2][(j + nj) / 2] = libre;
    tablero[ni][nj] = ocupada;
}

void deshacerMovimiento(int i, int j, int ni, int nj) {
    tablero[i][j] = ocupada;
    tablero[(i + ni) / 2][(j + nj) / 2] = ocupada;
    tablero[ni][nj] = libre;
}

bool resolverSolitarioChino() {
    if (fin()) {
        return true;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tablero[i][j] == ocupada) {
                int movimientos[4][2] = {{0, -2}, {-2, 0}, {0, 2}, {2, 0}};
                for (int k = 0; k < 4; k++) {
                    int ni = i + movimientos[k][0]; // cordenada x de la casilla destino
                    int nj = j + movimientos[k][1]; // cordenada y de la casilla destino
                    if (esMovimientoValido(i, j, ni, nj)) {
                        hacerMovimiento(i, j, ni, nj);
                        if (resolverSolitarioChino()) {
                            contador++;
                            cout << "Movimiento nº"<< contador <<" : (" << i << ", " << j << ") a (" << ni << ", " << nj << ")" << endl;
                            return true;
                        }
                        deshacerMovimiento(i, j, ni, nj);
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    if (resolverSolitarioChino()) {
        cout << "Solución encontrada!" << endl;
        imprimirTablero();
    } else {
        cout << "No se encontró ninguna solución." << endl;
    }
    return 0;
}
