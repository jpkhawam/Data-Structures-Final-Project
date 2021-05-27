#include <iostream>

//this class is our binary search tree
class Node {
private:
    int m_data;
    Node* m_left = nullptr;
    Node* m_right = nullptr;

public:
    //constructor
    Node(int data) {
        m_data = data;
    }

    //in case you need to change data of a node (since it is private)
    void setData(int data) {
        m_data = data;
    }

    //returns pointer to the node with the given data
    Node* find(int data) {
        if (this == nullptr) return nullptr;
        else if (data < m_data) m_left->find(data);
        else if (data > m_data) m_right->find(data);
        else return this;
    }

    //returns pointer to the minimum element
    Node* findMinimum() {
        if (this == nullptr) return nullptr;
        else if (m_left == nullptr) return this;
        else return m_left->findMinimum();
    }

    //returns pointer to the maximum element
    Node* findMaximum() {
        if (this == nullptr) return nullptr;
        else if (m_right == nullptr) return this;
        else return m_right->findMaximum();
    }

    Node* insert(int data) {
        if (this == nullptr) {
            Node* newNode = new Node(data);
            return newNode;
        }
        if (data <= m_data) m_left = m_left->insert(data);
        else m_right = m_right->insert(data);
        return this;
    }

    void displayInOrder() {
        if (this == nullptr) return;
        m_left->displayInOrder();
        std::cout << m_data << " ";
        m_right->displayInOrder();
    }

    void displayPostOrder() {
        if (this == nullptr) return;
        m_left->displayPostOrder();
        m_right->displayPostOrder();
        std::cout << m_data << " ";
    }

    void displayPreOrder() {
        if (this == nullptr) return;
        std::cout << m_data << " ";
        m_left->displayPreOrder();
        m_right->displayPreOrder();
    }

};

int main()
{
    Node* root = new Node(15);
    for (int i = 0; i < 10; i++) {
        root->insert(rand() % 10);
    }
    std::cout << "In order: ";
    root->displayInOrder();
    std::cout << "\nPre Order: ";
    root->displayPreOrder();
    std::cout << "\nPost Order: ";
    root->displayPostOrder();
    return 0;
}
