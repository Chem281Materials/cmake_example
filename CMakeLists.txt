cmake_minimum_required(VERSION 3.15)

set(SimpleMPI_USE_MPI "DEFAULT" CACHE STRING "String to indicate whether to use MPI (ON, OFF, DEFAULT)")

# Project name and version
project(SimpleMPI VERSION 1.0.0
  DESCRIPTION "Simple example of using MPI"
  LANGUAGES CXX
)

add_executable(simplempi src/main.cpp
  src/mpiwrapper/mpiwrapper.cpp)

target_compile_features(simplempi PUBLIC cxx_std_11)

target_include_directories(simplempi PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mpiwrapper)

# Find and link against MPI
if ( SimpleMPI_USE_MPI STREQUAL "ON" )
  find_package(MPI REQUIRED)
elseif ( SimpleMPI_USE_MPI STREQUAL "OFF" )
elseif ( SimpleMPI_USE_MPI STREQUAL "DEFAULT" )
  find_package(MPI)
else()
  message(FATAL_ERROR "Unrecognized value of SimpleMPI_USE_MPI" )
endif()
if ( MPI_FOUND )
  target_link_libraries(simplempi PUBLIC MPI::MPI_CXX)
  target_compile_definitions(simplempi PUBLIC __use_mpi=1)
else()
  message(WARNING "MPI was not found. Disabling MPI support.")
endif()
