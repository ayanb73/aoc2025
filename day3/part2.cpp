#include <string>
#include <iostream>
#include <fstream>

/**
 * For a string of integers 1 to 9, determine the largest
 * 12 digit integer that can be formed by selecting digits
 * left to right.
 */
size_t twelve_battery(std::string& line) {
    size_t joltage = 0;
    size_t prev = 0;
    for (int j = 11; j >= 0; --j) {
        size_t end_idx = line.length() - j;
        size_t max = 0;
        for (int i = prev; i < end_idx; ++i) {
            size_t value = line[i] - '0';
            if (value > max) {
                max = value;
                prev = i;
            }
        }
        joltage += max * pow(10, j);
        prev += 1;
    }
    return joltage;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    size_t joltage = 0;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            joltage += twelve_battery(line);
        }
    }
    std::cout << joltage << std::endl;

    return 0;
}
