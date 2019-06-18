#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<unordered_set<int>> loadGraph();
void maximumIndependent(vector<unordered_set<int>>const&, unordered_set<int>, unordered_set<int>);
//int maximumIndependent2(vector<unordered_set<int>> , unordered_set<int> , unordered_set<int> );
bool check(const vector<unordered_set<int>>& );
int greedy(vector<unordered_set<int>> );
int bs = 0;

int main() {

    vector<unordered_set<int>> G = loadGraph(); // inicializo lista de adjacencias para cada vertice
    unordered_set<int> A;
    unordered_set<int> I;
    int best=0;
    // Inicializa todos vertices por nao serem explorados ainda.
    for (int i = 1; i <= G.size(); i++) {
        A.insert(i);
    }
    // Inicializa o conjunto de solucoes vazio
    I.empty();
    //maximumIndependent2(G,I,A);
    maximumIndependent(G,I,A);
    // Inicia a busca pelo conjunto independente maximo
    cout << "Resultado: " << greedy(G);
    cout << endl;
    cout << bs;



    return 0;
}

void maximumIndependent(vector<unordered_set<int>>const& G, unordered_set<int> I, unordered_set<int> A){


    if(A.empty()){
        return;
    }

    int aux = *A.begin();
    A.erase(aux);
    unordered_set<int> A1(A);
    if(I.find(aux) == I.end()){

        for(auto a : G[aux-1]){
            A.erase(a);
        }
        unordered_set<int> A2(A);
        I.insert(aux);
        unordered_set<int> I2(I);
        I.erase(aux);
        maximumIndependent(G,I,A1);
        maximumIndependent(G,I2,A2);
        if(I.size()+1 > bs) bs = I.size()+1;
    }else{
        maximumIndependent(G,I,A1);
    }
}
/*
int maximumIndependent2(vector<unordered_set<int>> G, unordered_set<int> I, unordered_set<int> A,int bsx){

    int bs =0;
    int verticeAtual = *A.begin();
    A.erase(verticeAtual);
    if(I.find(verticeAtual) != I.end()){
        unordered_set<int> A2;
        int bs1=maximumIndependent2(G,I,A)
    }



}
*/

/*
 * Inicializa uma matriz binaria para o grafo
 *
 *
 */
vector<unordered_set<int>> loadGraph(){
    ifstream ios("input.txt",fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<unordered_set<int>> matriz(size,unordered_set<int>());
    int i=0,j=0;

    while(!ios.eof()){
        if(i >= j && i < 9){
            ios >> aux;
            if(aux == 1){
                matriz[i].insert(j+1);
                matriz[j].insert(i+1);
            }
            j++;
        }else{
            ios.ignore(numeric_limits<streamsize>::max(),'\n');
            j=0;
            i++;
        }

    }


    ios.close();
    return matriz;
}

int greedy(vector<unordered_set<int>> G){
    unordered_set<int> I;
    while(check(G)) {
        int min = numeric_limits<int>::max();
        int indice = -1, i;
        for (i = 0; i < G.size(); i++) {
            if (min > G[i].size() && !G[i].empty()) {
                min = G[i].size();
                indice = i;
            }
        }
        I.insert(indice + 1);
        for (auto pos = G[indice].begin(); pos != G[indice].end(); ++pos) {
            G[(*pos) - 1].clear();
        }
        G[indice].clear();
    }
    cout << "\nIndependent Set: ";
    for(auto a : I){
        cout << a << " ";
    }
    return I.size();
}

bool check(const vector<unordered_set<int>>& G){
    for(auto & pos : G){
        if(!pos.empty()){
            return true;
        }
    }
    return false;
}