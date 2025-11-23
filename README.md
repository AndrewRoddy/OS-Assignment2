
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
This is a very strict input file format. Only the integer values can be modified as everything else must stay the same. The user must guarantee this format is followed.
The `---` explain what type of value is below for easy understanding from just looking at the input file
# Program Description
### Bankers Algorithm
The system is in a safe state. The safe sequence is P3 -> P4 -> P1 -> P2 -> P0.

The bankers algorithm can be used by operating systems to avoid deadlock. The algorithm keeps track of the available resources in the system and allocates them to make sure the system does not run out of resources an enter deadlock. It makes sure that the system never leaves a safe state by granting resources. It makes sure there is at least one execution order so all processes can finish without entering deadlock.

It first calculates the need matrix by subtracting the allocation matrix from the max matrix. It then looks for a process that hasn't been tested yet and checks if the need is less than or equal to the currently available. If need is less than or equal to available then it adds the allocation to the available. It keeps repeating this until either no more processes can be selected and deadlock is possible or all processes are in a safe sequence. If all processes are in a safe sequence then it can return true.