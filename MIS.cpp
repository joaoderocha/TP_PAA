#include <queue>
#include "MIS.h"
#include "mypair.h"

unordered_set<int> solution;
//int bst = 0;
int ninst =0;
vector<pair<int,unordered_set<int>>> G;
priority_queue<mypair> S;





int findMSI() {

    G = loadGraph(); // inicializo lista de adjacencias para cada vertice
#if defined(DEBUG)
    int i=0;
    for(const auto& a: G){
        cout << " vertice " << i << " adjacentes: ";
        for(auto b : a.second){
            cout << b << " ";
        }
        i++;
        cout << endl;
    }
#endif
    // Inicializa o conjunto de solucoes vazio
    auto t1 = high_resolution_clock::now();
    int best = 0;//greedy(G);
    best = MIS(best);
    auto t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> >(t2 - t1);
    // Inicia a busca pelo conjunto independente maximo
    cout << endl;

    cout << "MIS: " << best << " elementos: ";
    for(auto a : solution){
        cout << a << " ";
    }
    cout <<" Tempo gasto: ";
    cout.precision(5);
    cout << fixed << time_span.count();
    cout << " segundos";
#if defined(DEBUG)
    cout << endl << ninst;
#endif

    return 0;
}

int maximumIndependent(vector<pair<int,unordered_set<int>>> G, unordered_set<int> I, unordered_set<int> A,int bi){
    int bs=0;

    if(A.empty()){
        return I.size();
    }
#if defined(DEBUG)
    ninst++;
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
            for (auto a : G[aux].second) { // tira dos que podem ser adicionados a solucao os vizinhos de aux
                A.erase(a);
            }
        }
        unordered_set<int> A2(A); // copia dos adjacentes da melhor solucao atual
        unordered_set<int> I2(I); // copia da melhor solucao atual

        I.erase(aux);

        if(teste(G.size(),countEdge(A2)) > bi) {
            bs = maximumIndependent(G, I2, A2, I2.size());
        }
        if(teste(G.size(),countEdge(A1)) > bi) {
            bs = max(maximumIndependent(G, I, A1, I.size()), bs);
        }
        if(solution.size() < I2.size()){
            solution = I2;
        }
#if defined(DEBUG)
        cout << " \n bst: " << bs;
#endif


    }else{
        if(teste(G.size(),countEdge(A1)) > bi)
            bs = maximumIndependent(G,I,A1,I.size());
    }
    return bs;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefectsInspection"
int MIS(const int& bi){
    int bs = bi,aux;
    unordered_set<int> I;
    unordered_set<int> A;
    for (int x = 0; x < G.size(); x++) {
        A.insert(x);
    }
    S.push(make_mypair(I,A));
    while(!S.empty()) {
        I = S.top().first();
        A = S.top().second();
        S.pop();
        if (!A.empty()) {
            aux = *A.begin();
            A.erase(aux);
            unordered_set<int> A1(A);
            if (I.insert(aux).second) {
                if (!A.empty()) {
                    for (auto a : G[aux].second) { // tira dos que podem ser adicionados a solucao os vizinhos de aux
                        A.erase(a);
                    }
                }
                 // copia dos adjacentes da melhor solucao atual
                unordered_set<int> I2(I); // copia da melhor solucao atual

                I.erase(aux);

                if(I2.size()+A.size() > bs){ // coloco
                    S.push(make_mypair(I2,A));
                    if(I2.size() > bs){
                        bs = I2.size();
                    }
                }
                if(I.size()+A1.size() > bs){ // nao coloco
                    S.push(make_mypair(I,A1));
                }


            }else{
                S.push(make_mypair(I,A1));
            }
        }

    }


    return bs;
}
#pragma clang diagnostic pop


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
vector<pair<int,unordered_set<int>>> loadGraph(const string& arquivo){
    ifstream ios(arquivo,fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<pair<int,unordered_set<int>>> matriz(size,make_pair(0,unordered_set<int>()));
    int i=0,j=0;
    cout << matriz.size() << " size \n";
    while(!ios.eof()){
        if(i >= j && i < size){
            ios >> aux;
            if(aux == 1){
                matriz[i].second.insert(j);
                matriz[j].second.insert(i);
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
        for(auto b : a.second){
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
vector<pair<int,unordered_set<int>>> loadGraphComplemento(const string& arquivo){
    ifstream ios(arquivo,fstream::in);

    int size;
    int aux;
    ios >> size;
    vector<pair<int,unordered_set<int>>> matriz(size,make_pair(0,unordered_set<int>()));
    int i=0,j=0;

    while(!ios.eof()){
        if(i >= j && i < size){
            ios >> aux;
            if(aux == 0){
                matriz[i].second.insert(j);
                matriz[j].second.insert(i);
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
        for(auto b : a.second){
            cout << b << " ";
        }
        i++;
        cout << endl;
    }
#endif
    int indice =0;
    for(auto& x : matriz){
        x.second.erase(indice);
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
    while(check()) {
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
bool check(){
    for(auto & pos : G){
        if(!pos.second.empty()){
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
int countEdge( unordered_set<int>const& A){
    int counter=0;
    if(!A.empty()) {
        for (int pos : A) {
            for (int pos2 : G[pos].second) {
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


vector<pair<int,unordered_set<int>>> generateSat(const string& arquivo) {
    ifstream ios(arquivo, fstream::in);
    int aux,x=0;
    vector<pair<int,unordered_set<int>>> matriz;
    ios >> aux;
    while(!ios.eof()) {// crio todos os vertices da matriz incluindo os que nao tem variavel
        ios >> aux;
        matriz.emplace_back();
        matriz[x].first=aux;
        x++;
    }

    for(int i=0;i<matriz.size();i+=3){ // adiciono arestas a todos elementos da mesma clausula
        // primeira variavel
        matriz[i].second.insert(i+1);
        matriz[i].second.insert(i+2);
        // segunda variavel
        matriz[i+1].second.insert(i);
        matriz[i+1].second.insert(i+2);
        // terceira variavel
        matriz[i+2].second.insert(i);
        matriz[i+2].second.insert(i+1);
    }
    for(int i=0;i<matriz.size();i++){ // adiciono arestas aos vertices que se o oposto uns dos outros
        for(int j=i+3;j<matriz.size();j+=3){
            if(matriz[i].first != 2 && matriz[j].first != 2){
                if(matriz[i].first == !matriz[j].first){
                    matriz[i].second.insert(j);
                    matriz[j].second.insert(i);

                }

            }
        }
    }
    for(auto a = matriz.begin();a != matriz.end();++a){ // removo os vertices nao existentes
        if(a->first == 2){
            matriz.erase(a);
            a--;
        }
    }
    x=0;
    for(const auto& a : matriz){
        cout <<"vetice"<< x << "    " << a.first << "<------- valor do vertice ||| adjacentes ---->";
        for(auto b : a.second){
            cout << b <<" ";
        }
        cout << endl;
        x++;
    }



    ios.close();
    return matriz;
}
