#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    std::vector<std::string> lines;
    size_t max_length = 0;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            lines.push_back(line);
            if (line.size() > max_length) {
                max_length = line.size();
            }
        }
    }

    bool reading = false;
    char current_op = ' ';
    std::vector<size_t> running;
    size_t total = 0;
    for (int i = max_length - 1; i >= 0; i--) {
        bool all_blank = true;
        std::string column = "";
        for (size_t j = 0; j < lines.size(); j++) {
            std::string cur_line = lines[j];
            if (i >= cur_line.size()) {
                continue;
            } else {
                all_blank = all_blank && (cur_line[i] == ' ');
                if (j != lines.size() - 1) {
                    column.push_back(cur_line[i]);
                } else {
                    if (cur_line[i] == '+'  || cur_line[i] == '*') current_op = cur_line[i];
                }
            }
        }
        if (!all_blank) {
            running.push_back(std::stoll(column));
        }
        if (all_blank || i == 0) {
            assert(current_op != ' ');
            for (size_t num : running) {
                //std::cout << current_op << " " << num << " ";
            }
            //std::cout << std::endl;
            if (current_op == '+') {
                size_t sum = 0;
                for (size_t num : running) {
                    sum += num;
                }
                total += sum;
            } else if (current_op == '*') {
                size_t product = 1;
                for (size_t num : running) {
                    product *= num;
                }
                total += product;
            }
            current_op = ' ';
            running.clear();
        }
    }
    std::cout << total << std::endl;

    return 0;
}
