#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {

    int id, m, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // Initialize MPI.
    MPI_Init(&argc, &argv);

    // Get the number of processes.
    MPI_Comm_size(MPI_COMM_WORLD, &m);

    // Get the individual process ID.
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message

    if(id == 0){
        //Compute an array with the right tuples for each processor
        //?

        //READ DATA
        Relation rela,Relation relb, vector<int> ensa, vector<int> ensb;//TODO
        int repartition_variable;


        vector<vector<int>> tuples_to_send[m];
        int size = rela.getSize();

        for(int i = 0; i<size; i++){
            vector<int> tuple = rela.getOrderedTuple(i);
            tuples_to_send[tuple[repartition_variable] % m].push_back(tuple);//this tuple is given to the appropriate processor
        }


        MPI_Scatter(
    tuples_to_send,
    1,//1 cell (vector of tuples by processor
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_COMM_WORLD)


    }
    else{


    }
        //Convert relation to array ? sort
        //tell the set used to join

    //Scatter the tuples to processors



    //Receive and make the join





    //Reduce to get only one joint relation











    // Terminate MPI.
    MPI_Finalize();

    return 0;

}
