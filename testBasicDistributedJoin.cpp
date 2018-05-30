#include <iostream>
#include <mpi.h>
#include "Relation.h"


int main (int argc, char *argv[]) {

    /**
    * Read files
    **/

    Relation rela,Relation relb, vector<int> ensa, vector<int> ensb;//TODO
    int repartition_variable;


    /**
    * Compute a basic distributed join
    **/

    MPI_Init(&argc, &argv);



    MPI_Finalize();
    return 0;
