#include <vector>

#include <iostream>

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Two value holder vectors - defined as two blank vectors
        std::vector<int> bottom_vec(n, -1);
        std::vector<int> upper_vec(n, -1);

        // Looping through each row
        for (int i = m - 1; i >= 0; --i) {
            // Looping over each value in each row
            for (int j = n - 1; j >= 0; --j) {
                // Case of the bottom most right index
                if (i == (m - 1) && j == (n - 1)) {
                    upper_vec[j] = grid[i][j];
                
                // Case of the bottom row
                } else if (i == (m - 1)) {
                    upper_vec[j] = grid[i][j] + upper_vec[j + 1];

                // Case of the right column
                } else if (j == (n - 1)) {
                    upper_vec[j] = grid[i][j] + bottom_vec[j];
                
                // Case of any other index in the grid
                } else {
                    upper_vec[j] = grid[i][j] + std::min(bottom_vec[j], upper_vec[j + 1]);
                }
            }

            // Pushing the current vector into the previous spot
            bottom_vec = upper_vec;
        }

        return upper_vec[0];
    }
};

int main() {

    Solution my_sol;

    std::vector<std::vector<int>> my_grid = {{1,2,3},{4,5,6}};


    std::cout << my_sol.minPathSum(my_grid) << std::endl;

    return 0;
}