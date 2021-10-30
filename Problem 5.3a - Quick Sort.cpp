#include <iostream>
#include <string>
#include <vector>

// swaps two elements from the array
void swap(std::vector<std::string>& input, int i, int j) {
    std::string temp = input[i];
    input[i] = input[j];
    input[j] = temp;
}

// is the solution
void quickSort(std::vector<std::string>& input, int lowerIndex, int higherIndex) {
    int i { lowerIndex };
    int j { higherIndex };
    //middle of array is the pivot
    std::string pivot { input[lowerIndex + (higherIndex - lowerIndex) / 2] };

    while (i <= j) {
        //keep going until it is out of order
        while (input[i] < pivot) {
            i++;
        }
        //same for other side
        while (input[j] > pivot) {
            j--;
        }
        //if it is out of order then swap
        if (i <= j) {
            swap(input, i, j);
            i++;
            j--;
        }
    }
    // call quickSort recursively to repeat this process
    if (lowerIndex < j) {
        quickSort(input, lowerIndex, j);
    }
    if (i < higherIndex) {
        quickSort(input, i, higherIndex);
    }
}

// for the user to use
void sort(std::vector<std::string>& input) {
    if (input.empty()) {
        return;
    }
    quickSort(input, 0, (int)input.size() - 1);
}

int main() {

    std::vector<std::string> input = { "cab", "bcd", "axz", "xwy", "mpo", "dcv" };
    sort(input);
    for (auto const& element : input)
        std::cout << element << " ";
    return 0;
}
