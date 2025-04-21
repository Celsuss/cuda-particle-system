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
add_executable(particle_simulator
  src/main.cpp
  src/particle.cpp
  src/simulator.cpp
  src/renderer.cpp
  kernels/particle_kernels.cu
)

# Set the CUDA architectures property for the target
set_target_properties(particle_simulator PROPERTIES
  CUDA_ARCHITECTURES 86  # For RTX 4070 Ti
)

# Link libraries
target_link_libraries(particle_simulator
  PRIVATE
  CUDA::cudart
  OpenGL::GL
  glfw
  GLEW::GLEW
)


# enable_testing()
