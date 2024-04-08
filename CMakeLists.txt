cmake_minimum_required(VERSION 3.20.0)
project("AdvectionSolver"
  VERSION 1.0
  DESCRIPTION "A simple C++ advection solver based on michaelschoellhorn/AdvectionSolver"
  LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(createDist createDist.cc)

add_executable(AdvSolv main.cc
  src/fluxes.cc
  src/loadData.cc
  src/simulation.cc)
target_include_directories(AdvSolv PUBLIC "include")

add_custom_command(TARGET createDist
  POST_BUILD
  COMMAND createDist
)

# add_custom_command(TARGET AdvSolv
#   POST_BUILD
#   COMMAND AdvSolv
# )
# # add_custom_target(bar DEPENDS createDist)
# add_dependencies(two one)