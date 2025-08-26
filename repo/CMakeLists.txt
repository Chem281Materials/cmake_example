cmake_minimum_required(VERSION 3.15)

# Project name and version
project(SimpleMPI VERSION 1.0.0
  DESCRIPTION "Simple example of using MPI"
  LANGUAGES CXX
)

add_executable(simplempi src/main.cpp)

target_compile_features(simplempi PUBLIC cxx_std_11)

# Find and link against the MPIWrapper library
find_package(MPIWrapper 1.0 REQUIRED)
target_link_libraries(simplempi PUBLIC MPIWrapper::MPIWrapper)
