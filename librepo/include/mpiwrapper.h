#ifndef mpiwrapper
#define mpiwrapper

#ifdef __use_mpi
#include<mpi.h>
#endif

int mp_init( int *argc, char ***argv );
int mp_finalize(void);
int mp_comm_rank( int *rank );
int mp_comm_size( int *size );

#endif
