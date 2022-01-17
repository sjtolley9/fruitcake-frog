# Build Project

This project requires Conan (https://docs.conan.io/en/latest/installation.html) and CMake. To build the project for Linux, run:

```
mkdir build && cd build
conan install ..

cmake .. -G "Unix Makefiles"
cd ..
./play.sh
```
