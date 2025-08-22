#ifndef mpiwrapper
#define mpiwrapper

#ifdef __use_mpi

#include<mpi.h>

#else

#define MPI_COMM_WORLD 0
typedef int MPI_Comm;

#endif

int mp_init( int *argc, char ***argv );
int mp_finalize(void);
int mp_comm_rank( MPI_Comm comm, int *rank );
int mp_comm_size( MPI_Comm comm, int *size );

#endif
