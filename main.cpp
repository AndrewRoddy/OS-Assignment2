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
        closeFile();    // Closes the file
     }

    void print() const;

    // Getters
    std::ifstream& getFile() { return file_; };
    vector<vector<int>> getAllocation() const { return allocation_; }
    vector<vector<int>> getMax()        const { return max_; }
    vector<int>         getAvailable()  const { return available_; }

private:
    void openFile(const std::string& fileName);
    void parseFile();
    void closeFile();

    vector<vector<int>> allocation_;
    vector<vector<int>> max_;
    vector<int> available_;
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

// void Banker::print() const {

// }

int main() {
    
    // Opens file as the bank on run
    Banker bank("input-file.txt");
    // bank.print();

}