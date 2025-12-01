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
            if (line[0] == 'L') {
                dial = (dial - num) % 100;
            } else if (line[0] == 'R') {
                dial = (dial + num) % 100;
            }

            if (dial == 0) {
                passcount++;
            }
        }
    }
    input_file.close();
    std::cout << passcount << std::endl;

    return 0;
}
