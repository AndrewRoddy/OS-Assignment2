
# Operating Systems Assignment 2

# **Usage Instructions**
Run on a Linux or Unix system. 
Run using these commands.
```cpp
g++ main.cpp banker.cpp
./a.out
```
This also uses the GNU C++ Compiler for `g++` using C++17 or later.

As a `Makefile` is included the user can use `make` to run the program and `make clean` to clean up the binaries after running the program.
```
make
make clean
```

### Input File Format - `input-file.txt`
```
---allocation
0, 1, 0,
2, 0, 0,
3, 0, 2,
2, 2, 1,
0, 0, 2,
---max
7, 5, 3,
3, 3, 2,
9, 0, 2,
2, 2, 2,
4, 3, 3,
---available
3, 2, 2,
```