// Ejemplo de la ordenacion por Quicksort sobre un vector de enteros

#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib> 
#include <vector>// Para usar ficheros
using namespace std;

void duplicadodyv(vector<int>& v);


int main(int argc, char *argv[]) {
	
	vector <int> v;
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
		
		v.clear();
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v.push_back( rand()%4);
		// Imprime vector
		cout<<"tamaño: "<<v.size()<<endl;
		// cout << "Vector: [ ";
		// for (int i=0; i<v.size(); i++){
		// 	cout << v[i] << " ";
		// }
		// cout << "]" << endl;

		cerr << "Ejecutando algoritmo  para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		duplicadodyv(v); // Ejecutamos el algoritmo para tamaÒo de caso tam
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
	// Imprime vector sin duplicados
	cout<<"tamaño: "<<v.size()<<endl;
	cout << "Vector sin duplicados: [ ";
	for (int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout << "]" << endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}
void ordenar_merge(vector<int>& v, int inicio, int fin) {
    if (inicio < fin) {
     
        int mitad = inicio + (fin - inicio) / 2;
        
        
        ordenar_merge(v, inicio, mitad);
        ordenar_merge(v, mitad + 1, fin);
        
        combinar_subvectores(v, inicio, mitad, fin);
    }
}
void combinar_subvectores(vector<int>& v, int inicio, int mitad, int fin) {
    // Tamaño de los subvectores
    int n1 = mitad - inicio + 1;
    int n2 = fin - mitad;
    
    // Vectores temporales para almacenar los subvectores
    vector<int> der, izq;
    

    for (int i = 0; i < n1; i++){
        izq.push_back( v[inicio + i]);
    }
    for (int j = 0; j < n2; j++){
        der.push_back (v[mitad + 1 + j]);
    }
    
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (izq[i] <= der[j]) {
            v[k] = izq[i];
            i++;
        } else {
            v[k] = der[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = izq[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = der[j];
        j++;
        k++;
    }
}
void duplicadodyv(vector<int>& v) {
    int n = v.size();
    ordenar_merge(v, 0, n - 1);
    auto ini=v.begin();
    auto siguiente=ini+1;
    while(siguiente!=v.end()){
        if(*ini==*siguiente){
            siguiente=v.erase(siguiente);
        }else{
            ini=siguiente;
            ++siguiente;
        }

    }   
}  

