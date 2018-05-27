#ifndef RELATION_H
#define RELATION_H
#include <vector>

//A Relation is a std::vector of int arrays (an array of ints is one tuple of a relation)

class Relation {
    public:
        Relation(const Relation&);
        Relation(const int, const int[], const std::vector<int*>);
        int* getOrderedTuple(int);
        int getSize();
        int* getPermutation();
        bool compareTo(int*, int*);
        void reorder(int[]);

    private:
        int arity;
        int permutation[];
        int size;
        std::vector<int*> tuples;//will always be ordered following permutation
};

Relation readRelation();
void writeRelation(Relation);



#endif
