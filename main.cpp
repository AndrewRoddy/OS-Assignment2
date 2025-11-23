#include "banker.hpp"

int main() {
    
    // Opens file as the bank on run
    Banker bank("input-file.txt");
    bank.print();
    bool safe = bank.bankersAlgorithm();

    if (safe) {
        std::cout << "System in safe state" << std::endl;
        vector<int> order = bank.getSafeState();
        for (int i=0; i < order.size(); ++i) {
            if (i!=0)std::cout << " -> ";
            std::cout << "P" << order[i];
        }
        std::cout << std::endl;

    } else {
        std::cout << "System NOT in safe state" << std::endl;
    }

    return 0;
}
