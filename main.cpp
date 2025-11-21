#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::vector;

class Banker {
public:
    Banker(std::string file) { 
        openFile(file); // Opens the file
        // parseFile();    // Gets the variables
        // closeFile();
     }

    void openFile(const std::string& fileName);
    // void parseFile();

    // Getters
    std::ifstream& getFile() { return file_; };
    vector<vector<int>> getAllocation() const { return allocation_; }
    vector<vector<int>> getMax()        const { return max_; }
    vector<int>         getAvailable()  const { return available_; }

private:
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

// void Banker::parseFile();

int main() {
    
    // Opens file as the bank on run
    Banker bank("input-file.txt");
    std::ifstream& file = bank.getFile();
    
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}