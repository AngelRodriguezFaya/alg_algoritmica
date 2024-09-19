#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
#include <vector>
using namespace std;

void shellSort(vector<int>& arr);

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
		
		cerr << "Ejecutando Shell Sort para tamaño caso: " << n << endl;
		
		t0 = std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecución del algoritmo
		shellSort(arr); // Ejecutamos el algoritmo para tamaño de caso n
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

void shellSort(vector<int>& arr) {
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
