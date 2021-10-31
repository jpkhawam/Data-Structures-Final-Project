#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

class HashTable {
private:
    // class to hold the information about every word, and a next element when collision occurs
    class StringNode {
    public:
        std::string string;
        StringNode* next { nullptr };
        StringNode() = default;
        explicit StringNode(const std::string& string) {
            this->string = string;
        }
    };
    //array that will serve as the table
    std::vector<StringNode*> table = std::vector<StringNode*>(table_size);
    static const unsigned table_size = 293; // prime number

private:
    static unsigned hash(const std::string& input) {
        unsigned hash {};
        for (int i = 0; i < (int)input.length(); i++)
            hash += input.at(i) * static_cast<int>(std::pow(37, i));
        return (hash % table_size);
    }

public:
    void put(const std::string& input) {
        unsigned index { hash(input) };
        if (table.at(index) == nullptr) {
            table.at(index) = new StringNode(input);
        }
        else {
            StringNode* current { table.at(index) };
            while (current->next != nullptr)
                current = current->next;
            current->next = new StringNode(input);
        }
    }

    bool exists(const std::string& input_string) {
        unsigned index { hash(input_string) };
        if (table.at(index) != nullptr) {
            StringNode* current { table.at(index) };
            do {
                if (current->string == input_string)
                    return true;
                current = current->next;
            } while (current != nullptr);
        }
        return false;
    }
};

int main() {

    HashTable hash_table;
    std::ifstream dictionary(R"(Assets\dictionary.txt)");
    //Exception if file doesn't exist
    try {
        dictionary.exceptions(std::ios_base::failbit);
    }
    catch (const std::ios_base::failure& exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    while (!dictionary.eof()) {
        std::string word;
        dictionary >> word;
        hash_table.put(word);
    }

    dictionary.close();

    std::ifstream paragraph(R"(Assets\paragraph.txt)");
    //Exception if file doesn't exist
    try {
        paragraph.exceptions(std::ios_base::failbit);
    }
    catch (const std::ios_base::failure& exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    std::vector<std::string> non_existent_words;

    while (!paragraph.eof()) {
        std::string word;
        paragraph >> word;
        if (!hash_table.exists(word))
            non_existent_words.push_back(word);
    }

    for (auto const& word : non_existent_words)
        std::cout << word << std::endl;

    return 0;
}
