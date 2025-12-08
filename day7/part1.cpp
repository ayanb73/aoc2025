#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void print_bitset(const std::vector<bool>& bitset) {
    for (bool bit : bitset) {
        std::cout << (bit ? '|' : '.');
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;
    std::vector<bool> visited;
    if (std::getline(input_file, line)) {
        visited.resize(line.size(), false);
        visited[line.find('S')] = true;
    }

    size_t splits = 0;
    //print_bitset(visited);
    while (std::getline(input_file, line)) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '^' && visited[i]) {
                splits++;
                if((i - 1) >= 0) visited[i-1] = true;
                if((i + 1) < line.size()) visited[i+1] = true;
                visited[i] = false;
            }
        }
        //print_bitset(visited);
    }
    std::cout << splits << std::endl;
    return 0;
}
