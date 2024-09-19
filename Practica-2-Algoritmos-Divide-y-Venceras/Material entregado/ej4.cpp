#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib> 
#include <vector>

using namespace std;

void quitar_duplicados ( vector<int>& v){
	for (int i=0; i < v.size(); i++){
		if(v[i]!=-1){
			for (int j=i+1; j < v.size(); j++){
			
				if (v[i] == v[j] ){
					v[j]=-1;
				}	
			}
		}

	}
	vector<int> aux;
	for(int i=0;i<v.size();i++){
		if(v[i]!=-1){
			aux.push_back(v[i]);
		}
	}
	v=aux;
}

	
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
		quitar_duplicados(v); // Ejecutamos el algoritmo para tamaÒo de caso tam
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