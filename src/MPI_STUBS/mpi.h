#ifndef MPI_STUBS
#define MPI_STUBS

#define MPI_COMM_WORLD 0

typedef int MPI_Comm;

int MPI_Init( int *argc, char ***argv ) { return 0; }
int MPI_Finalize(void) { return 0; }
int MPI_Comm_rank( MPI_Comm comm, int *rank ) { *rank = 0; return 0; }
int MPI_Comm_size( MPI_Comm comm, int *size ) { *size = 0; return 0; }

#endif
