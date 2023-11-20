#include <vector>
#include <list>
#include <map>

#include <iostream>

class Solution {
public:
    struct points_node {
        int number;         // Base number that this node represents
        int value_gained;   // The value to be gained from this number in the vector
        int value_potential;// The max value potential to be gained by choosing this node

        bool operator<(const points_node& second) const {
            // Sorts by the value potential - which ever node has the higher value potential
            return (this->number < second.number);
        }

        void print_node() {
            std::cout << "Number: " << number;
            std::cout << ", Value Gained: " << value_gained;
            std::cout << ", Value Potential: " << value_potential << std::endl;
        }
    };

    // Returns the maximum value for the node given the remaining list based on the outlined algorithm
    int max_node(const points_node& node_in, const std::list<points_node>& list_in) {
        // Base case size of list_in = 0 or 1
        if (list_in.size() == 0) {
            return node_in.value_gained;
        } else if (list_in.size() == 1) {
            return node_in.value_gained + list_in.cbegin()->value_gained;
        }

        // Fetching the maximum value from the available nodes given
        int max_value = -1;
        for (auto it = list_in.begin(); it != list_in.end(); ++it) {
            if (it->value_potential > max_value) {
                max_value = it->value_potential;
            }
        }

        return node_in.value_gained + max_value;
    }

    // Returns the maximum value potential for the given list based on the outlined algorithm
    // max_list assumes the list has been sorted by the base number
    int max_list(std::list<points_node>& list_in) {
        // Base case size = 0 or 1
        if (list_in.size() == 0) {
            return 0;
        } else if (list_in.size() == 1) {
            return list_in.cbegin()->value_gained;
        }

        // Since it is assumed that the list is sorted we iterate up through the list calculating each nodes value potential
        for (auto it = list_in.begin(); it != list_in.end(); ++it) {
            std::list<points_node>::iterator one_less = list_in.end();

            // Finding the one more and one less iterators as well as the copy nodes iterator
            for (auto inner_it = list_in.begin(); inner_it != list_in.end(); ++inner_it) {
                if (inner_it->number == it->number - 1) {
                    one_less = inner_it;
                }
            }
            
            // If there was a node one less than the current node, then we will generate the sub list up to that point, otherwise the sub list will be up to the current node
            if (one_less != list_in.end()) {
                it->value_potential = max_node(*it, std::list<points_node>(list_in.begin(), one_less));
            } else {
                it->value_potential = max_node(*it, std::list<points_node>(list_in.begin(), it));
            }
        }

        // Finding the maximum value among the value potentials generated
        int max_value = -1;
        for (auto it = list_in.begin(); it != list_in.end(); ++it) {
            if (it->value_potential > max_value) {
                max_value = it->value_potential;
            }
        }

        return max_value;
    }

    int deleteAndEarn(const std::vector<int>& nums) {
        // Tracks how many of each num there is in num
        std::map<int, int> nums_count;
        std::list<points_node> points_list;

        for (auto it = nums.begin(); it != nums.end(); ++it) {
            // If the element is already in the map then simply increment it
            if (nums_count.count(*it)) {
                nums_count.at(*it) += 1;

            // Otherwise initialize it
            } else {
                nums_count.insert({*it, 1});
            }
        }

        // For each value in the map - calculate the value of that node from the vector
        for (auto index : nums_count) {
            points_node new_node;
            new_node.number = index.first;
            new_node.value_gained = index.first * index.second;
            points_list.push_back(new_node);
        }

        

        return max_list(points_list);
    }
};



using namespace std;

int main() {

    vector<int> my_nums = {1,2,3,4};

    Solution my_sol;

    std::cout << my_sol.deleteAndEarn(my_nums) << std::endl;

    return 0;
}