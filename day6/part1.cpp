#include <cstddef>
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    std::vector<std::vector<size_t>> rows;
    std::vector<char> operations;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            if (line.empty()) break;
            bool numbers = true;
            for (char c : line) {
                if (c == '*' || c == '+') {
                    numbers = false;
                    operations.push_back(c);
                }
            }
            if (numbers) {
                std::istringstream iss(line);
                std::vector<size_t> things;
                std::string thing;
                while (iss >> thing) {
                    things.push_back(std::stoll(thing));
                }
                rows.push_back(things);
            }
        }
    }


    for (size_t i = 0; i < rows.size(); ++i) {
        assert(rows[i].size() == operations.size());
    }
    size_t total = 0;
    for (size_t j = 0; j < operations.size(); ++j) {
        std::cout << "Operation: ";
        size_t local;
        if (operations[j] == '+') local = 0;
        else local = 1;
        for (const std::vector<size_t>& row : rows) {
            std::cout << row[j] << " " << operations[j] << " ";
            if (operations[j] == '+') local += row[j];
            else local *= row[j];
        }
        total += local;
        std::cout << std::endl;
    }
    std::cout << total << std::endl;

    return 0;
}
