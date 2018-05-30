#include <iostream>
#include <mpi.h>
#include "Relation.h"


uint32_t hash( uint32_t a)
{
    //No hash :
    //return a;

    //Jenkins Hash
   a = (a+0x7ed55d16) + (a<<12);
   a = (a^0xc761c23c) ^ (a>>19);
   a = (a+0x165667b1) + (a<<5);
   a = (a+0xd3a2646c) ^ (a<<9);
   a = (a+0xfd7046c5) + (a<<3);
   a = (a^0xb55a4f09) ^ (a>>16);
   return a;

   //Could use a basic crypto hash and truncate it, such as SHA1 or MD5 (pretty slow)

   //MurmurHash : efficient non-crypto hash

}

Relation basicDistributedJoin(Relation rela,Relation relb, vector<int> ensa, vector<int> ensb, int repartition_variable) {

    int rank, m;

    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &m);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /**
    * Each processor browses all tuples and keeps those he has to process (modulo m)
    **/

    vector<int*> tuples_a_local;
    int size_a = rela.getSize();

    for(int i = 0; i<size_a; i++){
            int* tuple = rela.getOrderedTuple(i);//browse all tuples of relation a
            if(tuple[repartition_variable] % m == rank){
                tuples_a_local.push_back(tuple);//this tuple is given to the processor
            }
    }

    vector<int*> tuples_b_local;
    int size_b = relb.getSize();

    for(int i = 0; i<size_b; i++){
            int* tuple = relb.getOrderedTuple(i);//browse all tuples of relation a
            if(hash(tuple[repartition_variable]) % m == rank{
                tuples_b_local.push_back(tuple);//this tuple is given to the processor
            }
    }

    /**
    *  Each processor computes a join with his tuples
    **/
    Relation rel_a_local = Relation(rela.getArity(), rela.getPermutation(), tuples_a_local);
    Relation rel_b_local = Relation(relb.getArity(), relb.getPermutation(), tuples_b_local);

    Relation joint_local = Relation(rel_a_local, rel_b_local, rela, relb);

    vector<int*> tuples_local = joint_local.getTuples();
    int* permutation_local = joint_local.getPermutation();
    int arity_local = joint_local.getArity();
    int size_local = joint_local.getSize();

    /**
    *  Each non-root process sends his local jointure to the root process
    **/

    if(rank!=0){
        MPI_Send(size_local,1,MPI_INT,0,0,MPI_COMM_WORLD);
        for(int i = 0; i<size_local; i++){
            MPI_Send(joint_local.getOrderedTuple(i),arity_local,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }

    /**
    * Root process gets all local joins and computes the final one
    **/

    if(rank == 0){
        for(int r = 1; r<m; r++){
            int size_r;
            MPI_Recv(size_r,1,MPI_INT,r,0,MPI_COMM_WORLD, &status);
            for(int i = 0; i<size_r; i++){
                int* tuple;
                MPI_Recv(tuple,arity_local,MPI_INT,r,0,MPI_COMM_WORLD, &status);
                tuples_local.push_back(tuple);//we add new tuples to the local tuples of processor 0
            }
        }

        //arity and permutation are the same for all local joins, and tuples_local of 0 contains now all tuples
        Relation joint_total = Relation(arity_local, permutation_local, tuples_local);

        return(joint_total);


    }

    //We don't care of what other processes return
    return Relation(arity_local, permutation_local, tuples_local);










}
