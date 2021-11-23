#include <string>
#include <iostream>
#include <map>
using std::cout;
using std::string;
using std::map;

class Node
{
public:
    Node(char* value = NULL){
        this->value = value;
    };
    char* value;
    map<char, Node*> nodes;
    bool isEnd;
};

Node* getNodeTree(Node* node, const char *letter)
{
    if (letter == NULL || *letter == '\0') {
        return node;
    }
    if (node->nodes.count(*letter) < 1) {
        node->nodes.insert(std::pair<char, Node*>(*letter, new Node((char*)letter)));
    }
    letter++;
    return getNodeTree(node, letter);
}

void printNode(Node* node) {
    if (node == NULL || node->nodes.size() == 0) {
        return;
    }
    cout << node->value << std::endl;
    for(const auto s : node->nodes) {
        cout << (char) s.first << std::endl;
        printNode(s.second);
    }
}

int main()
{
    string word = "asdf";
    Node root = Node();
    Node* node = getNodeTree(&root, word.c_str());
    printNode(node);
    return 0;
}
