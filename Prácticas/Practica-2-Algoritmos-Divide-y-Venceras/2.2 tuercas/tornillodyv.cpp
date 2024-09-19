// Ejemplo de la ordenacion por Quicksort sobre un vector de enteros

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void matchPairs(int *v,int *v2, int izq, int der);


int main(int argc, char *argv[]) {
	
	int *tornillos;
	int *tuercas;
	int n, i, argumento;
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
	
	// Pasamos por cada tamaÒo de caso
	for (argumento= 3; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		n= atoi(argv[argumento]);
		
		// Reservamos memoria para el vector
		tornillos= new int[n];
		tuercas= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (int i = 0; i < n; ++i) {
        		tornillos[i] = i + 1;
        		tuercas[i] = i + 1;
    		}
    		for (int i = 0; i < n; ++i) {
       			int randomIndex = rand()% n;
       			int randomIndex2 = rand()% n;
        		swap(tornillos[i], tornillos[randomIndex]);
        		swap(tuercas[i], tuercas[randomIndex2]);
    		}
		/*cout << "Tornillos y Tuercas Emparejados:" << endl;
    		for (int i = 0; i < n; i++) {
        		cout << "Tornillo " << tornillos[i] << " va con Tuerca " << tuercas[i] << endl;
   		}*/
		cerr << "Ejecutando Quicksort para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		matchPairs(tornillos, tuercas, 0, n - 1); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		 cout << "Tornillos y Tuercas Emparejados:" << endl;
    		/*for (int i = 0; i < n; i++) {
        	cout << "Tornillo " << tornillos[i] << " va con Tuerca " << tuercas[i] << endl;
    		}*/
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] tornillos;
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
int partition(int arr[], int low, int high, int pivot) {
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        } else if (arr[j] == pivot) {
            swap(arr[j], arr[high]);
            j--;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}
int partitionTuercas(int arr[], int low, int high, int pivot) {
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        } else if (arr[j] == pivot) {
            swap(arr[j], arr[high]);
            j--;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

void matchPairs(int tornillos[], int tuercas[], int low, int high) {
    if (low < high) {
        // Seleccionamos un tornillo como pivote
        int pivot = tornillos[high];

        // Utilizamos el tornillo pivote para particionar las tuercas
        int index = partitionTuercas(tuercas, low, high, pivot);

        // Utilizamos la tuerca pivote para particionar los tornillos
        partition(tornillos, low, high, tuercas[index]);

        // Recursivamente emparejamos los tornillos y las tuercas en cada lado del pivote
        matchPairs(tornillos, tuercas, low, index - 1);
        matchPairs(tornillos, tuercas, index + 1, high);
    }
}
