#include "Relation.h"
#include "stdio.h"

#include <fstream>
#include <limits>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

Relation::Relation(int _arity, int _permutation[], std::vector<int*> _tuples){
    arity = _arity;
    permutation = _permutation;
    tuples = _tuples;
    size = tuples.size();

}

int* Relation::getOrderedTuple(int rank){
    return tuples[rank];
}

int Relation::getSize(){
    return size;
}

int Relation::getArity(){
    return arity;
}

int* Relation::getPermutation(){
    return permutation;
}

//some trick to use a non static comparator in std::sort
struct Relation::sortstruct{
    Relation* relation;
    int* permutation;
    int arity;
    sortstruct(Relation* r) : relation(r), permutation(r->getPermutation()), arity(r->getArity()){}

    bool operator() (int* tuple1, int* tuple2){
        //use the lexicographic order, with coordinates in the order given by permutation
        int i = 0;
        while (tuple1[permutation[i]] == tuple2[permutation[i]]){
            i++;
            if (i==arity){
                return true;//in this case both tuples are equal
            }
        }
        if (tuple1[permutation[i]]<tuple2[permutation[i]]){
            return true;
        }
        else{
            return false;
        }
    }

};



void Relation::reorder(int* newPermutation){
    sortstruct s(this);
    permutation = newPermutation;
    sort(tuples.begin(), tuples.end(), s);
}
