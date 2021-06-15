#include <iostream>
#include <vector>
#include <fstream>

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

    /*IMPORTANT*/
    //for information on how the text file is formatted, please read the comments below main()
    /*IMPORTANT*/

    std::ifstream file("Text.txt");
    //Exception if file doesn't exist
    try {
        file.exceptions(std::ios_base::failbit);
    }
    catch (const std::ios_base::failure& exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    int number_of_nodes = 0;
    file >> number_of_nodes;
    number_of_nodes++;

    std::vector<Node*> nodes(number_of_nodes);
    //for easy access to index, nodes.at(1) is a new Node(1). So we need nodes.at(0) empty
    nodes.push_back(nullptr);

    for (int i = 1; i < number_of_nodes; i++)
        nodes.at(i) = new Node(i);

    for (int i = 1; i < number_of_nodes; i++) {
        int val;
        file >> val;
        if (val == 0)
            nodes.at(i)->left = nullptr;
        else
            nodes.at(i)->left = nodes.at(val);
    }

    for (int i = 1; i < number_of_nodes; i++) {
        int val;
        file >> val;
        if (val == 0)
            nodes.at(i)->right = nullptr;
        else
            nodes.at(i)->right = nodes.at(val);
    }

    std::vector<Node*> requests1;
    std::vector<Node*> requests2;
    int val;

    while (!file.eof()) {
        file >> val;
        if (val == 0) break;
        requests1.push_back(nodes.at(val));
    }

    while (!file.eof()) {
        file >> val;
        if (val == 0) break;
        requests2.push_back(nodes.at(val));
    }

    Node* root = nodes.at(1);
    for (int i = 0; i < requests1.size(); i++) {
        solution(root, requests1.at(i), requests2.at(i));
    }

    return 0;
}

/*                          INFORMATION ON TEXT FILE FORMAT                             */

/*
 *
 * The first line contains the number of the nodes in the tree.
 * Since the node numbers are implicit (1,2,3,...,N), there is no need to include them
 * again in the text file.
 * The second line is N characters long, and specifies for each node at index i, its "left" (first) child
 * and 0 if it does not have a child
 * The same goes for the second line.
 *
 * Finally, the requests below are in the form of two strings of characters
 * which can be mapped into two vectors, in which every two elements at index i are for the same request.
 * The lines end with a 0 to signal the end of the line.
 *
 * EXAMPLE :
 *
 * 15           //NUMBER OF NODES, create 15 nodes going from value 1 til 15 (inclusive)
 *
 * 2 4 6 8 0 10 0 12 0 13 0 14 0 0 0    //node#1 has as left child the value 2, node #2 has 4, and so on...
 * 3 5 7 9 0 11 0 0 0 0 0 15 0 0 0      //node#1 has as right child the value 3, node#2 has 5, and so on...
 *
 * 1 2 4 12 8 12 13 0                   //the requests will be, (1,2), (2,12), ...
 * 2 12 6 75 9 6 0                      //i.e., the first from first line with the first from second line
 *
 */
