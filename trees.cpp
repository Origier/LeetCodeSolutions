#include "trees.h"


void Solution::add_children(Node * node, const std::vector<int>& cost) {
    // Base case - node is at the end of the array
    if (node->array_index >= cost.size() - 1) {
        return;
    }

    // Creating the left node since the current node is not at the end of the array
    node->left_branch = new Node;
    node->left_branch->value_self = cost[node->array_index + 1];
    node->left_branch->array_index = node->array_index + 1;
    // Creating the left nodes children
    add_children(node->left_branch, cost);

    // If the node is more than one away from the end then add both branches
    if (node->array_index != cost.size() - 2) {
        // Creating the right node
        node->right_branch = new Node;
        node->right_branch->value_self = cost[node->array_index + 2];
        node->right_branch->array_index = node->array_index + 2;
        // Creating the right nodes children
        add_children(node->right_branch, cost);
    }
}

void Solution::delete_tree(Node * node) {
    // If there is either branch - recursively delete that branch
    if (node->left_branch != NULL) {
        delete_tree(node->left_branch);
        // Once left nodes children have been deallocated we are safe to deallocate the left branch
        delete node->left_branch;
    }

    // If there is either branch - recursively delete that branch
    if (node->right_branch != NULL) {
        delete_tree(node->right_branch);
        // Once left nodes children have been deallocated we are safe to deallocate the left branch
        delete node->right_branch;
    }
}

void Solution::calculate_cost(Node * node) {
    // Base case - one branch is NULL therefore there is a zero cost move out and thus the optimal choice - this nodes cost is only itself
    if (node->left_branch == NULL || node->right_branch == NULL) {
        node->value_total = node->value_self;
        return;
    }

    // Otherwise calculate both the right and left node values 
    calculate_cost(node->left_branch);
    calculate_cost(node->right_branch);

    int right_value = node->right_branch->value_total;
    int left_value = node->left_branch->value_total;

    // This nodes total value is the sum of this nodes self value along with the lowest value between the right and left branch since that would be the optimal move
    if (right_value < left_value) {
        node->value_total = node->value_self + right_value;
    } else {
        node->value_total = node->value_self + left_value;
    }
}

int Solution::minCostClimbingStairs(const std::vector<int>& cost) {
    // If the array is 2 or less elements then just pick the cheapest route
    int size = cost.size();

    // If there is only one step then take two steps to the top
    if (size <= 1) {
        return 0;
    }
    
    // If there is only two steps then take the cheapest step and then one or two steps to the top
    if (size == 2) {
        if (cost[0] < cost[1]) {
            return cost[0];
        } else {
            return cost[1];
        }
    }

    // When the array is larger than 2 then we need to look at it as a tree to find the optimal route
    Node * first_step_tree = new Node;
    Node * second_step_tree = new Node;

    first_step_tree->value_self = cost[0];
    first_step_tree->array_index = 0;
    second_step_tree->value_self = cost[1];
    second_step_tree->array_index = 1;

    // A recursive call to populate the tree with children
    add_children(first_step_tree, cost);
    add_children(second_step_tree, cost);

    // Rescursively calculating the total cost for each tree
    calculate_cost(first_step_tree);
    calculate_cost(second_step_tree);

    int first_tree_cost = first_step_tree->value_total;
    int second_tree_cost = second_step_tree->value_total;

    // De-allocating memory for the trees
    delete_tree(first_step_tree);
    delete_tree(second_step_tree);

    delete first_step_tree;
    delete second_step_tree;

    // Returning whichever tree generated the lowest cost
    if (first_tree_cost < second_tree_cost) {
        return first_tree_cost;
    } else {
        return second_tree_cost;
    }
}
