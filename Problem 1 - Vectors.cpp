#include <iostream>

// Vector<type> vector_name(optional_parameters);
template<typename T>
class Vector {

private:
    T* m_array = nullptr;
    int m_capacity = 0; // storage size currently allocated to the vector
    int m_nbElements = 0;

public:
    // vector<int> v; Make an empty integer vector - O(1)
    Vector() {
        this->m_array = new T[10];
        this->m_capacity = 10;
    }

    // vector<int> v(n); Make a vector with n elements - O(n)
    explicit Vector(int size) {
        if (size < 0) {
            std::cerr << "Cannot initialize vector with negative size" << std::endl;
            exit(1);
        }
        this->m_array = new T[size];
        this->m_capacity = size;
    }

    // vector<int> v(n, value); Make a vector with n elements, initialized to value - O(n)
    Vector(int size, T value) {
        if (size < 0) {
            std::cerr << "Cannot initialize vector with negative size" << std::endl;
            exit(1);
        }
        this->m_array = new T[size];
        this->m_capacity = size;
        this->m_nbElements = size;
        for (int i = 0; i < size; i++)
            this->m_array[i] = value;
    }

    void display() {
        if (this->m_nbElements < 1) {
            std::cout << "Empty array." << std::endl;
            return;
        }
        for (int i = 0; i < this->m_nbElements; i++)
            std::cout << this->m_array[i] << " ";
        std::cout << std::endl;
    }

    // v.assign(n, value); assigns new value to the vector elements by replacing old ones - O(n)
    bool assign(int n, T value) {
        if (n < 0) return false;
        if (n > this->m_capacity) {
            resize(this->m_capacity + n);
        }
        for (int i = 0; i < n; i++)
            this->m_array[i] = value;
        if (this->m_nbElements < n)
            this->m_nbElements = n;
        return true;
    }

    // v.resize(n); resizes the container so that it contains ‘n’ elements - O(n)
    bool resize(int n) {
        if (n < 0) return false;

        T* tmp = new T[n];
        for (int i = 0; i < n; i++)
            tmp[i] = this->m_array[i];
        delete[] this->m_array;
        this->m_array = tmp;
        //only need to update nbElements if resizing causes data loss due to smaller size
        if (this->m_nbElements > n)
            this->m_nbElements = n;
        this->m_capacity = n;

        return true;
    }
    
    int size() { return this->m_nbElements; }
    int capacity() { return this->m_capacity; }
    bool empty() { return this->m_nbElements == 0; }
    
    T front() {
        if (this->m_nbElements == 0) {
            std::cerr << "Cannot access first element as array is empty" << std::endl;
            exit(1);
        }
        return this->m_array[0];
    }
    
    T back() {
        if (this->m_nbElements == 0) {
            std::cerr << "Cannot access last element as array is empty" << std::endl;
            exit(1);
        }
        return this->m_array[this->m_nbElements - 1];
    }

    void push_back(T value) {
        if (this->m_nbElements >= this->m_capacity)
            resize(this->m_capacity + 5);
        this->m_array[this->m_nbElements] = value;
        this->m_nbElements++;
    }

    void pop_back() {
        if (empty()) return;
        this->m_nbElements--;
    }

    void insert(int position, T value) {
        //if negative value, send error
        if (position < 0) {
            std::cerr << "Cannot pass negative number to function" << std::endl;
            exit(1);
        }
        //if greater than the number of elements, ignore the position and assume
        //we are just pushing back to the first empty index
        if (position >= this->m_nbElements) {
            push_back(value);
            return;
        }
        //this case is insertion in the middle/beginning of the array,
        // create a new array and place the new element accordingly
        T* tmp = new T[this->m_capacity + 1];
        for (int i = 0; i < position; i++)
            tmp[i] = this->m_array[i];
        tmp[position] = value;
        for (int i = position; i < this->m_nbElements; i++)
            //since now tmp is one element ahead, the indices also are
            tmp[i + 1] = this->m_array[i];
        delete[] m_array;
        this->m_array = tmp;
        //add 1 to element and capacity counters
        this->m_nbElements++;
        this->m_capacity++;
    }

    //v.erase(position); Erase value indexed by position - O(n)
    bool erase(int position) {
        if (position > this->m_nbElements - 1)
            return false;

        switch (this->m_nbElements) {
            case 0:
                return false;
            case 1:
                pop_back();
                return true;
            default:
                T* tmp = new T[this->m_capacity - 1];
                for (int i = 0; i < position; i++)
                    tmp[i] = this->m_array[i];
                for (int i = position; i < this->m_nbElements - 1; i++)
                    //since now m_array is one element ahead, the indices also are
                    tmp[i] = this->m_array[i + 1];
                delete[] m_array;
                this->m_array = tmp;
                //remove 1 from m_nbElements
                this->m_nbElements--;
                return true;
        }
    }
};


int main()
{
    //TEST THE CONSTRUCTORS
    std::cout << "Creating an empty array a..." << std::endl;
    Vector<int> A;
    std::cout << "Creating an array B with size 15, and initializing all values to 7...\n\n";
    Vector<int> B(15, 7);

    //TEST THE DISPLAY() AND EMPTY() FUNCTIONS
    std::cout << "Displaying array A: ";
    if (A.empty()) std::cout << "Array A is empty.\n";
    else A.display();

    std::cout << "Displaying array B: ";
    if (B.empty()) std::cout << "Array B is empty.\n";
    else B.display();
    std::cout << std::endl;

    //TEST THE ASSIGN() FUNCTION
    std::cout << "Assigning the first 2 elements of A to 9...\n";
    A.assign(2, 9);
    std::cout << "Displaying array A: ";
    A.display();
    std::cout << "Assigning the first 7 elements of B to 0...\n";
    B.assign(7, 0);
    std::cout << "Displaying array B: ";
    B.display();
    std::cout << std::endl;

    //TESTING THE RESIZE(), CAPACITY() AND SIZE() FUNCTIONS
    std::cout << "Current size of array B: " << B.capacity() << std::endl;
    std::cout << "Current number of elements in B: " << B.size() << std::endl;
    std::cout << "Resizing B to 5..." << std::endl;
    B.resize(5);
    std::cout << "Current size of array B: " << B.capacity() << std::endl;
    std::cout << "Displaying array B: ";
    B.display();
    std::cout << std::endl;

    //TESTING THE FRONT(), BACK(), PUSH_BACK(), INSERT(), POP_BACK() AND ERASE() FUNCTIONS
    std::cout << "Pushing back the number 88 to the array B\n";
    B.push_back(88);
    std::cout << "Inserting the value 44 at position 0...\n";
    B.insert(0, 44);
    std::cout << "Displaying array B: ";
    B.display();
    std::cout << "Erasing the element at position 2...\n";
    B.erase(2);
    std::cout << "The first element of B is " << B.front() << std::endl;
    std::cout << "The last element of B is " << B.back() << std::endl;
    std::cout << "Deleting the last element...\n";
    B.pop_back();
    std::cout << "Displaying array B: ";
    B.display();

    return 0;

}
