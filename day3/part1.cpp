#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    size_t joltage = 0;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            std::string sub1 = line.substr(0, line.length() - 1);
            size_t sub1_max = 0;
            size_t sub1_max_idx = 0;
            for (size_t i = 0; i < sub1.length(); ++i) {
                size_t value = sub1[i] - '0';
                assert(value >= 1 && value <= 9);
                if (value > sub1_max) {
                    sub1_max = value;
                    sub1_max_idx = i;
                }
            }
            std::string sub2 = line.substr(sub1_max_idx + 1);
            size_t sub2_max = 0;
            size_t sub2_max_idx = 0;
            for (size_t i = 0; i < sub2.length(); ++i) {
                size_t value = sub2[i] - '0';
                assert(value >= 1 && value <= 9);
                if (value > sub2_max) sub2_max = value;
            }
            // std::cout << "Joltage for " << line << " is " << sub1_max << sub2_max << std::endl;
            joltage += 10 * sub1_max + sub2_max;
        }
    }
    std::cout << joltage << std::endl;

    return 0;
}
