#include <stack>
#include <iostream>
#include <vector>
#include <list>
#include <stdlib.h>


using namespace std;



pair<bool,list<pair<int,int> > >  buscarSalida(vector<vector<bool> > &mapa, int objetivo,int fil,int col){
    
    mapa[fil][col]=false;
    pair<bool,list<pair<int,int> > >cas;
    cas.first=false; 
    pair <int,int> aux;
    aux.first=fil;
    aux.second=col;
   
    pair <int,int> child;

    pair<bool,list<pair<int,int> > > z;
    

    if(fil==objetivo && col==objetivo){
        cas.first=true;
        cas.second.push_front(aux);
        return cas;
       
    
    }
    for(int i=0;i<4;i++){
        if(i==0){//arriba
            if( fil>0  && mapa[fil-1][col]){
                child.first= fil-1;
                z=buscarSalida(mapa,objetivo,child.first,col);
                if(z.first){
                    z.second.push_front(make_pair(fil,col));
                    return z;
                }
            }


        }
        else if(i==1){//derecha
            if( col<=objetivo-1  && mapa[fil][col+1]){
                child.second= col+1;
                z=buscarSalida(mapa,objetivo,fil,child.second);
                if(z.first){
                    z.second.push_front(make_pair(fil,col));
                    return z;
                }
            }
        }
        else if(i==2){//abajo
            if( fil<=objetivo-1  && mapa[fil+1][col]){
                child.first= fil+1;
                z=buscarSalida(mapa,objetivo,child.first,col);
                if(z.first){
                    z.second.push_front(make_pair(fil,col));
                    return z;
                }
            }
        }
        else if(i==3){//izquierda
            if( col>0 && mapa[fil][col-1]){
                child.second= col-1;
                z=buscarSalida(mapa,objetivo,fil,child.second);
                if(z.first){
                    z.second.push_front(make_pair(fil,col));
                    return z;
                }
            }
        }

    }
    







    return cas;
}







int main(int argc,char **argv){

    vector<vector<bool> > mapa;
    vector<bool> auxi;
    int n;

    if(argc!=2){
        cerr<<"formato incorrecto , se escribe ./ej4.1 tamaño_en_int_del_laberinto_nXn(el mapa esta preparado para un 4x4 :)  )"<<endl;
        exit(1);
    }
   n=atoi(argv[1]);

   
    auxi.resize(n);
   for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if((i!=0 or j!=3)and (i!=1 or j!=2) and (i!=2 or j!=0) and(i!=3 or j!=0)/*and(i!=1 or j!=3)*/)
                auxi[j]=true;
             
            else
                auxi[j]=false;
        }

        mapa.push_back(auxi);
   }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mapa[i][j])
                cout<<"T   ";
            else
                cout<<"F   ";
        }
        cout<<endl;
    }
    auto r=buscarSalida(mapa,n-1,0,0);
    //pair<bool,list<pair<int,int> > > r;

    pair <int,int> aux;
    if(r.first){
        int tam=r.second.size();
        for(int i=0;i<tam;i++){
            aux=r.second.front();
            r.second.pop_front();
            cout<<"( "<<aux.first<<" , "<<aux.second<<" ), ";
        }
    }
    cout<<endl;




    return 0;
}
