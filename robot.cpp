#include <vector>
#include <iostream>

class Solution {
public:
    int uniquePaths(int m, int n) {
        // Generating the bottom options value array - each starting value is one since it can only travel left and not down from here
        std::vector<int> bottom_vec(n, 1);
        std::vector<int> upper_vec;
        
        // Loop through the upper_vec adding the diagonals to calculate how many unqiue paths there are from a given index
        for (int i = 1; i < m; ++i) {
            upper_vec.push_back(1);
            for (int j = 1; j < n; ++j) {
                upper_vec.push_back(bottom_vec[j] + upper_vec[j - 1]);
            }

            // At the end of each iteration - reset the bottom_vec array to the old upper_vec array
            bottom_vec = upper_vec;
            upper_vec.clear();
        }

        // After the loop the final element should contain the total number of unique options available
        return bottom_vec[n - 1];
    }
};

int main() {
    int m = 3;
    int n = 3;
    Solution my_sol;

    std::cout << my_sol.uniquePaths(m, n) << std::endl;

    return 0;
}