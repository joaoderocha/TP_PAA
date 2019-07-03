#include <iostream>
#include <afxres.h>
#include <queue>
#include "MIS.h"
#include "mypair.h"
#include <utility>






/*struct PairComparator {
    bool operator()(const std::pair<unordered_set<int>, unordered_set<int>> &p1,
                    const std::pair<unordered_set<int>, unordered_set<int>> &p2) const {
        return p1.first.size() < p2.first.size();
    }
};*/

/*bool PairComparator (const pair<unordered_set<int>, unordered_set<int>> &p1, const pair<unordered_set<int>, unordered_set<int>> &p2){
        return p1.first.size() < p2.first.size();

};*/
/*typedef bool (*comp)(pair<unordered_set<int>, unordered_set<int>>,pair<unordered_set<int>, unordered_set<int>>);
bool PairComparator (const pair<unordered_set<int>, unordered_set<int>> &p1, const pair<unordered_set<int>, unordered_set<int>> &p2){
    return p1.first.size() < p2.first.size();

};*/
/*auto PairComparator = [] ( pair<unordered_set<int>, unordered_set<int>> &p1, pair<unordered_set<int>, unordered_set<int>> &p2){
    return p1.first.size() < p2.first.size();
};*/




int main() {

    //cout << "Resolve MSI:";
    findMSI();
    //cout << "Resolve Clique maximo: ";
    //cout << "Seja G' o grafo complemento do original G, ache o MSI em G' que o resultado sera o Clique maximo em G.";
     // inverte grafico dps executa findMSI ou executa findMSI com param diferente

     //generateSat();


    return 0;
}