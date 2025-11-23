
#ifndef BANKER_HPP_
#define BANKER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;

class Banker {
public:
    Banker(std::string file) { 
        openFile(file); // Opens the file
        parseFile();    // Gets the variables
        getNeed();      // Finds the need
        safeState_ ={}; // Makes sure safe state is empty
        closeFile();    // Closes the file
    }

    void print() const;
    bool bankersAlgorithm();

    void openFile(const std::string& fileName);
    void parseFile();
    void getNeed();
    void closeFile();
    
    bool allocatable(int, vector<int>&) const;
    vector<int> getSafeState() {
        if (safeState_.empty()) { bankersAlgorithm(); }
        return safeState_;
    }

private:

    vector<vector<int>> allocation_;
    vector<vector<int>> max_;
    vector<vector<int>> need_;

    vector<int> available_;
    vector<int> safeState_;

    std::ifstream file_;
};

#endif