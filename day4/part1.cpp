#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Direction { int dx, dy; };
std::array<Direction, 8> DIRECTIONS = {{
    {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
}};

bool is_accessible(const std::vector<std::vector<bool>>& grid, int row_idx, int col_idx) {
    bool val = grid[row_idx][col_idx];
    int count = 0;
    for (const auto& dir : DIRECTIONS) {
        int new_row = row_idx + dir.dx;
        int new_col = col_idx + dir.dy;
        if (new_row < 0 || new_row >= grid.size() || new_col < 0 || new_col >= grid[new_row].size()) {
            continue;
        }
        if (grid[new_row][new_col]) {
            count++;
        }
        if (count >= 4) {
            return false;
        }
    }
    return true;
}

int count_accessible(const std::vector<std::vector<bool>>& grid) {
    int count = 0;
    for (int row_idx = 0; row_idx < grid.size(); ++row_idx) {
        for (int col_idx = 0; col_idx < grid[row_idx].size(); ++col_idx) {
            if (!grid[row_idx][col_idx]) {
                continue;
            }
            if (is_accessible(grid, row_idx, col_idx)) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::ifstream input_file(argv[1]);
    std::vector<std::vector<bool>> grid;
    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            std::vector<bool> row(line.size(), false);
            for (int i = 0; i < line.size(); ++i) {
                row[i] = (line[i] == '@');
                // std::cout << static_cast<int>(row[i]) << " ";
            }
            grid.push_back(row);
            // std::cout << "\n";
        }
    }
    std::cout << count_accessible(grid) << std::endl;
    return 0;
}
