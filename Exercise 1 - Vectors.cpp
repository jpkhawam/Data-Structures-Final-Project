#include <iostream>

//Usage:
//Create new vector : Vector<type> vector_name(optional_parameters);
template<typename T>
class Vector {

private:
    //prefix variable names with m_ so I can easily tell 
    // which variable is a member variable to this class
    T* m_array = nullptr;
    int m_capacity = 0;
    int m_nbElements = 0;

public:

    //vector<int> v; Make an empty integer vector. O(1)
    Vector() {
        this->m_array = new T[10];
        this->m_capacity = 10;
    }

    //vector<int> v(n); Make a vector with n elements. O(n)
    Vector(int size) {
        if (size < 0) {
            std::cerr << "Cannot initialize vector with negative size" << std::endl;
            exit(1);
        }
        this->m_array = new T[size];
        this->m_capacity = size;
    }

    //vector<int> v(n, value); Make a vector with n elements, initialized to value. O(n)
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

    //v.assign(n, value) It assigns new value to the vector elements by replacing old ones O(n)
    bool assign(int n, T value) {
        if (n <0) return false;
        if (n > this->m_capacity) {
            resize(this->m_capacity + n);
        }
        for (int i = 0; i < n; i++)
            this->m_array[i] = value;
        if (this->m_nbElements < n)
            this->m_nbElements = n;
        return true;
    }

    //v.resize(n) Resizes the container so that it contains ‘n’ elements. O(n)
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

    //v.size(); Return current number of elements. O(1)
    int size() {
        return this->m_nbElements;
    }

    //v.capacity() Returns the storage size currently allocated to the vector. O(1)
    int capacity() {
        return this->m_capacity;
    }

    //v.empty(); Return true if vector is empty. O(1)
    bool empty() {
        return this->m_nbElements == 0;
    }

    //v.front(); Return the first element. O(1)
    T front() {
        if (this->m_nbElements == 0) {
            std::cerr << "Cannot access first element as array is empty" << std::endl;
            exit(1);
        }

        return this->m_array[0];
    }

    //v.back(); Return the last element. O(1)
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
            tmp[i+1] = this->m_array[i];
        delete[] m_array;
        this->m_array = tmp;
        //add 1 to element and capacity counters
        this->m_nbElements++;
        this->m_capacity++;
    }

    //v.erase(position); Erase value indexed by position. O(n)
    bool erase(int position) {
        if (position > this->m_nbElements - 1)
            return false;

        switch (this->m_nbElements)
        {
        case 0:
            return false;
        case 1:
            pop_back();
            return true;
        default:
            T* tmp = new T[this->m_capacity-1];
            for (int i = 0; i < position; i++)
                tmp[i] = this->m_array[i];
            for (int i = position; i < this->m_nbElements-1; i++)
                //since now m_array is one element ahead, the indices also are
                tmp[i] = this->m_array[i+1];
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
    Vector<int> a;
    std::cout << "Creating an array b of size 10..." << std::endl;
    Vector<int> b(10);
    std::cout << "Creating an array c with size 15, and initializing all values to 7...\n";
    Vector<int> c(15, 7);
    std::cout << std::endl;

    //TEST THE DISPLAY() AND EMPTY() FUNCTIONS
    std::cout << "Displaying array a: ";
    a.display();
    if (a.empty()) std::cout << "Array a is empty.\n";
    //this second if is redundant but only for testing purposes
    else if (!a.empty()) std::cout << "Array a is not empty.\n";
    std::cout << "Displaying array b: ";
    b.display();
    if (b.empty()) std::cout << "Array b is empty.\n";
    else if (!b.empty()) std::cout << "Array b is not empty.\n";
    std::cout << "Displaying array c: ";
    c.display();
    if (c.empty()) std::cout << "Array c is empty.\n";
    else if (!c.empty()) std::cout << "Array c is not empty.\n";
    std::cout << std::endl;

    //TEST THE ASSIGN() FUNCTION
    std::cout << "Assigning the first 2 elements of a to 9...\n";
    a.assign(2, 9);
    std::cout << "Displaying array a: ";
    a.display();
    std::cout << "Assigning the first 4 elements of b to 3...\n";
    b.assign(4, 3);
    std::cout << "Displaying array b: ";
    b.display();
    std::cout << "Assigning the first 7 elements of c to 0...\n";
    c.assign(7, 0);
    std::cout << "Displaying array c: ";
    c.display();
    std::cout << std::endl;

    //TESTING THE RESIZE(), CAPACITY() AND SIZE() FUNCTIONS
    std::cout << "Current size of array a: " << a.capacity() << std::endl;
    std::cout << "Current number of elements in a: " << a.size() << std::endl;
    std::cout << "Resizing a to 3..." << std::endl;
    a.resize(3);
    std::cout << "Current size of array a: " << a.capacity() << std::endl;
    std::cout << "Displaying array a: ";
    a.display();
    std::cout << std::endl;

    std::cout << "Current size of array c: " << c.capacity() << std::endl;
    std::cout << "Current number of elements in c: " << c.size() << std::endl;
    std::cout << "Resizing c to 5..." << std::endl;
    c.resize(5);
    std::cout << "Current size of array c: " << c.capacity() << std::endl;
    std::cout << "Displaying array c: ";
    c.display();
    std::cout << std::endl;

    //TESTING THE FRONT(), BACK(), PUSH_BACK(), INSERT(), POP_BACK() AND ERASE() FUNCTIONS

    std::cout << "Displaying array c: ";
    c.display();
    std::cout << "Pushing back the number 88 to the array\n";
    c.push_back(88);
    std::cout << "Displaying array c: ";
    c.display();
    std::cout << "Inserting the value 44 at position 0...\n";
    c.insert(0, 44);
    std::cout << "Displaying array c: ";
    c.display();
    std::cout << "Erasing the element at position 2...\n";
    c.erase(2);
    std::cout << "Displaying array c: ";
    c.display();
    std::cout << "The first element of c is " << c.front() << std::endl;
    std::cout << "The last element of c is " << c.back() << std::endl;
    std::cout << "Deleting the last element...\n";
    c.pop_back();
    std::cout << "Displaying array c: ";
    c.display();

    return 0;

}


