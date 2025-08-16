cmake_minimum_required(VERSION 3.15)

# Project name and version
project(SimpleMPI VERSION 1.0.0
  DESCRIPTION "Simple example of using MPI"
  LANGUAGES CXX
)

add_executable(simplempi src/main.cpp)

target_compile_features(simplempi PUBLIC cxx_std_11)

# Find and link against MPI
find_package(MPI)
if ( MPI_FOUND )
  target_link_libraries(simplempi PUBLIC MPI::MPI_CXX)
else()
  message(WARNING "MPI was not found. Disabling MPI support.")
  target_include_directories(simplempi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/MPI_STUBS)
endif()
