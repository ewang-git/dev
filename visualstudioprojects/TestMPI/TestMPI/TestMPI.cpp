// TestMPI.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"


#include <cassert>
#include <mpi.h>
#include <iostream>


void firstExercise(void) ;
void testMPICH2(void) ;
void sharingData(void) ;
void sharingData2(void) ;
void sharingDataPack(void) ;
void masterSlave(void) ;

int main(int argc, char* argv[])
{
  int rc ;
  
  rc = MPI_Init(&argc, &argv);

  assert (rc == MPI_SUCCESS) ;

//  testMPICH2() ;
//  firstExercise() ;
//  sharingData() ;
//  sharingData2() ;
//    sharingDataPack() ;
    masterSlave() ;
  
  MPI_Finalize();

  return 0;
} 
void testMPICH2()
{
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    int value = 17;
    int result = MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    if (result == MPI_SUCCESS)
      std::cout << "Rank 0 OK!" << std::endl;
  } else if (rank == 1) {
    int value;
    int result = MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
			  MPI_STATUS_IGNORE);
    if (result == MPI_SUCCESS && value == 17)
      std::cout << "Rank 1 OK!" << std::endl;
  }
}


void firstExercise()
{
    int rank, size;

    MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    printf( "Hello world from process %d of %d\n", rank, size );

}

// broadcast a number to all processes and echo the number to the terminal
void sharingData()
{
    int rank, value;

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    do {
		if (rank == 0) {
			printf("Enter an int ( a negative number to terminate)\n") ;
			fflush( stdout );
		    scanf( "%d", &value );       // get user's input from process 0 only
		}

	MPI_Bcast( &value, 1, MPI_INT, 0, MPI_COMM_WORLD );
	
	printf( "Process %d got %d\n", rank, value );
	fflush( stdout );
    } while (value >= 0);

}

//broadcast two numbers (int and double) to all processes and echo the numbers to the terminal
void sharingData2()
{
    int          rank;
    struct { int a; double b ;} value;
    MPI_Datatype mystruct;
    int          blocklens[2];
    MPI_Aint     indices[2];
    MPI_Datatype old_types[2];

    // rank identify who am I in the communicator, can see it as process id in the communicator
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    /* One value of each type */
    blocklens[0] = 1;
    blocklens[1] = 1;
    /* The base types */
    old_types[0] = MPI_INT;
    old_types[1] = MPI_DOUBLE;
    /* The locations of each element */
    MPI_Address( &value.a, &indices[0] );
    MPI_Address( &value.b, &indices[1] );
    /* Make relative */
    indices[1] = indices[1] - indices[0];
    indices[0] = 0;

	// create the mystruct object
	// MPI_Type_struct (numberOfBlocks (int), numberOfElementsInEachBlock (array), byteOffsetOfEachBlock (array), typeOfElementsInEachBlock) ;
    MPI_Type_struct( 2, blocklens, indices, old_types, &mystruct );
    MPI_Type_commit( &mystruct );

    do {
		if (rank == 0) {
			printf("Enter an int and a double ( a negative number to terminate)\n") ;
			fflush( stdout );
			scanf( "%d %lf", &value.a, &value.b );
		}

	MPI_Bcast( &value, 1, mystruct, 0, MPI_COMM_WORLD );   // The "value" variable is logically shared by all processes!!!! (distributed shared memory)
	
	printf( "Process %d got %d and %f\n", rank, value.a, value.b );
	fflush(stdout) ;
    } while (value.a >= 0);

    /* Clean up the type */
    MPI_Type_free( &mystruct );

}

// read one int and one double numbers. pack the data into char[] and broadcast to all processes.
void sharingDataPack()
{
	int          rank;
    int          packsize, position;
    int          a;
    double       b;
    char         packbuf[100];


	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

    do {
	if (rank == 0) {
		printf("Enter an int and a double ( a negative number to terminate)\n") ;
		fflush( stdout );
	    scanf( "%d %lf", &a, &b );
	    packsize = 0;
	    MPI_Pack( &a, 1, MPI_INT, packbuf, 100, &packsize, 
		      MPI_COMM_WORLD );
	    MPI_Pack( &b, 1, MPI_DOUBLE, packbuf, 100, &packsize, 
		      MPI_COMM_WORLD );
	}
	MPI_Bcast( &packsize, 1, MPI_INT, 0, MPI_COMM_WORLD );
	MPI_Bcast( packbuf, packsize, MPI_PACKED, 0, MPI_COMM_WORLD );
	if (rank != 0) {
	    position = 0;
	    MPI_Unpack( packbuf, packsize, &position, &a, 1, MPI_INT, 
			MPI_COMM_WORLD );
	    MPI_Unpack( packbuf, packsize, &position, &b, 1, MPI_DOUBLE,
			MPI_COMM_WORLD );
	}
	
	printf( "Process %d got %d and %f\n", rank, a, b );
	fflush( stdout );
    } while (a >= 0);

}