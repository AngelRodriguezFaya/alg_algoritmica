// Ejemplo de la ordenacion por Quicksort sobre un vector de enteros

#include <cstdlib> // Para usar srand y rand
#include <chrono>
#include <iostream>
#include <fstream> // Para usar ficheros
using namespace std;

void quicksort(int *v, int izq, int der);


int main(int argc, char *argv[]) {
	
	int *v;
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
		v= new int[n];
		
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%n;
		
		cerr << "Ejecutando Quicksort para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		quicksort(v,0,n-1); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
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
int partition(int v[], int izq, int der) {
    
  // Seleciono elemento al final como pivot
  int pivot = v[der];
  
  // puntero elemto mayo
  int i = (izq - 1);

  // comparo con el pivot
  for (int j = izq; j < der; j++) {
    if (v[j] <= pivot) {
        
      // Si se encuentra un elemento menor que piv intercambio con el mayor apuntado por i
      i++;
      
      swap(&v[i], &v[j]);
    }
  }
  
  // swap pivot con el mayor en i
  swap(&v[i + 1], &v[der]);
  
  // devuelvo el punto de particion
  return (i + 1);
}
void quicksort(int v[], int izq, int der) {
	if (izq < der) {
      
    // encontrar el pivote que tenga los elementos menores a la izq y los mayores a la der
    int pi = partition(v, izq, der);

    // llamada recursiva hacia la izq
    quicksort(v, izq, pi - 1);

    // llamada recursiva hacia la der
    quicksort(v, pi + 1, der);
  }
}



