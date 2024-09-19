#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

void particion(vector<int> &arr, int low, int high, int pivot, int &left, int &right);
void emparejar(vector<int> &tornillos, vector<int> &tuercas, int c, int f);

int main() {
    int n;
    cout << "Ingrese el tamaño de los vectores de tornillos y tuercas: ";
    cin >> n;

    // Inicializamos los vectores de tornillos y tuercas
    vector<int> tornillos(n);
    vector<int> tuercas(n);

    // Generamos vectores aleatorios de prueba sin repeticiones
    for (int i = 0; i < n; i++) {
        tornillos[i] = i; // Colocamos cada elemento en su posición original
        tuercas[i] = i;
    }

    // Barajamos los vectores para que las posiciones sean diferentes
    random_shuffle(tornillos.begin(), tornillos.end());
    random_shuffle(tuercas.begin(), tuercas.end());

    cout << "Tornillos antes de emparejar: ";
    for (int i = 0; i < n; i++) {
        cout << tornillos[i] << " ";
    }
    cout << endl;

    cout << "Tuercas antes de emparejar: ";
    for (int i = 0; i < n; i++) {
        cout << tuercas[i] << " ";
    }
    cout << endl;

    // Emparejamos los tornillos y las tuercas
    emparejar(tornillos, tuercas, 0, n - 1);

    cout << "Tornillos después de emparejar: ";
    for (int i = 0; i < n; i++) {
        cout << tornillos[i] << " ";
    }
    cout << endl;

    cout << "Tuercas después de emparejar: ";
    for (int i = 0; i < n; i++) {
        cout << tuercas[i] << " ";
    }
    cout << endl;

    return 0;
}

void particion(vector<int> &arr, int low, int high, int pivot, int &left, int &right) {
    left = low;
    right = high;
    while (left <= right) {
        while (arr[left] < pivot)
            left++;
        while (arr[right] > pivot)
            right--;
        if (left <= right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }
}

void emparejar(vector<int> &tornillos, vector<int> &tuercas, int c, int f) {
    if (c < f) {
        int i, j, k, l;
        particion(tuercas, c, f, tuercas[c], i, j); // Pivote de tuercas
        particion(tornillos, c, f, tuercas[i], k, l); // Pivote de tuercas
        emparejar(tornillos, tuercas, c, i - 1);
        emparejar(tornillos, tuercas, j + 1, f);
    }
}

