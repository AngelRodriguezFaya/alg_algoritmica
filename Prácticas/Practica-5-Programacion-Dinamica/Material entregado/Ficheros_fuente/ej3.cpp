#include <stack>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>


using namespace std;


vector<vector<int> > coleccionarOro(vector<vector<int> > &mapa,int fil,int col ){
    vector<vector<int> > m;
    int var;
    m.resize(fil);
    for(int i=0;i<fil;i++){
        m[i].resize(col);
    }


    m[0][col-1]=0;
    for(int i=0;i<fil;i++){
        
        for(int j=col-1;j>=0;j--) {
            var=-1;
            if(mapa[i][j]==-1){
                m[i][j]=-1;
            }
            else{//comparamos de que casilla viene
                
                if(j+1<col ){
                    var=max(var,m[i][j+1]);
                }
                if(i-1>=0){
                    var=max(var,m[i-1][j]);

                }
                if(j+1<col&& i-1>=0){
                    var=max(var,m[i-1][j+1]);
                }

                if(mapa[i][j]==1 && var!=-1){
                    var+=1;
                }
            }
            if(!(i==0 and j==col-1)){
                m[i][j]=var;
            }
           
        }
    }    
    return m;

}

vector<pair<int, int>> sacarSolucion(const vector<vector<int>> &mapa, int fil, int col) {
    vector<pair<int, int>> camino;
    int i = fil-1;
    int j = 0;
    int siguiente_i;
    int siguiente_j;
    int var;

    while (!(i ==0 &&  j == col-1)) {
        camino.insert(camino.begin(),make_pair(i,j));
        
        var=-1;
        if (mapa[i][j] == -1) {
             siguiente_i = i;
            siguiente_j = j;
             
        }else{
            if (j + 1 < col) {
                var = mapa[i][j + 1];
                siguiente_i = i;
                siguiente_j = j + 1;
            }
             if (i - 1 >= 0) {

                if(var < mapa[i - 1][j]){
                    var= mapa[i-1][j];
                    siguiente_i = i - 1;
                    siguiente_j = j;
                }
            }  
            if (j + 1 < col) {
                if(var < mapa[i - 1][j + 1]){
                    var = mapa[i - 1][j + 1];
                    siguiente_i = i - 1;
                    siguiente_j = j + 1;
                }
            }
            i = siguiente_i;
            j = siguiente_j;
            
        
        }
        camino.insert(camino.begin(),make_pair(i,j));
        // Determinar la dirección desde donde se llegó a (i, j)
        
    }

    return camino;
}


int main(int argc, char **argv) {
  
    vector<vector<int> > m;

    int fil,col,oro, resultado;
    unsigned long int semilla;

    if (argc != 5) {
        cerr<<"\nError: El programa se debe ejecutar de la siguiente forma.\n\n";
        cerr<<argv[0]<<" semilla num_fila num_Columna num_bolsas_Oro\n\n";
        return 0;
    }

    // Inicializamos generador de no. aleatorios
    semilla= atoi(argv[1]);
    srand(semilla);

    fil = atoi(argv[2]);
    col = atoi(argv[3]);
    oro = atoi(argv[4]);

    vector<int> aux;
    aux.resize(col);
    for(int i=0; i< fil; i++){
        for(int j= 0; j< col; j++){
            aux[j]= 0;

        }
        m.push_back(aux);
    }

    for(int a=0; a<oro; a++){
        m[rand()%fil][rand()%col]= 1;
    }
    for(int a=0; a<2; a++){
        int f=rand()%fil;
        int c = rand()%col;
        if(m[f][c]!=1){
            m[f][c]= -1;
        }
    }
    m[0][col-1]=0;
    m[fil-1][0]=0;

    cout << "  laberinto:"<<endl;
    for(int i=0;i<fil;i++){
        for(int j=0;j<col;j++){
            cout<<m[i][j]<<"  ";
        }
        cout<<endl;
    }
    cout << endl<<endl;
    vector<pair<int, int>> res;
    vector<vector<int> > auxi;
    auxi=coleccionarOro(m,m.size(),m[0].size());
     cout << "  laberinto:"<<endl;
    for(int i=0;i<fil;i++){
        for(int j=0;j<col;j++){
            cout<<auxi[i][j]<<"  ";
        }
        cout<<endl;
    }
    res = sacarSolucion(auxi,fil,col);
      cout<<"secuencia solución: ";
        pair<int,int> au;
       for (const auto &p : res) {
            cout << "( " << p.first << " , " << p.second << " ), ";
        }
        cout << endl;
   
    return 0;
}

