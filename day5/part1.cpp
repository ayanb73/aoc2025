#include <string>
#include <iostream>
#include <fstream>

#include "interval_tree.hpp"

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    IntervalTree t;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty()) break;
            size_t dash = line.find('-');
            size_t min = std::stoll(line.substr(0, dash));
            size_t max = std::stoll(line.substr(dash + 1));
            if (min > max) {
                std::swap(min, max);
            }
            t.insert(min, max);
            //t.print();
        }
        int fresh = 0;
        while (std::getline(input_file, line)) {
            bool is_fresh = t.contains(std::stoll(line));
            if (is_fresh) {
                fresh++;
            }
        }
        std::cout << fresh << std::endl;
    }

    return 0;
}
