#include <iostream>
#include <vector>
#include <string>

/*              Note that this sort only works on words that contain smaller-case letters only                  */
/*                          since we are using the ascii code for the letters                                  */

//ascii code of small letter a
constexpr int ascii = 97;
//number of letters, is 26 but +1 for array indices
constexpr int nbr_letters = 27;

void countSort(std::vector<std::string>& input, int pos) {

    std::vector<std::string> output(input.size()); 
    //this array will count the occurences of every character
    int count[nbr_letters] = { 0 };

    // Store count of occurrences in count[]
    for (int i = 0; i < input.size(); i++)
        count[input[i].at(pos) - ascii]++;

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (int i = 1; i < nbr_letters; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = input.size() - 1; i >= 0; i--) {
        output[count[input[i].at(pos)-ascii] - 1] = input[i];
        count[input[i].at(pos) - ascii]--;
    }

    // Copy the output array to input[], so that input[] now
    // contains sorted numbers according to current digit
    for (int i = 0; i < input.size(); i++)
        input[i] = output[i];

}


//we will use radixsort to basically do countsort once for every i-th letter in our strings
void radixSort(std::vector<std::string>& input) {

    //all strings are of the same size
    int string_size = input[0].size(); 

    //do count sort for every i-th letter starting from the end
    for (int pos = string_size-1; pos >= 0; pos--)
        countSort(input, pos);
}

int main() {
    //input of strings of same fixed size (in this case 7)
    std::vector<std::string> input = { "climate", "justify", "bracket", "fortune", "dignity", "routine", "unaware",
                            "popular", "royalty", "paradox", "absence", "hostage", "factory", "abolish", "compose" };

    radixSort(input);
    
    for (const std::string& str : input) std::cout << str << " ";

    return 0;
}
