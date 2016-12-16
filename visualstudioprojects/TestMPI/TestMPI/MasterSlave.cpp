#include <stdio.h>
#include <string.h>
#include "mpi.h"

int master_io(MPI_Comm, int) ;
int slave_io(MPI_Comm, int) ;

// Split a communicator for slave processes from WORLD communicator.
// Only master process in the WORLD will do I/O to the external.
void masterSlave(void)
{
    int rank, size;
    MPI_Comm new_comm;

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_split( MPI_COMM_WORLD, rank == 0, 0, &new_comm );
    if (rank == 0) 
	master_io( MPI_COMM_WORLD, new_comm );
    else
	slave_io( MPI_COMM_WORLD, new_comm );

    return ;
}

/* This is the master */
int master_io(MPI_Comm master_comm, int comm )
{
    int        i,j, size;
    char       buf[256];
    MPI_Status status;

    MPI_Comm_size( master_comm, &size );
    for (j=1; j<=2; j++) {
		for (i=1; i<size; i++) {
			MPI_Recv( buf, 256, MPI_CHAR, i, 0, master_comm, &status );   //receive in master communicator
			fputs( buf, stdout );
		}
    }
	return 0 ;
}

/* This is the slave */
int slave_io( MPI_Comm master_comm, int comm )
{
    char buf[256];
    int  rank;
    
    MPI_Comm_rank( comm, &rank );           // rank in the split communicator
    sprintf( buf, "Hello from slave %d\n", rank );
    MPI_Send( buf, strlen(buf) + 1, MPI_CHAR, 0, 0, master_comm );     // send to master communicator
    
    sprintf( buf, "Goodbye from slave %d\n", rank );
    MPI_Send( buf, strlen(buf) + 1, MPI_CHAR, 0, 0, master_comm );     // send to master communicator

    return 0;
}
