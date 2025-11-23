
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

### Make File - `Makefile`
```Makefile
COMPILER = g++
COMPILERFLAGS = -std=c++17
```
Chooses the compiler and the version of C++ to run. Here it chooses C++17.

```
TARGETS = a.out
```
Chooses the target file that the final executable will be named.
Here I chose `a.out` as the final file name.

```
# SETUP
all: run
```
Decides what will be run when the uses types `make`

```
run: $(TARGETS)
	./a.out
```
The run command will do `./a.out`

```
$(TARGETS): main.o banker.o
	$(COMPILER) $(COMPILERFLAGS) -o a.out main.o banker.o
```
Links the object files together. These files are `main.o` and `banker.o`. These are what is links to `a.out`.

```
main.o: main.cpp
	$(COMPILER) $(COMPILERFLAGS) -c main.cpp

banker.o: banker.cpp
	$(COMPILER) $(COMPILERFLAGS) -c banker.cpp
```
Compiles the `main.o` file and the `banker.o` file together.

```
clean:
	rm -f *.o $(TARGETS)
```
Here it removes all `.o` files and the selected `a.out` file to clean the system.
This can be run by doing `make clean` in the terminal.

### Banker Header File - `banker.hpp`
```cpp
#ifndef BANKER_HPP_
#define BANKER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
```
This includes all of the headers that the program will be using.
It uses:
`iostream` for output to the terminal
`fstream` for the ability to read and write to files
`string` to use `std::string` and features of strings
`vector` for `std::vector` and `.push_back()` for the vectors

```cpp
using std::vector;
```
This allows for the user of `std::vector` without the `std::`

```cpp
class Banker {
```
Begins the `Banker` class. This class is where all variables and functions for this project are stored.

```cpp
public:
    Banker(std::string file) { 
        openFile(file); // Opens the file
        parseFile();    // Gets the variables
        getNeed();      // Finds the need
        safeState_ ={}; // Makes sure safe state is empty
        closeFile();    // Closes the file
    }
```
The constructor opens the file, then parses it which gets the data from the file and assigns it to private variables. Then it finds the need for each process. Then it initializes the safe state variable to empty. After that it closes the file as it is done using it.

```cpp
    void print() const;
    bool bankersAlgorithm();

    void openFile(const std::string& fileName);
    void parseFile();
    void getNeed();
    void closeFile();
    
    bool allocatable(int, vector<int>&) const;
```
Here the program declares a lot of member functions.
These functions will all be explained later.
```cpp
    vector<int> getSafeState() {
        if (safeState_.empty()) { bankersAlgorithm(); }
        return safeState_;
    }
```
This function checks if the user has already run and created the safe state vector. If it has not it runs the bankers algorithm function.
It then returns the correct safe state vector.

```cpp
private:

    vector<vector<int>> allocation_;
    vector<vector<int>> max_;
    vector<vector<int>> need_;

    vector<int> available_;
    vector<int> safeState_;

    std::ifstream file_;
};
```
These are the member variables used in the program.

```cpp
#endif
```
This ends the `#ifndef` statement to define everything needed in the header file.
The input file is formatted in a way where each different group is titled with three dashes at the beginning. This if statement detects if the program is going to experience a mode change.