#include <iostream>
#include <vector>

constexpr int g_max_value = 26;

std::vector<int> customSort(const std::vector<int> &input) {
    int size = input.size();
    std::vector<int> output(size);
    // this will keep track of where in output[] we have filled so far
    int elementsFilled = 0;

    // each element in this array represents the number of occurrences of
    // the number 0<i<27 from input
    std::vector<int> helper_array(g_max_value + 1, 0);

    for (int index = 0; index < size; index++) {
        // helper_array[i] stores the number of occurrences the number i appears
        // passes once on each element on input, so O(n)
        helper_array.at(input.at(index))++;
    }

    //the outer for loop runs only 26 times
    for (int index = 1; index < g_max_value + 1; index++) {
        //the inner for loop runs for i times, i being the amount of occurences of i
        //what this results is both loops resulting in an O(n) complexity combined
        for (int val = 0; val < helper_array.at(index); val++) {
            output.at(elementsFilled) = index;
            elementsFilled++;
        }
    }

    return output;
}

int main() {
    std::vector<int> input{ 1, 5, 2, 5, 7, 2, 4, 8, 11, 22, 13, 16, 2, 6, 9, 5, 3, 1 };
    std::vector<int> result = customSort(input);
    for (int i = 0; i < input.size(); i++)
        std::cout << result.at(i) << " ";
    return 0;
}
