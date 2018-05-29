#ifndef RELATION_C
#define RELATION_C

#include "Relation.h"
#include "stdio.h"

#include <fstream>
#include <limits>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

Relation::Relation(int _arity, int _permutation[], std::vector<int*> _tuples){
    arity = _arity;
    permutation = _permutation;
    tuples = _tuples;
    size = tuples.size();

}

Relation::Relation(string const& filename){
    ifstream inputfile(filename.c_str(),ios::in);

    if (inputfile){
        int sizecount = 0;//counting size of the relation
        string line;
        vector<int*> tuples;
        while(getline(inputfile, line)){
            vector<string> idsstring;
            istringstream iss (line);
            sizecount ++;
            int i = 0; //counting arity
            string elem;
            while(getline(iss,elem,' ')){
                idsstring.push_back(elem);
                i++;
            }
            arity = i;
            int* ids = new int[i];
            for(int k = 0;k<arity;k++){
                ids[k] = atoi(idsstring[k].c_str());
            }
            tuples.push_back(ids);
        }
        size = sizecount;
        this->tuples = tuples;
        this->initPermutation(size);
        this->reorder(this->permutation);
    }
    else{
        throw(string("Fichier invalide."));
    }

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

//Initializing the permutation at the creation of the relation.

void Relation::initPermutation(int size){
    int* permutation = new int[size];
    for(int i=0;i<size;i++){
        permutation[i] = i;
    }
    this->permutation = permutation;
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
    //setting the permutation gives us a new order
    permutation = newPermutation;
    sortstruct s(this);
    sort(tuples.begin(), tuples.end(), s);
}

#endif
