#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
using namespace std;

void countingSort(vector<int>& arr);

int main(int argc, char *argv[]) {
	
	int n, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc <= 3) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida Semilla tamCaso1 tamCaso2 ... tamCasoN\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Inicializamos generador de no. aleatorios
	semilla= atoi(argv[2]);
	srand(semilla);
	
	// Pasamos por cada tamaño de caso
	for (argumento = 3; argumento < argc; argumento++) {
		
		// Cogemos el tamaño del caso
		n = atoi(argv[argumento]);
		
		// Creamos un vector de tamaño n
		vector<int> arr(n);
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int i = 0; i < n; i++)
			arr[i] = rand() % n;
		
		cerr << "Ejecutando Counting Sort para tamaño caso: " << n << endl;
		
		t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		countingSort(arr); // Ejecutamos el algoritmo para tamaño de caso n
		tf = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecución del algoritmo
		
		unsigned long tejecucion = std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tamaño caso "<< n << endl;
		
		// Guardamos tamaño de caso y t_ejecucion a fichero de salida
		fsalida << n << " " << tejecucion << "\n";
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}

void countingSort(vector<int>& arr) {
    // Encontrar el valor máximo en el vector
    int max_val = arr[0];
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Crear un vector de conteo y inicializarlo con ceros
    vector<int> count(max_val + 1, 0);

    // Contar la frecuencia de cada elemento en el vector original
    for (int i = 0; i < arr.size(); ++i) {
        count[arr[i]]++;
    }

    // Actualizar el vector de conteo para almacenar la posición real de cada elemento
    for (int i = 1; i <= max_val; ++i) {
        count[i] += count[i - 1];
    }

    // Crear un vector de salida del mismo tamaño que el vector original
    vector<int> output(arr.size());

    // Ordenar los elementos en el vector de salida usando el vector de conteo
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copiar los elementos ordenados al vector original
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = output[i];
    }
}

