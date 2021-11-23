#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
using std::cout;
using std::string;
using std::map;
using std::ofstream;

class Node
{
public:
    Node(){ };
    map<char, Node*> nodes;
    char value = 0;
    bool isEnd;
    int id;
};

static Node emptyNode = Node();
int idCounter = 0;

char* unconstchar(const char* s) {
    if(!s)
      return NULL;
    int i;
    char* res = NULL;
    res = (char*) malloc(std::strlen(s)+1);
    if(!res){
        fprintf(stderr, "Memory Allocation Failed! Exiting...\n");
        exit(EXIT_FAILURE);
    } else{
        for (i = 0; s[i] != '\0'; i++) {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}

void getNodeTree(Node* root, const char *letter)
{
    if (letter == NULL || *letter == '\0') {
        return;
    }
    Node* currentNode = root;
    if (root->nodes.count(*letter) < 1) {
        currentNode = new Node();
        currentNode->value = *letter != 0 ? *unconstchar(letter) : 0;
        currentNode->id = idCounter;
        idCounter++;
        root->nodes.insert(std::pair<char, Node*>(*letter, currentNode));
    } else {
        currentNode = root->nodes.at(*letter);
    }
    return getNodeTree(currentNode, ++letter);
}

void printNodeTitles(Node* root, ofstream* output, std::vector<string>* included) {
    if (root == NULL) {
        return;
    }
    for (const auto currentRow : root->nodes) {
        auto currentNode = currentRow.second;
        *output << "    " << currentNode->id << " ";
        *output << "[ label=" << currentNode->value << " ]" << std::endl;
        included->push_back((string)&currentNode->value);
        printNodeTitles(currentNode, output, included);
    }
}

void printNode(Node* root, ofstream* output) {
    if (root == NULL) {
        return;
    }
    for (const auto row : root->nodes) {
        auto currentNode = row.second;
        *output << "   " << root->id << " -> " << currentNode->id << std::endl;
        printNode(currentNode, output);
    }
}

void dumpNodeToFile(Node* node, string filename) {
    cout << "dumping node to " << filename << std::endl;
    ofstream output;
    output.open(filename);
    output << "digraph D {" << std::endl;
    std::vector<string>* included = new std::vector<string>();
    included->push_back((string)&node->value);
    printNodeTitles(node, &output, included);
    delete included;
    output << std::endl;
    printNode(node, &output);
    output << "}" << std::endl;
}

int main()
{
    string word = "asdf";
    string word2 = "basf";
    string word3 = "avs";
    string word4 = "avs";
    emptyNode.id = idCounter;
    idCounter++;
    getNodeTree(&emptyNode, word.c_str());
    getNodeTree(&emptyNode, word2.c_str());
    getNodeTree(&emptyNode, word3.c_str());
    getNodeTree(&emptyNode, word4.c_str());
    dumpNodeToFile(&emptyNode, "trie.dot");
    return 0;
}
