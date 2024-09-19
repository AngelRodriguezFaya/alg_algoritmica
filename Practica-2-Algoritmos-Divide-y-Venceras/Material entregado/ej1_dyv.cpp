#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib> 

using namespace std;
int contarVotos(int  v[], int candidato, int inicio, int fin) {
    int conteo = 0;
    for (int i = inicio; i <= fin; ++i) {
        if (v[i] == candidato) {
            conteo++;
        }
    }
    return conteo;

 }
int mayoria_absoluta_dyv(int v[], int n, int inicio, int fin) {
    if (inicio == fin){ 
        return v[inicio];
    }

    // Dividir el rango en dos partes
    int mitad = (inicio + fin) / 2;

    int mayoriaIzquierda = mayoria_absoluta_dyv(v, n, inicio, mitad);
    int mayoriaDerecha = mayoria_absoluta_dyv(v, n, mitad + 1, fin);

    // Combinar las soluciones de ambas partes
    if (mayoriaIzquierda == mayoriaDerecha && mayoriaDerecha!=-1) {
        return mayoriaDerecha;
    }
    else{
        if (mayoriaIzquierda!=-1) {
            if ( contarVotos(v,mayoriaIzquierda, inicio, mitad)+contarVotos(v,mayoriaIzquierda, mitad + 1, fin)> (mitad +1- inicio)) {
                return mayoriaIzquierda;
            }
        }
    
        if (mayoriaDerecha!=-1) {
            if ( contarVotos(v,mayoriaDerecha, inicio, mitad)+contarVotos(v,mayoriaDerecha, mitad + 1, fin)> (fin- mitad+1)) {
                return mayoriaDerecha;
            }
        }
    }
    return -1;
}

int encontrarMayoria(int votos[], int n) {
    return (mayoria_absoluta_dyv(votos, n, 0, n - 1) );
}






int main(int argc, char* argv[]) {
    int * v;
	int n, i, k,argumento,num_casos_vot,num_casos_cand,cont;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc < 6) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida semilla nºcasosAProbar  nºvotantes1 nºvotantes2 nºvotantes3.... nºvotantes_n  nºcandidatos1 .... nºcandidatos_n  \n";
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
    num_casos_vot=atoi(argv[3]);
    cont=4+num_casos_vot;
    for (argumento= 4; argumento<4+num_casos_vot; argumento++,cont++) {
		n= atoi(argv[argumento]);
		// Reservamos memoria para el vector
        k=atoi(argv[cont]);
		v= new int[n];
		// Generamos vector aleatorio de prueba, con componentes entre 0 y k
		for (i= 0; i<n; i++)
			v[i]= rand()%k;
		 for(i=0;i<=(n/2)+10%n;i++)
             v[i]=15;
		cerr << "Ejecutando mayoria absoluta iterativo  para nºvotantes : " << n <<"nºcandidatos"<<k<< endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        int l=encontrarMayoria(v, n); // Ejecutamos el algoritmo 
		tf= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		// if (l){
        //     cout<<"true"<<endl;
        // }else{
        //     cout<<"false"<<endl;
        // }
        cout<<l<<endl;
		unsigned long tejecucion= std::chrono::duration_cast<std::chrono::microseconds>(tf - t0).count();
		
		cerr << "\tTiempo de ejec. (us): " << tejecucion <<endl;
		
		// Guardamos tam. de caso y t_ejecucion a fichero de salida
		fsalida<<n<<" "<<k<<" "<<tejecucion<<"\n";
		
		
		// Liberamos memoria del vector
		delete [] v;
	
    }
	// Cerramos fichero de salida
	fsalida.close();
	
	return 0;
}