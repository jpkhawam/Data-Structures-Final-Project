#include <iostream>

class MinHeap {

private:
    class Task {
        public:
            int priority { 99 };
            int id { -1 };
            int duration {};

            Task() = default;

            Task(int priority, int id, int duration) {
                this->priority = priority;
                this->id = id;
                this->duration = duration;
            }
    };

    int capacity { 10 };
    int size {};
    Task* items = new Task[capacity];

private:
    static int getLeftChildIndex(int parentIndex) { return 2 * parentIndex + 1; }
    static int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 2; }
    static int getParentIndex(int childIndex) { return (childIndex - 1) / 2; }

    bool hasLeftChild(int index) const { return getLeftChildIndex(index) < size; }
    bool hasRightChild(int index) const { return getRightChildIndex(index) < size; }
    static bool hasParent(int index) { return getParentIndex(index) >= 0; }

    Task leftChild(int index) { return items[getLeftChildIndex(index)]; }
    Task rightChild(int index) { return items[getRightChildIndex(index)]; }
    Task parent(int index) { return items[getParentIndex(index)]; }

    void swap(int indexOne, int indexTwo) {
        Task tmp = items[indexOne];
        items[indexOne] = items[indexTwo];
        items[indexTwo] = tmp;
    }

    void ensureExtraCapacity() {
        if (size == capacity) {
            Task* newTasks = new Task[capacity * 2];
            for (int i = 0; i < size; i++)
                newTasks[i] = items[i];
            delete[] items;
            items = newTasks;
            capacity *= 2;
        }
    }

    void heapifyUp() {
        int index = size - 1;
        while (hasParent(index) && parent(index).priority > items[index].priority) {
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }

    void heapifyDown() {
        int index = 0;
        while (hasLeftChild(index)) {
            int smallerChildIndex = getLeftChildIndex(index);
            if (hasRightChild(index) && rightChild(index).priority < leftChild(index).priority) {
                smallerChildIndex = getRightChildIndex(index);
            }

            if (items[index].priority < items[smallerChildIndex].priority) {
                break;
            }
            else {
                swap(index, smallerChildIndex);
            }
            index = smallerChildIndex;
        }

    }

public:

    //  display the first task that will be printed
    // returns the minimum element
    Task peek() {
        if (size == 0) {
            std::cerr << "Empty heap." << std::endl;
            exit(1);
        }
        return items[0];
    }

    // mark a task as done and test again
    // remove the minimum element
    Task poll() {
        if (size == 0) {
            std::cerr << "Empty heap." << std::endl;
            exit(1);
        }
        Task tmp = items[0];
        items[0] = items[size - 1];
        size--;
        heapifyDown();
        return tmp;
    }

    void add(Task item) {
        ensureExtraCapacity();
        items[size] = item;
        size++;
        heapifyUp();
    }

    int calculateDuration(int id) {
        //first find the desired task by the id
        int target_index = 0;
        for (; target_index < size; target_index++)
            if (items[target_index].id == id)
                break;

        if (items[target_index].id != id) {
            std::cerr << "Task not found." << std::endl;
            exit(1);
        }

        int duration {};
        for (int i = 0; i < size; i++)
            if (items[i].priority <= items[target_index].priority)
                duration += items[i].duration;
        return duration;
    }
};

int main() {

    MinHeap heap;
    heap.add({ 2, 100, 3 });
    heap.add({ 5, 40, 4 });
    heap.add({ 1, 20, 2 });
    heap.add({ 4, 30, 5 });
    heap.add({ 5, 200, 4 });
    heap.add({ 3, 50, 4 });

    std::cout << "Enter an id of a task: (20/30/40/50/100/200)" << std::endl;
    int id_to_look_for;
    std::cin >> id_to_look_for;
    int result = heap.calculateDuration(id_to_look_for);
    std::cout << "Your ID is: " << id_to_look_for << ". The necessary time to print your task is: "
              << result << std::endl;

    return 0;
}
