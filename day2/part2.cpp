#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

uint8_t num_digits(size_t num) {
    size_t count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

/**
 * Calculate the sum of all numbers in the range [min, max] that have a repeated sequence of
 * any length of digits.
 */
size_t range_repeats_sum(size_t min, size_t max) {
    size_t sum = 0;
    for (size_t i = min; i <= max; ++i) {
        uint8_t dig_i = num_digits(i);
        if (dig_i == 1) continue;

        for (int j = 1; j <= 5; ++j) {
            if (dig_i % j == 0) {
                size_t divisor = 0;
                uint8_t tmp = 0;
                while (tmp < dig_i) {
                    divisor += pow(10, tmp);
                    tmp += j;
                }
                if (divisor == 1) break;
                if (i % divisor == 0) {
                    sum += i;
                    break;
                }
            }
        }
    }
    return sum;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    size_t pos = 0;
    size_t comma = 0;
    size_t sum = 0;
    if (input_file.is_open()) {
        if (std::getline(input_file, line)) {
            while (comma < line.npos) {
                comma = line.find(',', pos);
                std::string range = line.substr(pos, comma - pos);
                size_t dash_idx = range.find('-');
                size_t min = std::stol(range.substr(0, dash_idx));
                size_t max = std::stol(range.substr(dash_idx + 1));
                // std::cout << "Range: " << min << " - " << max << std::endl;
                sum += range_repeats_sum(min, max);
                // std::cout << "Current sum: " << sum << std::endl;
                pos = comma + 1;
            }
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
