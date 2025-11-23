#include "banker.hpp"

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
}
bool Banker::allocatable(int rowIndex, vector<int>& nowAvailable) const {
    // If need is ever greater than now available cannot allocate
    for (int x=0; x<nowAvailable.size(); ++x) {
        if (need_[rowIndex][x] > nowAvailable[x]) { return false; }
    }
    return true; // If need is never greater than now available
}
bool Banker::bankersAlgorithm() { 
    safeState_.clear(); // Makes sure safe state is empty

    int size = allocation_.size();
    // Makes sure allocation and max have same length
    if (size != max_.size()) return false;
    // Vector of if its tested or not
    vector<bool> tested(size, false);

    // Temporary copy of available_ to be edited
    vector<int> currentlyAvailable = available_;
    bool safe;
    int processesDone = 0;

    while (processesDone < size) {
        safe = false;
        for (int x=0; x<size; ++x) {
            if (tested[x]) continue; // If process already tested then skip
            if (allocatable(x, currentlyAvailable)) {
                // iterate through row
                for (int y=0; y<allocation_[0].size(); ++y) {
                    currentlyAvailable[y] += allocation_[x][y];
                } 
                
                tested[x] = true;
                safe = true;

                safeState_.push_back(x);
                processesDone++;
            }
        }
        if (!safe) return false;
    }
    return true;   
}
