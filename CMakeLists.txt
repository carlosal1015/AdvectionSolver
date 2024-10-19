cmake_minimum_required(VERSION 3.30.3)
project("AdvectionSolver"
  VERSION 1.0
  DESCRIPTION "A simple C++ advection solver based on michaelschoellhorn/AdvectionSolver"
  LANGUAGES CXX)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds are not allowed")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "icpx") # g++ clang++
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_HOST_SYSTEM_NAME Linux) # Windows
set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE) # Ninja
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsycl -std=c++20")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lOpenCL -lsycl")

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
