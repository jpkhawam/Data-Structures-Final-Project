#include <iostream>
#include <vector>
#include <random>
#include <ctime>

constexpr int g_number_of_queues = 3;

class Node {
public:
    int type = -1;                  //is the "priority" of the node
    Node* next = nullptr;

public:
    explicit Node(int type) {
        this->type = type;
    }
};

class Queue {
public:
    Node* front = nullptr;
    Node* rear = nullptr;

public:
    bool isEmpty() {
        return this->front == nullptr;
    }

    int size() {
        if (this->isEmpty()) return 0;

        Node* current = this->front;
        int size = 1;
        while (true) {
            if (current == this->rear) break;
            current = current->next;
            size++;
        }
        return size;
    }
    
    void enqueue(int type) {
        Node* tmp = new Node(type);
        if (this->isEmpty()) {
            this->front = this->rear = tmp;
            return;
        }
        else {
            this->rear->next = tmp;
            this->rear = tmp;
        }
    }

    bool dequeue() {
        if (this->isEmpty())
            return false;
        Node* tmp = this->front;
        this->front = this->front->next;
        delete tmp;
        if (this->front == nullptr)
            this->rear = nullptr;
        return true;
    }
};

//returns a vector of the amount of data enqueued in each queue
std::vector<int> inputData(std::vector<Queue>& queues, int roundNumber) {
    // Initialize our mersenne twister with a random seed based on the clock and
    // multiply the time by roundNumber each time so each round input is different
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr) * roundNumber) };

    // Create a reusable random number generator that generates uniform numbers between 1 and 10
    // we can cap it at 10, can be anything else
    std::uniform_int_distribution<> rng{ 1, 10 };

    //for display, we could store the random ni's in a vector
    std::vector<int> random_numbers(g_number_of_queues);

    for (int i = 0; i < g_number_of_queues; i++) {
        random_numbers.at(i) = rng(mersenne);
        for (int count = random_numbers.at(i); count > 0; count--) {
            queues.at(i).enqueue(i);
        }
    }
    return random_numbers;
}

//returns number of elements "outputted" (dequeued)
int outputData(std::vector<Queue>& queues) {
    int total_size = 0;
    for (Queue& q : queues)
        total_size += q.size();

    // Initialize our mersenne twister with a random seed based on the clock
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    // Create a reusable random number generator that generates
    // uniform numbers between total_size/3 and total_size
    std::uniform_int_distribution<> rng{ total_size / 3, total_size };

    int amount_to_output = rng(mersenne);

    int amount_remaining = amount_to_output;
    for (int i = 0; i < g_number_of_queues; i++) {
        while (amount_remaining > 0 && !(queues.at(i).isEmpty()))
        {
            queues.at(i).dequeue();
            amount_remaining--;
        }
    }
    return amount_to_output;
}

int main()
{
    std::vector<Queue> queues(g_number_of_queues);
    //average size of each queue
    std::vector<double> averages(g_number_of_queues,0);

    std::cout << "Number of queues: " << g_number_of_queues << std::endl;

    int amount_of_rounds = 0;
    std::cout << "How many rounds would you like to run?" << std::endl;
    std::cin >> amount_of_rounds;
    std::cout << std::endl << std::endl;


    for (int round = 1; round <= amount_of_rounds; round++) {
        std::cout << "Round " << round << ": " << std::endl;

        std::vector<int> random_numbers = inputData(queues, round);

        std::cout << "Numbers inputted into each queue: ";
        for (const int& i : random_numbers)
            std::cout << i << "  ";

        int amount_outputted = outputData(queues);

        std::cout << "\nAmount of data outputted from the system: " << amount_outputted << '\n';
        std::cout << "Size of queues after output: " << std::endl;
        for (int i = 0; i < queues.size(); i++){
            std::cout << "q" << i << ".size(): " << queues.at(i).size() << '\n';
            averages.at(i) += queues.at(i).size();
        }
        std::cout << std::endl << std::endl;
    }

    std::cout << "Average size of queues: \n";
    for (int i = 0; i < g_number_of_queues; i++) {
        std::cout << "q" << i << ": " << averages.at(i)/amount_of_rounds << std::endl;
    }

    return 0;
}
