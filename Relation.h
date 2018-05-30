#ifndef RELATION_H
#define RELATION_H
#include <vector>
#include <string>

//A Relation is a std::vector of int arrays (an array of ints is one tuple of a relation)
using namespace std;

class Relation {
    public:
        Relation(int, int[], vector<int*>);
        Relation(const string&);
        Relation(Relation,Relation,vector<int>,vector<int>);
        int* getOrderedTuple(int);
        int getSize();
        int getArity();
        int* getPermutation();
        void reorder(int[]);
        struct sortstruct;
        vector<int*>getTuples();
        //bool compareTo(int*, int*);


    private:
        int arity;
        int* permutation;
        int size;
        std::vector<int*> tuples;//will always be ordered following permutation
        void initPermutation(int);//to initialize the permutation at the creation from a file.
};

Relation readRelation();
void writeRelation(Relation);
int smallerX(int*,int*,int*,int*,int);



#endif
