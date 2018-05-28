#ifndef RELATION_H
#define RELATION_H
#include <vector>

//A Relation is a std::vector of int arrays (an array of ints is one tuple of a relation)

class Relation {
    public:
        Relation(const Relation&);
        Relation(int, int[], std::vector<int*>);
        int* getOrderedTuple(int);
        int getSize();
        int getArity();
        int* getPermutation();
        void reorder(int[]);
        struct sortstruct;
        //bool compareTo(int*, int*);


    private:
        int arity;
        int* permutation;
        int size;
        std::vector<int*> tuples;//will always be ordered following permutation
};

Relation readRelation();
void writeRelation(Relation);



#endif
