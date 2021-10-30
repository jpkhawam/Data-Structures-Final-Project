#include <iostream>
#include <vector>

std::vector<int> customSort(const std::vector<int> &input) {
    int size { static_cast<int>(input.size()) };
    int low{};
    int high { size - 1 };
    std::vector<int> output(size);

    // since we have only 3 possible values, this is easy to do in linear time
    for (int i = 0; i < size; i++) {
        // if the value is 0, put it at the beginning
        if (input.at(i) == 0) {
            output.at(low) = 0;
            low++;
        }
        //if the value is 2, put it at the end
        else if (input.at(i) == 2) {
            output.at(high) = 2;
            high--;
        }
        //if it is 1, continue
        else if (input.at(i) == 1)
            continue;
        else {
            std::cerr << "Array contained a value different than 0, 1 and 2." << std::endl;
            std::exit(1);
        }
    }
    //now all the unfilled values must be 1
    for (int i = low; i <= high; i++) {
        output.at(i) = 1;
    }
    return output;
}

int main() {
    std::vector<int> input { 0, 1, 1, 0, 0, 2, 2, 2, 0, 0, 1, 0, 2, 1 };
    std::vector<int> output = customSort(input);

    std::cout << "Initial array: ";
    for (const int i : input) {
        std::cout << i << " ";
    }

    std::cout << "\nSorted Array: ";
    for (int i = 0; i < input.size(); i++) {
        std::cout << output.at(i) << " ";
    }
    std::cout << std::endl;
}
