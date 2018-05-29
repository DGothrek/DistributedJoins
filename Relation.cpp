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

Relation jointure(Relation rela,Relation relb, vector<int> ensa, vector<int> ensb){
  //Computes the join of rela et relb. ensa contains the variable in rela
  //that pair with the variables of b contained in ensb. We must assert
  //that the two lists ensa et ensb have the same length and that they are
  //compatible with the arities of rela et relb.
  int len;
  if (ensa.size()!=ensb.size()){
    throw(string("The columns are not compatible because of their lengths."))
  }
  len = ensa.size();

  //Preparing the permutations.
  sa = rela.getArity();
  sb = relb.getArity();
  int* pa = new int[sa];
  int* pb = new int[sb];
  int counta = 0;
  for(int i = ensa.begin();i!=ensa.end();i++){
    pa[counta] = i;
    counta++;
  }
  for(int j=0;j<sa;j++){
    if(find(ensa.begin();ensa.end(),j)==ensa.end()){//the element does not belong to ensa
      pa[counta] = j;
      counta++;
    }
  }
  int countb = 0;
  for(int i = ensb.begin();i!=ensb.end();i++){
    pa[countb] = i;
    countb++;
  }
  for(int j=0;j<sa;j++){
    if(find(ensb.begin();ensb.end(),j)==ensb.end()){//the element does not belong to ensa
      pa[countb] = j;
      countb++;
    }
  }
  //this way the permutation contains the elements to compare first, and in the good order.

  //now working on the join.

  //First rearranging the comparisons of a and b, so that the comparison if good.
  rela.reorder(pa);
  relb.reorder(pb);

}


#endif
