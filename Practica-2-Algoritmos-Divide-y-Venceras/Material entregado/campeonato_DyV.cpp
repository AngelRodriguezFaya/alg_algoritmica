#include <iostream>
#include <vector>
#include <fstream> // Para usar ficheros
#include <chrono>

using namespace std;

struct Partido {
    int jugador1;
    int jugador2;
};

void organizaCampeonatoDyV(vector<int>& jugadores, int diaInicio, vector<vector<Partido>>& calendario) {
    int n = jugadores.size();
    if (n == 1) { 
        return;
    }

    vector<int> jugadores1(jugadores.begin(), jugadores.begin() + n/2);
    vector<int> jugadores2(jugadores.begin() + n/2, jugadores.end());

    organizaCampeonatoDyV(jugadores1, diaInicio, calendario);
    organizaCampeonatoDyV(jugadores2, diaInicio + n/2, calendario);

    for (int i = 0; i < n/2; ++i) {
        for (int j = 0; j < n/2; ++j) {
            Partido partido{jugadores1[j], jugadores2[(j+i) % (n/2)]};
            calendario[diaInicio + i].push_back(partido);
        }
    }
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

        // Declaraciones en inicializaciones
        vector<int> jugadores(n);
        for (int i = 0; i < n; ++i) 
            jugadores[i] = i;
        
        vector<vector<Partido>> calendario(n);
		
		cerr << "Ejecutando 2.5 Campeonato DyV para tam. caso: " << n << endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
		organizaCampeonatoDyV(jugadores, 0, calendario);; // Ejecutamos el algoritmo para tamanio de caso n
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