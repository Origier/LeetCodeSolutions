#include <vector>

#include <iostream>

class Solution {
public:
    long long uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // Two value holder vectors - defined as two blank vectors
        std::vector<long long> bottom_vec(n, -1);
        std::vector<long long> upper_vec(n, -1);

        // Looping through each row
        for (int i = m - 1; i >= 0; --i) {
            // Looping over each value in each row
            for (int j = n - 1; j >= 0; --j) {
                // Case of the bottom most right index
                if (i == (m - 1) && j == (n - 1)) {
                    if (obstacleGrid[i][j] == 1) {
                        return 0;
                    } else {
                        upper_vec[j] = 1;
                    }
                
                // Case of the bottom row
                } else if (i == (m - 1)) {
                    if (upper_vec[j + 1] == 0) {
                        upper_vec[j] = 0;
                    } else {
                        upper_vec[j] = obstacleGrid[i][j] == 1 ? 0 : 1;
                    }

                // Case of the right column
                } else if (j == (n - 1)) {
                    if (bottom_vec[j] == 0) {
                        upper_vec[j] = 0;
                    } else {
                        upper_vec[j] = obstacleGrid[i][j] == 1 ? 0 : 1;
                    }
                    
                // Case of any other index in the grid
                } else {
                    if (obstacleGrid[i][j] == 1) {
                        upper_vec[j] = 0;
                    } else {
                        upper_vec[j] = upper_vec[j + 1] + bottom_vec[j];
                    }
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

    std::vector<std::vector<int>> my_grid = {{0,0},{1,1},{0,0}};


    std::cout << my_sol.uniquePathsWithObstacles(my_grid) << std::endl;

    return 0;
}