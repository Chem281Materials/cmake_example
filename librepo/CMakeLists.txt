cmake_minimum_required(VERSION 3.15)

set(MPIWrapper_USE_MPI "DEFAULT" CACHE STRING "String to indicate whether to use MPI (ON, OFF, DEFAULT)")

# Project name and version
project(MPIWrapper VERSION 1.0.0
  DESCRIPTION "Wrapper for MPI libraries"
  LANGUAGES CXX
)

add_library(MPIWrapper)

add_library(MPIWrapper::MPIWrapper ALIAS MPIWrapper)

target_sources(MPIWrapper
  PRIVATE src/mpiwrapper.cpp)

set_target_properties(
  MPIWrapper
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR})

target_compile_features(MPIWrapper PUBLIC cxx_std_11)

target_include_directories(
  MPIWrapper
  PRIVATE src
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Find and link against MPI
if ( MPIWrapper_USE_MPI STREQUAL "ON" )
  find_package(MPI REQUIRED)
elseif ( MPIWrapper_USE_MPI STREQUAL "OFF" )
elseif ( MPIWrapper_USE_MPI STREQUAL "DEFAULT" )
  find_package(MPI)
else()
  message(FATAL_ERROR "Unrecognized value of SimpleMPI_USE_MPI" )
endif()
if ( MPI_FOUND )
  target_link_libraries(MPIWrapper PRIVATE MPI::MPI_CXX)
  target_compile_definitions(MPIWrapper PRIVATE __use_mpi=1)
else()
  message(WARNING "MPI was not found. Disabling MPI support.")
endif()




#######################################
# BEGIN INSTALL SECTION
#######################################

include(GNUInstallDirs)

install(TARGETS MPIWrapper
        EXPORT MPIWrapperTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/MPIWrapperConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper)

write_basic_package_version_file(
  "MPIWrapperConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/MPIWrapperConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper)

install(
  EXPORT MPIWrapperTargets
  FILE MPIWrapperTargets.cmake
  NAMESPACE MPIWrapper::
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MPIWrapper)
