#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    int dial = 50;
    int passcount = 0;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            int num = std::stoi(line.substr(1));
            bool crossing = false;
            if (line[0] == 'L') {
                if (num > dial) {
                    passcount += (static_cast<int>(dial != 0)) + (num - dial) / 100;
                    crossing = true;
                }
                dial = (dial - num) % 100;
                if (dial < 0) {
                    dial = 100 + dial;
                }
            } else if (line[0] == 'R') {
                if (num > (100 - dial)) {
                    passcount += (static_cast<int>(dial != 0)) + (num - ((100 - dial) % 100)) / 100;
                    crossing = true;
                }

                dial = (dial + num) % 100;
            }

            if (dial == 0 && !crossing) {
                passcount++;
            }
            std::cout << line << " " << dial << " " << passcount << std::endl;
        }
    }
    input_file.close();
    std::cout << passcount << std::endl;

    return 0;
}
