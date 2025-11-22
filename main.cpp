#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;

class Banker {
public:
    Banker(std::string file) { 
        openFile(file); // Opens the file
        parseFile();    // Gets the variables
        getNeed();      // Finds the need
        closeFile();    // Closes the file
     }

    void print() const;
    bool bankersAlgorithm() const;

    void openFile(const std::string& fileName);
    void parseFile();
    void getNeed();
    void closeFile();

    // bool allocatable(int rowIdex) const;

private:

    vector<vector<int>> allocation_;
    vector<vector<int>> max_;
    vector<int> available_;
    
    vector<vector<int>> need_;

    std::ifstream file_;
};

void Banker::openFile(const std::string& fileName) {
    // Opens the file
    file_.open(fileName);

    // Makes sure the file opened properly
    if (!file_.is_open()) {
        std::cout << "\033[31m"; // Makes the text red
        std::cout << "ERROR : File is not opening." << std::endl;
    } else {
        std::cout << "\033[32m"; // Makes th text green
        std::cout << "File opened!" << std::endl;
    }
    std::cout << "\033[37m"; // Reset text color back to white
}
void Banker::closeFile() {
    if (file_.is_open()) {
        file_.close();
        std::cout << "\033[32m"; // Makes th text green
        std::cout << "File closed!" << std::endl;
        std::cout << "\033[37m"; // Reset text color back to white
    }
}
void Banker::parseFile() {

    // Parse Mode
    enum class PM { none, allocation, max, available };
    PM mode = PM::none;

    std::string line;
    while (std::getline(file_, line)) {
        if (line.empty()) continue;

        // Change the mode if necessary
        if (line.find("---") != std::string::npos) { 

            // Sets the mode based on line
            if (line.find("allocation") != std::string::npos) {
                mode = PM::allocation;
            } else if (line.find("max") != std::string::npos) {
                mode = PM::max;
            } else if (line.find("available") != std::string::npos) {
                mode = PM::available;
            }
        } else {
            // Sets the vector based on the mode

            // Makes the vector
            // Subtracts 48 to make it a proper number
            vector<int> vec = {
                line[0] - 48,
                line[3] - 48,
                line[6] - 48
            };

            // Based on the mode add to the vector
            if (mode == PM::allocation) allocation_.push_back(vec);
            if (mode == PM::max)        max_.push_back(vec);
            if (mode == PM::available)  available_ = vec;
        }
    }
}
void Banker::print() const {
    std::cout << "     Alloc |  Max  | Avail" << std::endl;
    std::cout << "     ----- | ----- | -----" << std::endl;
    std::cout << "     A B C | A B C | A B C" << std::endl;
    std::cout << "     ----- | ----- | -----" << std::endl;

    for (int y=0; y<allocation_.size(); ++y) {
        std::cout << "P" << y << " | ";

        // Prints off allocation
        for (int x=0; x<3; ++x) {
            std::cout << allocation_[y][x] << " ";
        }

        std::cout << "| "; // Spacing

        // Prints off Max row
        for (int x=0; x<3; ++x) {
            std::cout << max_[y][x] << " ";
        }
        
        std::cout << "| "; // Spacing

        // There is only one line for available
        if (y==0) {
            for (int x=0; x<3; ++x) {
                std::cout << available_[x] << " " ;
            }
        };
        std::cout << std::endl;
    }
}
void Banker::getNeed() { 
    // Iterates through all values in allocation and max
    for (int y=0; y<allocation_.size(); ++y) {
        vector<int> processNeed; // Row
        for (int x=0; x<allocation_[y].size(); ++x) {
            // Get new need value
            int newNeed = max_[y][x] - allocation_[y][x];
            // Add value the row
            processNeed.push_back(newNeed);
        }
        // Add row to list
        need_.push_back(processNeed);
    }
    return need_;
}
// bool Banker::allocatable(int rowIdex) const {

// }
bool Banker::bankersAlgorithm() const { 

    // Makes sure allocation and max have same length
    if (allocation_.size() != max_.size()) return false;
    return true;   
}

int main() {
    
    // Opens file as the bank on run
    Banker bank("input-file.txt");
    bank.print();
    bool safe = bank.bankersAlgorithm();
    if (safe) std::cout << "System in safe state" << std::endl;
    else std::cout << "System NOT in safe state" << std::endl;

}