# GAMES101
GAMES101 assignments finished by hailin (as you know, a boring boy)


## Enviroment
1. Platform: **Window**（linux/mac may not work）
2. Compile: **CMake with g++(MinGW)**

## Eigen3
_This repo already contain Eigen3.4.0, you can just ignore this step_.
1. Download [Eigen3](https://gitlab.com/libeigen/eigen/-/releases/3.4.0)
2. Build Eigen3
    ```cmd
    cd eigen3
    mkdir build
    cd build
    cmake -G "MinGW Makefiles" .. \ 
          -D CMAKE_INSTALL_PREFIX=${path_to_GAMES101}/Eigen3
    make install
    ```

## Compile and Run the code

_Take work0 as example_

```cmd
cd work0
mkdir build
cmake -G "MinGW Makefiles" ..
cmake --build .
.\Transformation.exe
```