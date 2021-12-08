#pragma once
#include <unordered_map>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::unordered_map;

class Graph{
    struct Node{
        int id;
        string title, thumbURL, pageURL;
        vector<Node*> outgoingNodes, incomingNodes;
        //optimal previous node for shortest path
        Node* prev; //TODO: check if this is best
        Node(int id, string title, Node* prev=nullptr);
    };
    //use IDs to get Node
    unordered_map<int, Node*> adjList;
    Node* currNode;
public:

    Graph(int srcIDthe , string srcTitle);
    void setCurrNode(int id);
    //creates an edge from current node to this new node
    void insertNode(int id, string title, bool outgoing = true);
    void breadthSearch(int targetID); //TODO: think this through
};