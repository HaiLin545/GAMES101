# GAMES101

GAMES101 assignments finished by hailin (as you know, a boring boy)

## 环境准备

-   操作系统：兼容了 windows 和 linux(ubuntu) ，其他 os 不清楚
-   编译工具：cmake 和 g++ (MinGW)

### 需要安装的第三方依赖

为了方便，将依赖安装在根目录的 lib 下统一存放。安装时先请将${path_to_repo}替换为本地仓库目录。

#### 1. Eigen3

1. [下载源代码](https://gitlab.com/libeigen/eigen/-/releases/3.4.0)并且解压缩
2. 在 Eigen3 源码目录下，构建源码

    ```cmd
    mkdir build && cd build
    cmake -G "MinGW Makefiles" .. \
          -D CMAKE_INSTALL_PREFIX=${path_to_repo}/lib/eigen3
    make install -j 8
    ```

#### 2. opencv

1. [下载源码](https://github.com/opencv/opencv/releases/tag/4.8.0)并且解压缩，或者 git clone（速度慢）
2. 在 opencv 源码目录下，构建源码
    ```cmd
    mkdir build && cd build
    cmake -G "MinGW Makefiles" .. \
          -D CMAKE_INSTALL_PREFIX=${path_to_repo}/lib/opencv
    make install -j 8
    ```
3. （仅 windows 下需要）添加环境变量${path_to_repo}/lib/opencv/x64/mingw/bin

## 跑作业代码

_Take work0 as example_

```cmd
cd work0 && mkdir build
cmake -G "MinGW Makefiles" ..
cmake --build .
.\Transformation.exe
```
