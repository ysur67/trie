#include <string>
#include <iostream>
#include <map>
using std::cout;
using std::string;
using std::map;

class Node
{
public:
    Node(){ };
    map<char, Node*> nodes;
    bool isEnd;
};

void getNodeTree(Node* root, const char *letter)
{
    if (letter == NULL || *letter == '\0') {
        return;
    }
    Node* currentNode = root;
    if (root->nodes.count(*letter) < 1) {
        currentNode = new Node();
        root->nodes.insert(std::pair<char, Node*>(*letter, currentNode));
    }
    return getNodeTree(currentNode, ++letter);
}

void printNode(Node* root) {
    if (root == NULL || root->nodes.size() == 0) {
        return;
    }
    for(const auto node : root->nodes) {
        cout << (char) node.first << std::endl;
        printNode(node.second);
    }
}

int main()
{
    string word = "asdf";
    string word2 = "basf";
    Node root = Node();
    getNodeTree(&root, word.c_str());
    getNodeTree(&root, word2.c_str());
    printNode(&root);
    return 0;
}
