#include <iostream> 
#include <stack> 
#include <vector>
#include <random>                   //to generate the vector
#include <algorithm>                //for std::greater<>() to sort in decreasing order

constexpr int max_capacity = 10;    //for stack sizes, needed later

//this function will serve as our solution, you can pass any vector of numbers to it
void solution(std::vector<int>& vector) {

    //step 1: sort the numbers in decreasing order
    sort(vector.begin(), vector.end(), std::greater<>());
    //display the vector
    std::cout << "Sorted vector: ";
    for (auto const& i : vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl << std::endl;

    //stacks will be the array of stacks we will use to store the numbers
    std::vector<std::stack<int>> stacks;
    //to keep track of each stack's capacity, we can use another array for that
    //so for stack at index i in stacks[], int at index i in stack_capacity represents
    //the capacity of that stack
    std::vector<int> stack_capacity;

    //for each number in vector
    for (auto const& value : vector) {
        //keep track of: if we find a place for it in an existing stack
        bool found_spot = false;
        //this variable keeps track of the minimum space between the stacks for each number
        int minimum_found = 11;
        //this one will tell us the index of the stack that is most suitable
        int min_index = -1;

        //pass on each existing stack
        for (int index = 0; index < stack_capacity.size(); index++) {
            //if there is a space in one of them
            if (stack_capacity.at(index) - value < minimum_found
                && stack_capacity.at(index) - value >= 0) {
                //remember the properties of this convenient stack
                minimum_found = stack_capacity.at(index) - value;
                min_index = index;
                found_spot = true;
            }
           
        }
        //now place our value in the stack we found
        if (found_spot) {
            stacks.at(min_index).push(value);
            stack_capacity.at(min_index) -= value;
        }
        //else, if we didn't find
        else {
            //create new stack 
            std::stack<int> s;
            s.push(value);
            stacks.push_back(s);
            stack_capacity.push_back(max_capacity-value);
        }

    }

    //display the stacks
    for (int index = 0; index < stacks.size(); index++) {
        std::cout << "Stack " << index << ": ";
        //using this vector so I can display the values in descending order
        //not needed but easier on the eyes
        std::vector<int> vals;
        while (!stacks.at(index).empty()) {
            vals.push_back(stacks.at(index).top());
            stacks.at(index).pop();
        }
        for (int index = vals.size() - 1; index >= 0; index--) {
            std::cout << vals.at(index) << " ";
        }
        std::cout << std::endl;
    }
       
}

int main()
{
    //create a random vector to test the solution
    std::vector<int> vector;
    srand(time(NULL));
    for (int i = 1; i <= 15; i++) {
        //*i so they differ from each other
        //%9 so it's between 0 and 9
        //+1 so it's between 1 and 10
        vector.push_back(rand() * i % 9 + 1);
    }

    //display the vector to the user
    std::cout << "Initial vector: ";
    for (auto const& i : vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    solution(vector);
    return 0;
}

