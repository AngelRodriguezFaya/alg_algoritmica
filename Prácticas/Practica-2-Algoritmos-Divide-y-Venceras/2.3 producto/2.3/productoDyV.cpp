#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

bool es_producto_tres_consecutivos(int N, int a, int b, int c) {
    return a * b * c == N;
}

bool buscar_producto_tres_consecutivos(int N, int low, int high) {
    if (low > high) {
        return false;
    }

    int mid = low + (high - low) / 2;

    if (es_producto_tres_consecutivos(N, mid, mid + 1, mid + 2)) {
        return true;
    } else if (N < mid * (mid + 1) * (mid + 2)) {
        return buscar_producto_tres_consecutivos(N, low, mid - 1);
    } else {
        return buscar_producto_tres_consecutivos(N, mid + 1, high);
    }
}

int main(int argc, char *argv[]) {
    int argumento;
	
    if (argc <= 3) {
        cerr << "Uso: " << argv[0] << " <nombre_fichero_salida> <numero_producto>\n";
        return 1;
    }

    ofstream salida(argv[1]);
    if (!salida.is_open()) {
        cerr << "Error al abrir el archivo de salida.\n";
        return 1;
    }
    for (argumento = 2; argumento < argc; argumento++) {
	    int iteraciones = atoi(argv[argumento]);
	    auto t0 = chrono::high_resolution_clock::now();
	    for (int i = 1; i <= iteraciones; ++i) {
		
		bool resultado = buscar_producto_tres_consecutivos(i, 1, cbrt(i));
		

	    }
	    auto tf = chrono::high_resolution_clock::now();
		auto tejecucion = chrono::duration_cast<chrono::nanoseconds>(tf - t0).count();
		
		salida << iteraciones << " " << tejecucion << " " << /*(resultado ? "verdadero" : "falso") <<*/ "\n";
    }

    salida.close();
    cout << "Proceso completado. Los resultados se han guardado en '" << argv[1] << "'.\n";

    return 0;
}

