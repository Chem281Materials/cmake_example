#include <iostream>
#include <dlfcn.h>

int main(int argc, char** argv) {
  void* lib_handle = dlopen("/work/librepo/build/libMPIWrapper.so", RTLD_LAZY);
  if ( !lib_handle ) {
    std::cerr << "dlopen failed: " << dlerror() << '\n';
    return 1;
  }

  typedef int(*mp_init_t)(int*, char***);
  mp_init_t mp_init;
  mp_init = (mp_init_t) (intptr_t) dlsym(lib_handle, "mp_init");
  if ( !mp_init ) {
    std::cerr << "dlsym failed: " << dlerror() << '\n';
    return 2;
  }

  typedef int(*mp_finalize_t)();
  mp_finalize_t mp_finalize;
  mp_finalize = (mp_finalize_t) (intptr_t) dlsym(lib_handle, "mp_finalize");
  if ( !mp_finalize ) {
    std::cerr << "dlsym failed: " << dlerror() << '\n';
    return 2;
  }

  typedef int(*mp_comm_rank_t)(int*);
  mp_comm_rank_t mp_comm_rank;
  mp_comm_rank = (mp_comm_rank_t) (intptr_t) dlsym(lib_handle, "mp_comm_rank");
  if ( !mp_comm_rank ) {
    std::cerr << "dlsym failed: " << dlerror() << '\n';
    return 2;
  }

  typedef int(*mp_comm_size_t)(int*);
  mp_comm_size_t mp_comm_size;
  mp_comm_size = (mp_comm_size_t) (intptr_t) dlsym(lib_handle, "mp_comm_size");
  if ( !mp_comm_size ) {
    std::cerr << "dlsym failed: " << dlerror() << '\n';
    return 2;
  }

  mp_init(&argc, &argv);

  int world_size;
  mp_comm_size(&world_size);

  int world_rank;
  mp_comm_rank(&world_rank);

  if (world_rank == 0) {
    std::cout << "World size: " << world_size << std::endl;
  }

  mp_finalize();

  return 0;
}
