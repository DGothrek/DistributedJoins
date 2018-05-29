#include <iostream>
#include <mpi.h>

int main (int argc, char *argv[]) {

    int id, p, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // Initialize MPI.
    MPI_Init(&argc, &argv);

    // Get the number of processes.
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Get the individual process ID.
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    std::cout << "Processeur " << processor_name << " ID = " << id << " bienvenue en INF442 !" << std::endl;

    //Compute an array with the right tuples for each processor

        //Convert relation to array ? sort
        //tell the set used to join

    //Scatter the tuples to processors



    //Receive and make the join





    //Reduce to get only one joint relation











    // Terminate MPI.
    MPI_Finalize();

    return 0;

}
