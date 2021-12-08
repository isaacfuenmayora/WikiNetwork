#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
using std::vector;
using std::string;
using std::unordered_map;
using std::queue;

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
    Graph(int srcID, string srcTitle);
    //sets current node to existing node
    void setCurrNode(int id);
    //creates an edge from current node to existing node
    void connectOutNode(int id);
    //creates an edge from current node to a new node
    void insertOutNode(int id, string title);
    //performs breadthFirstSearch from current node to find existing node with targetID
    void breadthFirstSearch(int targetID); 
};