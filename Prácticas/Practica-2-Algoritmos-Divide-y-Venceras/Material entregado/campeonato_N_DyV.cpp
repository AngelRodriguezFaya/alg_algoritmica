#include <iostream>
#include <vector>
#include <fstream> // Para usar ficheros
#include <chrono>

using namespace std;

struct Partido {
    int jugador1;
    int jugador2;
};

void organizaCampeonato(unsigned int n) {
    vector<vector<Partido>> calendario(n-1);

    unsigned int i, j;

    for (i = 0; i < n; ++i) {
        for (j = i + 1; j < n; ++j) {
            Partido partido{i, j};
            calendario[j- i-1].push_back(partido);
        }
    }

    
    // // Imprimir el calendario
    // for (int i = 0; i < n - 1; ++i) {
    //     cout << "Dia " << i + 1 << ":\n";
    //     for (const auto& partido : calendario[i]) {
    //         cout << "Partido entre el jugador " << partido.jugador1 + 1
    //                   << " y el jugador " << partido.jugador2 + 1 << '\n';
    //     }
    // } 
    
}

int main(int argc, char *argv[]) {
	
	unsigned int n, k, argumento;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	ofstream fsalida;
	
	if (argc <= 2) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida tamanio_k_1 tamanio_k_2 ... tamanio_k_n\n\n";
		return 0;
	}
	
	// Abrimos fichero de salida
	fsalida.open(argv[1]);
	if (!fsalida.is_open()) {
		cerr<<"Error: No se pudo abrir fichero para escritura "<<argv[1]<<"\n\n";
		return 0;
	}
	
	// Pasamos por cada tamanio de caso
	for (argumento= 2; argumento<argc; argumento++) {
		
		// Cogemos el tamanio del caso
		k= atoi(argv[argumento]);
        n = 1 << k;  // n = 2^k
		
		cerr << "Ejecutando 2.5 Campeonato N_DyV para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		organizaCampeonato(n); // Ejecutamos el algoritmo para tamanio de caso n
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion << " para tam. caso "<< n<<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<< k <<" "<< n << " " <<tejecucion<<"\n";
		
	}
	
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}