#include <iostream>
#include <mpi.h>
#include "Relation.h"
#include "testRelation.cpp"


int main (int argc, char *argv[]) {

    try{

        /**
        * Read files
        **/

        Relation relat_test1 = Relation("data/facebook.dat");
        Relation relat_test2 = Relation("data/facebook.dat");
        vector<int> ens1;
        vector<int> ens2;
        ens1.push_back(0);
        ens2.push_back(1);


        /**
        * Compute a basic distributed join
        **/

        MPI_Init(&argc, &argv);

        Relation relat_test = basicDistributedJoin(relat_test1,relat_test2,ens1,ens2,0);

        MPI_Finalize();

        int size = relat_test.getSize();
        for(int i=0;i<size;i++){
            for(int j=0;j<relat_test.getArity();j++){
                std::cout<<relat_test.getOrderedTuple(i)[j]<<", ";
            }
            cout<<endl;
        }
    }
    catch(string const& err){
        cout<<err<<endl;
    }






    return 0;
}
