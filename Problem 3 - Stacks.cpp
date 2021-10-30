#include <iostream>
#include <stack>
#include <vector>
#include <random>       // to generate the vector via std::mt19937
#include <algorithm>    // for std::greater<>() to sort in decreasing order
#include <ctime>        // for std::time

constexpr int g_max_capacity = 10;  // for stack sizes, needed later

namespace MyRandom {
    // for the function getRandomNumber()
    // Initialize mersenne twister with a random seed based on the current system clock
    std::mt19937 mersenne { static_cast<std::mt19937::result_type>(std::time(nullptr)) };
}

int getRandomNumber(int min, int max) {
    std::uniform_int_distribution random_number { min, max };
    return random_number(MyRandom::mersenne);
}

// this function will serve as our solution, you can pass any vector of numbers to it
void solution(std::vector<int>& vector) {

    // step 1: sort the numbers in decreasing order
    sort(vector.begin(), vector.end(), std::greater<>());
    // display the vector
    std::cout << "Sorted vector: ";
    for (auto const& i : vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;

    // this vector will be the array of stacks we will use to store the numbers
    std::vector<std::stack<int>> stacks;
    // to keep track of each stack's capacity, we can use another array for that
    // so for stack at index i in stacks[], int at index i in stack_capacity represents
    // the capacity of that stack
    std::vector<int> stack_capacity;

    // for each number in vector
    for (auto const& value : vector) {
        // keep track of: if we find a place for it in an existing stack
        bool found_spot = false;
        // this variable keeps track of the minimum space between the stacks for each number
        int minimum_found = 11;
        // this one will tell us the index of the stack that is most suitable
        int min_index = -1;

        // pass on each existing stack
        for (int index = 0; index < stack_capacity.size(); index++) {
            // if there is a space in one of them
            if (stack_capacity.at(index) - value < minimum_found
                && stack_capacity.at(index) - value >= 0) {
                //remember the properties of this convenient stack
                minimum_found = stack_capacity.at(index) - value;
                min_index = index;
                found_spot = true;
            }

        }
        // now place our value in the stack we found
        if (found_spot) {
            stacks.at(min_index).push(value);
            stack_capacity.at(min_index) -= value;
        }
            // else, if we didn't find
        else {
            // create new stack
            std::stack<int> s;
            s.push(value);
            stacks.push_back(s);
            stack_capacity.push_back(g_max_capacity-value);
        }

    }

    //display the stacks
    for (int stack_index = 0; stack_index < stacks.size(); stack_index++) {
        std::cout << "Stack " << stack_index << ": ";
        // using this vector so I can display the values in descending order
        // not needed but easier on the eyes
        std::vector<int> values;
        while (!stacks.at(stack_index).empty()) {
            values.push_back(stacks.at(stack_index).top());
            stacks.at(stack_index).pop();
        }
        for (int index = (int)values.size() - 1; index >= 0; index--) {
            std::cout << values.at(index) << " ";
        }
        std::cout << std::endl;
    }

}

int main() {

    std::vector<int> vector;
    for (int i = 1; i <= 15; i++) {
        vector.push_back(getRandomNumber(1, 9));
    }

    std::cout << "Initial vector: ";
    for (auto const& i : vector)
        std::cout << i << " ";
    std::cout << std::endl;

    solution(vector);
    return 0;
}
