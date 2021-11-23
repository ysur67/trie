#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <vector>
using std::cout;
using std::map;
using std::ofstream;
using std::string;

class Node
{
public:
    Node(){};
    map<char, Node *> nodes;
    char value = 0;
    bool isEnd;
    int id;
};

static Node emptyNode = Node();
int idCounter = 0;

char *unconstchar(const char *s)
{
    if (!s)
        return NULL;
    int i;
    char *res = NULL;
    res = (char *)malloc(std::strlen(s) + 1);
    if (!res)
    {
        fprintf(stderr, "Memory Allocation Failed! Exiting...\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (i = 0; s[i] != '\0'; i++)
        {
            res[i] = s[i];
        }
        res[i] = '\0';
        return res;
    }
}

void insertInTrie(Node *root, const char *letter)
{
    if (letter == NULL || *letter == '\0')
    {
        return;
    }
    Node *currentNode = root;
    if (root->nodes.count(*letter) < 1)
    {
        currentNode = new Node();
        currentNode->value = *letter != 0 ? *unconstchar(letter) : 0;
        currentNode->id = idCounter;
        idCounter++;
        root->nodes.insert(std::pair<char, Node *>(*letter, currentNode));
    }
    else
    {
        currentNode = root->nodes.at(*letter);
    }
    return insertInTrie(currentNode, ++letter);
}

void printHeaderOfDot(Node *root, ofstream *output)
{
    if (root == NULL)
    {
        return;
    }
    for (const auto currentRow : root->nodes)
    {
        auto currentNode = currentRow.second;
        *output << "    " << currentNode->id << " ";
        *output << "[ label=" << currentNode->value << " ]" << std::endl;
        printHeaderOfDot(currentNode, output);
    }
}

void printNode(Node *root, ofstream *output)
{
    if (root == NULL)
    {
        return;
    }
    for (const auto row : root->nodes)
    {
        auto currentNode = row.second;
        *output << "   " << root->id << " -> " << currentNode->id << std::endl;
        printNode(currentNode, output);
    }
}

void dumpNodeToFile(Node *node, string filename)
{
    cout << "dumping node to " << filename << std::endl;
    ofstream output;
    output.open(filename);
    output << "digraph D {" << std::endl;
    printHeaderOfDot(node, &output);
    output << std::endl;
    printNode(node, &output);
    output << "}" << std::endl;
}

int main()
{
    string trieWords[30] = {
        "bad", "easy", "lol", "hurt", "rule", "code", "hate", "coffee", "ice",
        "fire", "icecream", "hangman", "destroy", "computer", "book",
        "dictionary", "technology", "power", "thunder", "controller",
        "dexterity", "keyboard", "thunderous", "lizard", "hazardous",
        "algorithm", "destruction", "operation", "assignment", "despicable"
    };
    emptyNode.id = idCounter;
    idCounter++;
    for (auto word : trieWords)
    {
        insertInTrie(&emptyNode, word.c_str());
    }
    dumpNodeToFile(&emptyNode, "trie.dot");
    return 0;
}
