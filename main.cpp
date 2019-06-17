#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

vector<vector<int>> loadGraph();

int main() {


    vector<vector<int>> matriz = loadGraph();
    cout << endl;



    for(const auto& a : matriz){
        for(const auto b : a){
            cout << b << " ";
        }
        cout << endl;
    }




    return 0;
}


/*
 * Inicializa uma matriz binaria para o grafo
 *
 *
 */
vector<vector<int>> loadGraph(){
    ifstream ios("input.txt",fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<vector<int>> matriz(size,vector<int>(size,-1));
    int i=0,j=0;

    for(const auto& a : matriz){
        for(const auto b : a){
            cout << b << " ";
        }
        cout << endl;
    }

    while(!ios.eof()){
        if(i >= j && i < 9){
            ios >> aux;
            matriz[i][j] = aux;
            matriz[j][i] = aux;
            j++;
        }else{
            ios.ignore(numeric_limits<streamsize>::max(),'\n');
            j=0;
            i++;
        }

        for(const auto& a : matriz){
            for(const auto b : a){
                cout << b << " ";
            }
            cout << endl;
        }

    }


    ios.close();
    return matriz;
}