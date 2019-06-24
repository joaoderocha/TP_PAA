#include "MIS.h"

unordered_set<int> solution;
int bst = 0;

int findMSI() {

    vector<unordered_set<int>> G = loadGraphComplemento(); // inicializo lista de adjacencias para cada vertice
#if defined(DEBUG)
    int i=0;
    for(const auto& a: G){
        cout << " vertice " << i << " adjacentes: ";
        for(auto b : a){
            cout << b << " ";
        }
        i++;
        cout << endl;
    }
#endif
    unordered_set<int> A;
    unordered_set<int> I;
    int best=0;
    // Inicializa todos vertices por nao serem explorados ainda.
    for (int x = 0; x < G.size(); x++) {
        A.insert(x);
    }
    // Inicializa o conjunto de solucoes vazio
    I.empty();
    //maximumIndependent2(G,I,A);
    auto t1 = high_resolution_clock::now();
    bst = 0;//greedy(G);
    maximumIndependent(G,I,A);
    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    // Inicia a busca pelo conjunto independente maximo
    cout << endl;

    cout << "MIS: " << bst << " elementos: ";
    for(auto a : solution){
        cout << a << " ";
    }
    cout <<" Tempo gasto: ";
    cout.precision(5);
    cout << fixed << time_span.count();



    return 0;
}

void maximumIndependent(vector<unordered_set<int>>const& G, unordered_set<int> I, unordered_set<int> A){


    if(A.empty()){
        return;
    }
#if defined(DEBUG)
    if(I.size() == 4){
        cout << "stop!";
    }
    {
        cout << "Instancia: \n";
        cout << "I: ";
        for(auto a : I){
            cout << a << " ";
        }
        cout << endl;
        cout << "A: ";
        for(auto b : A){
            cout << b << " ";
        }
        cout << endl;
    }
#endif
    int aux = *A.begin();
    A.erase(aux);
    unordered_set<int> A1(A); // Elementos que podem ser usados
    if(I.insert(aux).second){ // Se aux pode ser adicionado na solucao atual

        if(!A.empty()) {
            for (auto a : G[aux]) { // tira dos que podem ser adicionados a solucao os vizinhos de aux
                A.erase(a);
            }
        }
        unordered_set<int> A2(A); // copia dos adjacentes da melhor solucao
        unordered_set<int> I2(I); // copia da melhor solucao

        I.erase(aux);
        if(teste(A2.size(),countEdge(G,A2)) > bst) {
            maximumIndependent(G, I2, A2);
            if (I.size() + 1 > bst) {
                solution = I2;
                bst = I.size() + 1;
            }
        }
#if defined(DEBUG)
        cout << " test: " << teste(A2.size(),countEdge(G,A2));
        cout << " \n bst: " << bst;
#endif
        if(teste(A2.size(),countEdge(G,A2)) > bst)
            maximumIndependent(G,I,A1);

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
vector<unordered_set<int>> loadGraph(const string& arquivo){
    ifstream ios(arquivo,fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<unordered_set<int>> matriz(size,unordered_set<int>());
    int i=0,j=0;

    while(!ios.eof()){
        if(i >= j && i < size){
            ios >> aux;
            if(aux == 1){
                matriz[i].insert(j);
                matriz[j].insert(i);
            }
            j++;
        }else{
            ios.ignore(numeric_limits<streamsize>::max(),'\n');
            j=0;
            i++;
        }

    }

#if defined(DEBUG)
    i=0;
    for(const auto& a: matriz){
        cout << " vertice " << i << " adjacentes: ";
        for(auto b : a){
            cout << b << " ";
        }
        i++;
        cout << endl;
    }
#endif
    ios.close();
    return matriz;
}
/*
 * Gera o complemento do grafo dado
 */
vector<unordered_set<int>> loadGraphComplemento(const string& arquivo){
    ifstream ios(arquivo,fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<unordered_set<int>> matriz(size,unordered_set<int>());
    int i=0,j=0;

    while(!ios.eof()){
        if(i >= j && i < size){
            ios >> aux;
            if(aux == 0){
                matriz[i].insert(j);
                matriz[j].insert(i);
            }
            j++;
        }else{
            ios.ignore(numeric_limits<streamsize>::max(),'\n');
            j=0;
            i++;
        }

    }

#if defined(DEBUG)
    i=0;
    for(const auto& a: matriz){
        cout << " vertice " << i << " adjacentes: ";
        for(auto b : a){
            cout << b << " ";
        }
        i++;
        cout << endl;
    }
#endif
    int indice =0;
    for(auto& x : matriz){
        x.erase(indice);
        indice++;
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
        I.insert(indice );
        for (auto pos = G[indice].begin(); pos != G[indice].end(); ++pos) {
            G[(*pos) ].clear();
        }
        G[indice].clear();
    }
    solution = I;
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

/*
 * Conta quantidade de arestas 'counter' em uma lista de vertices A, de um grafo G
 *
 *
 *
 * 1 - Inicializa contador
 * 2 - Para cada elemento presente em A, verifique em G o numero de adjacentes.
 * 3 - retorne n/2
 */
int countEdge(vector<unordered_set<int>>const& G, unordered_set<int>const& A){
    int counter=0;
    if(!A.empty()) {
        for (int pos : A) {
            for (int pos2 : G[pos]) {
                if (A.find(pos2) != A.end()) {
                    counter++;
                }
            }
        }
        return floor(counter / 2);
    }else{
        return 0;
    }
}
/*
 * Um grafo de n vertices e m arestas nao pode ter um conjunto independente maximo maior do que o resultado da formula a seguir
 */
int teste(int n, int m){
    return floor((1 + sqrt(1-8*m - 4*n + 4*pow(n,2)))/2);
}
/*
 * Gera o complemento de um grafo lido em input.txt e escreve no mesmo formato em input2.txt
 */
void generateComplementoTxt(){
    ifstream ios("input.txt", fstream::in);
    ofstream out("input2.txt",fstream::out);
    int i = 0, j = 0,size;
    bool aux;
    ios >> size;
    out << size << endl;
    while(!ios.eof()){
        ios >> aux;
        if(i!=j){
            out << !aux << (j < size-1 ? " " : "");
            j++;
        }else{
            out << 0 << (j < size-1 ? " " : "");
            j++;
        }
        if(j == size){
            j=0;
            i++;
            if(ios.peek()!= char_traits<char>::eof()) out << endl;
        }
    }

    ios.close();
    out.close();

}