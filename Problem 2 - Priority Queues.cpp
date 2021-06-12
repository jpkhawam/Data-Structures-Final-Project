#include <iostream>
#include <vector>
#include <time.h>

constexpr int number_of_queues = 3;

class Node {
public:
    const int data = 0;             //is only 0 in this use case
    int type = -1;                  //is the "priority" of the node
    Node* next = nullptr;

public:
    Node(int type) {
        this->type = type;
    }
};

class Queue {
private:
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
        while (current->next != nullptr) {
            current = current->next;
            size++;
        }
        return size;
    }

    //inputs default value of 0
    void enqueue(int type) {
        Node node = Node(type);
        Node* tmp = &node;

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
        //delete tmp;

        if (this->front == nullptr)
            this->rear = nullptr;
        return true;
    }
};

//returns a vector of the amount of data enqueued in each queue
std::vector<int> inputData(std::vector<Queue>& queues) {

    srand(time(nullptr));

    //for display, we could store the random ni's in a vector
    std::vector<int> random_numbers(number_of_queues);

    for (int i = 0; i < number_of_queues; i++) {
        //we can cap it at 10, can be anything else
        int random_number_i = rand() % 10 + 1;
        random_numbers.at(i) = random_number_i;
        for (int count = random_number_i; count > 0; count--) {
            queues.at(i).enqueue(i);
        }
    }

    return random_numbers;
}

//returns number of elements "outputted" (dequeued)
int outputData(std::vector<Queue>& queues) {
    srand(time(nullptr));

    int total_size = 0;
    for (Queue& q : queues)
        total_size += q.size();

    //the amount to output should be random but still reasonable
    //this makes it so that it is between total_size/2 and total_size
    int amount_to_output = rand() % (total_size / 2) + total_size / 2;

    int amount_remaining = amount_to_output;
    for (int i = 0; i < number_of_queues; i++) {
        while (amount_remaining > 0 && !queues.at(i).isEmpty())
        {
            queues.at(i).dequeue();
            amount_remaining--;
        }
    }

    return amount_to_output;
}

//runs the solution once
void runOnce(std::vector<Queue>& queues)
{
    std::vector<int> random_numbers = inputData(queues);
    int amount_outputted = outputData(queues);

    std::cout << "Numbers inputted into each queue: ";
    for (const int& i : random_numbers)
        std::cout << i << "  ";

    std::cout << "\nAmount of data outputted from the system: " << amount_outputted << '\n';
    
    for (int i = 0; i < queues.size(); i++)
        std::cout << "q" << i << ".size(): " << queues.at(i).size() << '\n';
    std::cout << std::endl << std::endl;
}

int main()
{
    std::vector<Queue> queues(number_of_queues);

    int amount_of_rounds = 0;
    std::cout << "How many rounds would you like to run? ";
    std::cin >> amount_of_rounds;
    std::cout << std::endl << std::endl;
    
    for (int i = 0; i < amount_of_rounds; i++)
        runOnce(queues);

    return 0;
}
