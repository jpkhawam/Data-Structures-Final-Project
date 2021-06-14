#include <iostream>
#include <vector>

struct Node {
    int val = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    explicit Node(int val)
    {
        this->val = val;
    }
};

bool findPath(std::vector<Node*>& path, Node* root, int val) {

    //when we reach a leaf, return
    if (root == nullptr)
        return false;

    //not a node, insert in vector so we check if it exists
    path.push_back(root);

    //case of finding the desired value. Return here
    if (root->val == val)
        return true;

    //if not, keep digging in on both sides, until one returns true or it fails
    if ((root->left && findPath(path, root->left, val))
        || (root->right && findPath(path, root->right, val)))
        return true;

    //in which case we need to remove that element from the vector
    path.pop_back();

    //and state that we didn't find
    return false;
}

int findDirectRelation(std::vector<Node*>& path1, std::vector<Node*>& path2, Node* first, Node* second) {

    int index1 = 0, index2 = 0;
    bool found = false;

    //the bigger array will contain the other element somewhere inside, and itself at the end
    if (path1.size() > path2.size()) {
        index1 = path1.size() - 1;
        for (int i = 0; i < path1.size(); i++) {
            if (path1.at(i)->val == second->val) {
                index2 = i;
                found = true;
                break;
            } 
        }
    }

    else {
        index2 = path2.size() - 1;
        for (int i = 0; i < path2.size(); i++) {
            if (path2.at(i)->val == first->val) {
                index1 = i;
                found = true;
                break;
            }
        }
    }
    if (found) return std::abs(index1 - index2);
    return -1;
}

int findIndexCommonAncestor(std::vector<Node*>& path1, std::vector<Node*>& path2) {
    for (int i = 1; i < path1.size() && i < path2.size(); i++) {
        if (path1.at(i) == path2.at(i)) continue;
        return i - 1;
    }
}

void solution(Node* root, Node* first, Node* second) {
    //path# will store the list of nodes that lead to the # node
    std::vector<Node*> path1;
    std::vector<Node*> path2;
    //this modifies these vectors, storing the nodes in them
    findPath(path1, root, first->val);
    findPath(path2, root, second->val);

    //this checks if there is a direct relation between the two
    //if yes it prints the distance
    int directRelation = findDirectRelation(path1, path2, first, second);
    if (directRelation > -1) {
        std::cout << first->val << " and " << second->val << " are descendant-" << directRelation << std::endl;
        return;
    }

    //else, just find the youngest common ancestor and print the distances
    //from the nodes to it
    int indexAncestor = findIndexCommonAncestor(path1, path2);
    std::cout << first->val << " and " << second->val << " are cousin" << path1.size() - indexAncestor - 1 << "-"
        << path2.size() - indexAncestor - 1 << "-" << path1.at(indexAncestor)->val << std::endl;
}

int main() {

    //      Create tree identical to the one in the given           //
    //--------------------------------------------------------------//
    Node* root = new Node(1);    Node* node2 = new Node(2);         //
    Node* node3 = new Node(3);   Node* node4 = new Node(4);         //
    Node* node5 = new Node(5);   Node* node6 = new Node(6);         //
    Node* node7 = new Node(7);   Node* node8 = new Node(8);         //
    Node* node9 = new Node(9);   Node* node10 = new Node(10);       //
    Node* node11 = new Node(11); Node* node12 = new Node(12);       //
    Node* node13 = new Node(13); Node* node14 = new Node(14);       //
    Node* node15 = new Node(15);                                    //
    root->right = node3;    root->left = node2;                     //
    node2->left = node4;    node2->right = node5;                   //
    node4->left = node8;    node4->right = node9;                   //
    node8->left = node12;   node12->left = node14;                  //
    node12->right = node15; node3->left = node6;                    //
    node3->right = node7;   node6->left = node10;                   //
    node6->right = node11;  node10->left = node13;                  //
    //--------------------------------------------------------------//

    solution(root, root, node2);   //1 and 2 are descendant-1
    solution(root, node2, node12); //2 and 12 are descendant-3
    solution(root, node4, node6);  //4 and 6 cousin2-2-1
    solution(root, node12, node7); //12 and 7 cousin4-2-1
    solution(root, node8, node5);  //8 and 5 cousin2-1-2
    solution(root, node12, node9); //12 and 9 cousin2-1-4
    solution(root, node13, node6); //13 and 6 descendant-2

    return 0;
}
