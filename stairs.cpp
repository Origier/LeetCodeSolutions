#include <iostream>

#include <vector>
#include <algorithm>

class Solution {
public:
    int minCostClimbingStairs(const std::vector<int>& cost) {
        int size = cost.size();

        // When the size is only one the step can just be skipped
        if (size <= 1) {
            return 0;
        }

        // When the size is exactly two just return the cheapest element
        if (size == 2) {
            if (cost[0] < cost[1]) {
                return cost[0];
            } else {
                return cost[1];
            }
        }

        // Otherwise we must calculate the cheapest route

        // reverse the list the generate a parallel list of cost indicies
        std::vector<int> cost_copy = cost;
        std::reverse(cost_copy.begin(), cost_copy.end());

        // min_step_cost is the list of cost indicies - setting each index to be the minimum value cost to reach that index based on previous indicies
        // The minimum value of index x is the inherit value of that index plus the minimum value of the two indicies it can travel to
        // Therefore, we start from the back of the list since this will generate the minimum value costs as we ascend the list
        std::vector<int> min_step_cost;
        int minimum_value;

        // Adding the first two elements which will be just the base index cost
        min_step_cost.push_back(cost_copy[0]);
        min_step_cost.push_back(cost_copy[1]);
        
        // Looping throught the reversed list to calculate all of the costs
        for (int i = 2; i < size; ++i) {
            // Setting the lowests cost / best route for the index to step to based on the current index
            if (min_step_cost[i - 1] < min_step_cost[i - 2]) {
                minimum_value = min_step_cost[i - 1];
            } else {
                minimum_value = min_step_cost[i - 2];
            }

            // Pushing back the newly defined cost for this index
            min_step_cost.push_back(cost_copy[i] + minimum_value);
        }

        // Once the loop is done, each index at the end of the min_step_cost vector represents to total minimum cost for traveling in that path
        // Simply return the smallest value from the last two elements
        if (min_step_cost[size - 1] < min_step_cost[size - 2]) {
            return min_step_cost[size - 1];
        } else {
            return min_step_cost[size - 2];
        }
    }
};


int main() {
    Solution my_sol;

    std::vector<int> test_vec = {10, 15, 20, 30};

    int min_cost = my_sol.minCostClimbingStairs(test_vec);

    std::cout << min_cost << std::endl;

    return 0;
}