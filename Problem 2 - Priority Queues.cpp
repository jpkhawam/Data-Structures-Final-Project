#include <iostream>
#include <vector>
#include <time.h>

constexpr int number_of_queues = 10;

class Node {
public:
    const int data = 0;
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
};

//DONE:
/*
    1) generate the numbers n1, n2, n3....
    each number represents how much data enters this queue at this round ( all 0 )
*/

//TODO:
/*
    2) generate the number n
        this number represents how much data leaves from the queues at this round
    3) calculate the size of each queue
        maybe put these into a vector

    next step is, make (a) new function((s)) for 1 n every round, and dequeue that much
    from all the queues. Also figure out a way for display
    it can display one line per round since u can get size each round and what not.
*/

//returns a vector of the amount of data enqueued in each queue
std::vector<int> inputData(std::vector<Queue>& queues) {

    srand(time(nullptr));

    //for display, we could store the random ni's in a vector
    std::vector<int> random_numbers(number_of_queues);

    for (int i = 0; i < number_of_queues; i) {
        //we can cap it at 10, can be anything else
        int random_number_i = rand() % 10 + 1;
        random_numbers.at(i) = random_number_i;
        for (int count = random_number_i; count > 0; count--) {
            queues.at(i).enqueue(i);
        }
    }

    return random_numbers;
}

void outputData(std::vector<Queue>& queues) {
    srand(time(nullptr));
    //TODO: FIND A GOOD NUMBER
    int amount_to_output = rand() % 8 + 3;
}


int main()
{
    std::vector<Queue> queues(number_of_queues);
    int amount_of_rounds = 0;
    std::cout << "How many rounds would you like to run? ";
    std::cin >> amount_of_rounds;

    return 0;
}
