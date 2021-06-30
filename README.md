This is HTMLQuery, a multithreaded program to perform queries on url responses.

### How to build

To configure the project, from the project root:
```
mkdir build
cmake -S . -B build/ -DCMAKE_TOOLCHAIN_FILE=lib/scripts/buildsystems/vcpkg.cmake
```
![Configure gif](img/configure.gif)


Once the project is configured, build it using:
```
cmake --build build
```
![Configure gif](img/build.gif)

### Usage

Once build, you can launch the process from the build folder with the path to a text file and number of threads.

