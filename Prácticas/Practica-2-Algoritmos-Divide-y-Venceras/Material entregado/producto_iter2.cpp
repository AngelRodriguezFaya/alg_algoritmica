#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

using namespace std;

bool producto_tres_consecutivos(int N, int iteraciones) {
    int raiz_cubica = ceil(pow(N, 1.0/3.0));
    for (int i = 1; i <= raiz_cubica; ++i) {
        int producto = i * (i + 1) * (i + 2);
        if (producto == N) {
            return true;
        }
        if(producto >N){
        	return false;
        }
    }
    return false;
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
		
		bool resultado = producto_tres_consecutivos(i, iteraciones);
		/*if(resultado){
		cout << i << " " <<  " " <<  "verdadero"  << "\n";
		}*/
		

	    }
	    auto tf = chrono::high_resolution_clock::now();
		auto tejecucion = chrono::duration_cast<chrono::nanoseconds>(tf - t0).count();
		
		salida << iteraciones << " " << tejecucion << " " << /*(resultado ? "verdadero" : "falso") <<*/ "\n";
    }

    salida.close();
    cout << "Proceso completado. Los resultados se han guardado en '" << argv[1] << "'.\n";

    return 0;
}

