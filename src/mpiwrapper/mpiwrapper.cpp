#include "mpiwrapper.h"

int mp_init( int *argc, char ***argv ) {
#ifdef __use_mpi
  return MPI_Init(argc, argv);
#else
  return 0;
#endif
}

int mp_finalize(void) {
#ifdef __use_mpi
  return MPI_Finalize();
#else
  return 0;
#endif
}

int mp_comm_rank( MPI_Comm comm, int *rank ) {
#ifdef __use_mpi
  return MPI_Comm_rank(comm, rank);
#else
  *rank = 0;
  return 0;
#endif
}

int mp_comm_size( MPI_Comm comm, int *size ) {
#ifdef __use_mpi
  return MPI_Comm_size(comm, size);
#else
  *size = 0;
  return 0;
#endif
}
