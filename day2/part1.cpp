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
 * Calculate the sum of all numbers in the range [min, max] that have repeated digits,
 * such that it's exactly two repeats of a sequence of 1 or more digits, with no leading
 * zeros.
 */
size_t range_repeats_sum(size_t min, size_t max) {
    size_t result = 0;

    for (size_t i = min; i <= max; ++i) {
        uint8_t digits_in_i = num_digits(i);
        if (digits_in_i % 2 == 1) {
            continue;
        }
        size_t divisor = pow(10, digits_in_i / 2) + 1;
        if (i % divisor == 0) {
            result += i;
        }
    }

    return result;
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
                //std::cout << "Range: " << min << " - " << max << std::endl;
                sum += range_repeats_sum(min, max);
                //std::cout << "Current sum: " << sum << std::endl;
                pos = comma + 1;
            }
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
