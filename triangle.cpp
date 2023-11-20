#include <vector>
#include <iostream>
#include <algorithm>

class Solution {
public:
    int minimumTotal(const std::vector<std::vector<int>>& triangle) {
        // The assumption is that each ascending row is greater in size than the previous
        std::vector<std::vector<int>> copy_vec(triangle.cbegin(), triangle.cend());
        
        // Reversing the vector to work from bottom up
        std::reverse(copy_vec.begin(), copy_vec.end());

        // Creating placeholder vectors to calculate the values - contructing the lower_vec with the first vector from the triangle copy
        std::vector<int> upper_vec(copy_vec[0].size(), 0);
        std::vector<int> lower_vec(copy_vec[0].cbegin(), copy_vec[0].cend());

        std::for_each(copy_vec.cbegin() + 1,
                    copy_vec.cend(), 
                    [&lower_vec, &upper_vec] (const std::vector<int>& vec) {
                        int i = 0;
                        std::for_each(vec.cbegin(), vec.cend(), [&i, &upper_vec, lower_vec] (const int& num) {
                            upper_vec[i] = num + std::min(lower_vec[i], lower_vec[i + 1]);
                            ++i;
                        });
                        
                        // Moving the values calculated into the lower vector
                        lower_vec = upper_vec;
        });

        return lower_vec[0];
    }
};


int main() {
    Solution my_sol;
    std::vector<std::vector<int>> my_tri = {{1},{2,3},{4,5,6}};

    std::cout << my_sol.minimumTotal(my_tri) << std::endl;

    return 0;
}