#include <cstdlib>
#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // Para la función swap
#include <ctime> // Para utilizar time

using namespace std;

void emparejarTornillosYTuercas(vector<int> &tornillos, vector<int> &tuercas, int n);

int main(int argc, char *argv[]) {
    int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf;
    unsigned long int semilla;
    ofstream fsalida;

    if (argc <= 3) {
        cerr << "\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr << argv[0] << " NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
        return 0;
    }

    // Abrimos fichero de salida
    fsalida.open(argv[1]);
    if (!fsalida.is_open()) {
        cerr << "Error: No se pudo abrir fichero para escritura " << argv[1] << "\n\n";
        return 0;
    }

    // Inicializamos generador de números aleatorios
    semilla = atoi(argv[2]);
    srand(semilla);

    // Pasamos por cada tamaño de caso
    for (argumento = 3; argumento < argc; argumento++) {

        // Cogemos el tamaño del caso
        n = atoi(argv[argumento]);

        vector<int> tornillos(n);
        vector<int> tuercas(n);

        // Generamos vectores aleatorios de prueba sin repeticiones e iguales
        for (int i = 0; i < n; i++) {
            tornillos[i] = i; // Colocamos cada elemento en su posición original
            tuercas[i] = i;
        }

        // Barajamos los vectores para que las posiciones sean diferentes
        random_shuffle(tornillos.begin(), tornillos.end());
        random_shuffle(tuercas.begin(), tuercas.end());
        
        
        /*
         cout << "Tornillos antes de emparejar: ";
        for (int i = 0; i < n; i++) {
            cout << tornillos[i] << " ";
        }
        cout << endl;

        cout << "Tuercas antes de emparejar:   ";
        for (int i = 0; i < n; i++) {
            cout << tuercas[i] << " ";
        }
        cout << endl;

        cerr << "Emparejando tornillos y tuercas para tamaño de caso: " << n << endl;*/

        t0 = std::chrono::high_resolution_clock::now();
        emparejarTornillosYTuercas(tornillos, tuercas, n);
        tf = std::chrono::high_resolution_clock::now();

        unsigned long tejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();

        cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tamaño de caso " << n << endl;

        // Guardamos tamaño de caso y tiempo de ejecución a fichero de salida
        fsalida << n << " " << tejecucion << "\n";

        // Mostramos los vectores después del emparejamiento Descomentar para ver funcionamiento
        
        
       /* cout << "Tornillos después de emparejar: ";
        for (int i = 0; i < n; i++) {
            cout << tornillos[i] << " ";
        }
        cout << endl;

        cout << "Tuercas después de emparejar:   ";
        for (int i = 0; i < n; i++) {
            cout << tuercas[i] << " ";
        }
        cout << endl;
        cout << "---------------------------------------------------------";
        cout << endl;
*/    }

    // Cerramos fichero de salida
    fsalida.close();

    return 0;
}

void emparejarTornillosYTuercas(vector<int> &tornillos, vector<int> &tuercas, int n) {

    for (int i = 0; i < n; i++) {	//Recorrer vector tornillos
        for (int j = 0; j < n; j++) {	//recorrer vector tuercas
            if (tornillos[i] == tuercas[j]) {	//Si el componenete del vector tornillos y del vector tuercas es igual
                swap(tuercas[i], tuercas[j]);	//intercambiar posiciones
                break; 			// Cuando se ha encontrado la pareja que coincide se 
            }
        }
    }
}

