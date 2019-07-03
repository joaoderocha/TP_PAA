//
// Created by jharo on 7/2/2019.
//

#include "mypair.h"

mypair::mypair(const unordered_set<int> &i, const unordered_set<int> &a) : A(a), I(i) {}

const unordered_set<int> &mypair::first() const {
    return I;
}

const unordered_set<int> &mypair::second() const {
    return A;
}

bool mypair::operator<(const mypair &rhs) const {
    return this->first().size() < rhs.first().size();
}

mypair make_mypair(unordered_set<int> &i,unordered_set<int> &a){
    return mypair(i,a);
}


