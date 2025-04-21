# cuda-particle-system

## TODO
### Read about generate compile file for clangd using cmake
https://clangd.llvm.org/installation

## Build system
``` bash
    cd build/
    cmake ..
    make
    ./cuda-particle-system
```
### With clang support
``` bash
    cd build/
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1
    ln -s compile_commands.json ../src/
    make
    ./cuda-particle-system
```

## Install cuda toolset
### Arch linux
Install cuda toolset.
``` bash
`sudo pacman -S cuda cuda-gbd nvidia-utils opencl-nvidia glfw-x11 glew glm``

## Verify Your Installation
After installation, verify that CUDA is correctly set up:
``` bash
`nvcc --version``
