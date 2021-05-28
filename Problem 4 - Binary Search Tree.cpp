#include <iostream>

//this class is our binary search tree
class Node {
private:
    int m_data;
    Node* m_left = nullptr;
    Node* m_right = nullptr;

public:
    //-------------------------------------------------------
    //THESE ARE THE SOLUTIONS
    //THIS FUNCTION TESTS IF A AND B HAVE A DIRECT RELATION
    //I.E. A IS PARENT/GRANDPARENT/... OF B OR VICE VERSA
    bool directRelation(Node* secondNode) {

        //if either is a nullptr, there is no point in searching
        if (this == nullptr || secondNode == nullptr) return false;

        //variables we need to use. 
        Node* firstNode = this;
        //number of edges between the 2 in case we find them
        int edges = 0;
        //keeps track if we find or not
        bool found = false;

        //searches from the first to the second node
        while (!found) {
            if (secondNode->m_data == firstNode->m_data) {
                found = true;
                break;
            }
            else if (secondNode->m_data < firstNode->m_data) {
                if (firstNode->m_left != nullptr) {
                    firstNode = firstNode->m_left;
                    edges++;
                    continue;
                }
                else break;
            }
            else if (secondNode->m_data > firstNode->m_data) {
                if (firstNode->m_right != nullptr) {
                    firstNode = firstNode->m_right;
                    edges++;
                    continue;
                }
                else break;
            }
        }

        if (found) {
            std::cout << "Persons A and B are descendants-" << edges;
            return true;
        }
        //else let's try from the second node finding the first node
        else {
            edges = 0;
            firstNode = this;
        }

        while (!found) {
            if (firstNode->m_data == secondNode->m_data) {
                found = true;
                break;
            }
            else if (firstNode->m_data < secondNode->m_data) {
                if (secondNode->m_left != nullptr) {
                    secondNode = secondNode->m_left;
                    edges++;
                    continue;
                }
                else break;
            }
            else if (firstNode->m_data > secondNode->m_data) {
                if (secondNode->m_right != nullptr) {
                    secondNode = secondNode->m_right;
                    edges++;
                    continue;
                }
                else break;
            }
        }

        if (found) {
            std::cout << "Persons A and B are descendants-" << edges;
            return true;
        }
        //else there is no direct relation
        else return false;
    }
   
    //--------------------------------------------------------
    // THIS IS JUST THE CLASS TREE 
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
    root->insert(10);
    root->insert(7);
    root->insert(9);
    Node* secondNode = root->find(9);
    root->directRelation(secondNode);
    return 0;
}
