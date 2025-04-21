cmake_minimum_required(VERSION 3.31)

# Project name and supported languages
project(cuda-particle-system
  VERSION 1.0
  LANGUAGES CXX CUDA)

# Enable CUDA as a language
enable_language(CUDA)


# Set C++ Standard
# set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)


# Find required packages
find_package(CUDAToolkit REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

# Add include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${OpenGL_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -arch=sm_86 --use_fast_math -O3")
set(CMAKE_CXX_FLAGS "-g --std=c++17")

# Add executable
## Explicitly add files, use for prod
# add_executable(cuda-particle-system
#   src/main.cpp
#   src/particle.cpp
#   src/simulator.cpp
#   src/renderer.cpp
#   kernels/particle_kernels.cu
# )
## Automaticly add files, don't use for prod
### Automatically find all source files
file(GLOB_RECURSE CPP_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE CUDA_SOURCES "${CMAKE_SOURCE_DIR}/kernels/*.cu")

### Print found files (optional, for debugging)
message(STATUS "Found C++ files: ${CPP_SOURCES}")
message(STATUS "Found CUDA files: ${CUDA_SOURCES}")

### Add executable with automatically discovered files
add_executable(cuda-particle-system
  ${CPP_SOURCES}
  ${CUDA_SOURCES}
)


# Set the CUDA architectures property for the target
set_target_properties(cuda-particle-system PROPERTIES
  CUDA_ARCHITECTURES 86  # For RTX 4070 Ti
)

# Link libraries
target_link_libraries(cuda-particle-system
  PRIVATE
  CUDA::cudart
  OpenGL::GL
  glfw
  GLEW::GLEW
)


# enable_testing()
