#include <vector>
#include <algorithm>

#include <iostream>

class Solution {
public:
    int deleteAndEarn(const std::vector<int>& nums) {
        std::vector<int> copy_nums(nums.cbegin(), nums.cend());

        // Sort the vector in ascending order
        std::sort(copy_nums.begin(), copy_nums.end());
        int two_num_back = 0;
        int one_num_back = 0;
        int current_num = *copy_nums.begin();
        int current_val = 0;
        int prev_num = 0;
        int temp = 0;

        for (int i = 0; i < copy_nums.size(); ++i) {
            if (copy_nums[i] == current_num) {
                current_val += current_num;
            } else {
                // If the variables are all still default then just set the first variable back
                if (one_num_back == 0) {
                    one_num_back = current_val;
                
                // In the case that the prev number is one less than the current number - add the current value to whatever was two numbers back
                } else if (current_num - 1 == prev_num) {
                    temp = one_num_back;
                    one_num_back = two_num_back + current_val;
                    two_num_back = std::max(temp, two_num_back);
                
                // Otherwise just add the max of the two previous
                } else {
                    temp = one_num_back;
                    one_num_back = current_val + std::max(one_num_back, two_num_back);
                    two_num_back = std::max(temp, two_num_back);
                }
                prev_num = current_num;

                // Resetting to the next number
                current_val = copy_nums[i];
                current_num = copy_nums[i];
            }
        }

        // Final step is to add the last number to the values
        if (current_num - 1 == prev_num) {
            temp = one_num_back;
            one_num_back = two_num_back + current_val;
            two_num_back = std::max(temp, two_num_back);
        
        // Otherwise just add the max of the two previous
        } else {
            temp = one_num_back;
            one_num_back = current_val + std::max(one_num_back, two_num_back);
            two_num_back = std::max(temp, two_num_back);
        }
        

        // By the end of the array we should have the only two maximum value options parsed outs
        return std::max(one_num_back, two_num_back);
    }
};



using namespace std;

int main() {

    vector<int> my_nums = {3,4,4,2};

    Solution my_sol;

    std::cout << my_sol.deleteAndEarn(my_nums) << std::endl;

    return 0;
}