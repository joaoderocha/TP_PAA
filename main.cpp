#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <unordered_set>
#include <algorithm>
#include <chrono>




using namespace std;
using namespace chrono;


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
    auto t1 = high_resolution_clock::now();
    bs = greedy(G);
    maximumIndependent(G,I,A);
    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    // Inicia a busca pelo conjunto independente maximo
    cout << endl;

    cout << "MIS: " << bs << " Tempo gasto: ";
    cout.precision(5);
    cout << fixed << time_span.count();


    return 0;
}

void maximumIndependent(vector<unordered_set<int>>const& G, unordered_set<int> I, unordered_set<int> A){


    if(A.empty()){
        return;
    }

    int aux = *A.begin();
    A.erase(aux);
    unordered_set<int> A1(A); // Elementos que podem ser usados
    if(I.find(aux) == I.end()){ // Se aux pode ser adicionado na solucao atual

        for(auto a : G[aux-1]){ // tira dos que podem ser adicionados a solucao os vizinhos de aux
            A.erase(a);
        }
        unordered_set<int> A2(A); //
        I.insert(aux);
        unordered_set<int> I2(I);
        I.erase(aux);
        if(I.size()+A.size() > bs)
            maximumIndependent(G,I,A1);
        if(I.size()+A2.size()+1 > bs) {
            maximumIndependent(G, I2, A2);
            if (I.size() + 1 > bs) bs = I.size() + 1;
        }
    }else{
        maximumIndependent(G,I,A1);
    }
}

/*
 * Objetivo: Inicializa uma matriz binaria para o grafo
 * Descricao: Le um arquivo de entrada que contem o numero de vertices seguido
 * por uma matriz que representa as adjacencias da mesma
 * cria um vetor de sets nao ordenados do tamanho da entrada X.
 * crie duas variaveis i e j para simular uma matriz com o valor 0 em ambos
 * crie uma variavel auxiliar para ler o conteudo do arquivo
 * 1 - enquanto nao encontrar o final do arquivo
 * 2 - Se o contador i for maior ou igual a j e i seja menor que o numero de vertices faca:
 *          2.1 - leia o proximo elemento do arquivo
 *          2.2 - se for igual a 1, significa que existe um vertice de i para j entao faca
 *              2.2.1 - Adicione j+1 a X na posicao i
 *              2.2.2 - Adicione i+1 a X na posicao j
 *          2.3 - incremente J
 *      Caso contrario
 *      pule pra proxima linha do arquivo
 *      contador j recebe 0
 *      incremente i
 * 3 - fecha arquivo
 * 4 - retorne X
 */
vector<unordered_set<int>> loadGraph(){
    ifstream ios("input.txt",fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<unordered_set<int>> matriz(size,unordered_set<int>());
    int i=0,j=0;

    while(!ios.eof()){
        if(i >= j && i < size){
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
/*
 * Aproixmacao gulosa do do problema de conjunto independente maximo
 * 1 - Verifica em G se existem vertices possiveis de serem adicionados a solucao I CC passo 5
 * 2 - Procura pelo primeiro elemento com o menor numero de adjacencias
 * 3 - insere ele na solucao I e remove todos adjacentes dele
 * 4 - volta pro passo 1
 * 5 - o conjunto independente encontrado e I
 */
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
    return I.size();
}
/*
 * Verifica se o grafo G possui elementos com listas de adjacentes vazias
 * retorna verdadeiro caso encontre um vertice com elementos adjacentes a ele
 * e falso caso contrario.
 */
bool check(const vector<unordered_set<int>>& G){
    for(auto & pos : G){
        if(!pos.empty()){
            return true;
        }
    }
    return false;
}