//
// Created by jharo on 7/2/2019.
//

#ifndef TP_PAA_MYPAIR_H
#define TP_PAA_MYPAIR_H

#include <unordered_set>

using namespace std;

class mypair {
    unordered_set<int> I;
    unordered_set<int> A;
public:
    mypair(const unordered_set<int> &a, const unordered_set<int> &i);

    const unordered_set<int> &first() const;

    const unordered_set<int> &second() const;


    bool operator<(const mypair &rhs) const;

};

mypair make_mypair(unordered_set<int> &a,unordered_set<int> &i);

#endif //TP_PAA_MYPAIR_H
