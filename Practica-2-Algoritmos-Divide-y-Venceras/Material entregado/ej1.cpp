#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <cstdlib> 

using namespace std;

bool mayoria_absoluta_iter(int v[],int n,int k){
    int cont[k]={};
    int mas_votado=0;
    bool mayoria_absoluta=false;

	for(int i=0;i<k;i++){
    	for(int j=0;j<n;j++){
            if(v[j]==i){
            	cont[i]++;
            }
        }
        if(cont[i]>=cont[mas_votado] && i!=0){
            mas_votado=i;
			
        }
    }
    if(cont[mas_votado]>n/2){
		
        mayoria_absoluta=true;
    }
	cout<<"mas votado: "<< mas_votado<<" y sus votos: "<<cont[mas_votado]<<endl;
    return mayoria_absoluta;

}


int main(int argc, char* argv[]) {
    int * v;
	int n, i, k,argumento,num_casos_vot,num_casos_cand,cont;
    chrono::time_point<std::chrono::high_resolution_clock> t0, tf; // Para medir el tiempo de ejecución
	unsigned long int semilla;
	ofstream fsalida;
	
	if (argc < 6) {
		cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
		cerr<<argv[0]<<" NombreFicheroSalida semilla nºcasosAProbar nºvotantes1 nºvotantes2 nºvotantes3.... nºvotantes n   nºcandidatos1 .... nºcandodatos n  \n";
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
		v= new int[n];
		cout<<atoi(argv[cont])<<endl;
        k= atoi(argv[cont]);
		// Generamos vector aleatorio de prueba, con componentes entre 0 y n-1
		for (i= 0; i<n; i++)
			v[i]= rand()%k;
		for(i=0;i<=n/2+2;i++){
            v[i]=2;
		}
		// for (i= 0; i<n; i++)
		 //	cout<<v[ i]<<endl;
		cerr << "Ejecutando mayoria absoluta iterativo  para nºvotantes : " << n <<"nºcandidatos"<<k<< endl;
		
		t0= std::chrono::high_resolution_clock::now(); // Cogemos el tiempo en que comienza la ejecuciÛn del algoritmo
        bool l=mayoria_absoluta_iter(v, n,k); // Ejecutamos el algoritmo 
		tf= std::chrono::high_resolution_clock::now();
        if (l){
            cout<<"true"<<endl;
        }else{
            cout<<"false"<<endl;
        }
        
		 // Cogemos el tiempo en que finaliza la ejecuciÛn del algoritmo
		
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