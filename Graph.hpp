#pragma once
#include <unordered_map>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::unordered_map;

class Graph{
private:
    struct Node{
        int id;
        string title;
        vector<Node*> outgoingNodes, incomingNodes;
        bool hasAllOutgoing = false;
        //optimal previous node for shortest path
        Node* prev;
        Node(int id, string title, Node* prev=nullptr);
    };
    //use IDs to get Node
    unordered_map<int, Node*> adjList;
    //source/current Node
    Node* currNode;
    //returns true if graph contains node with id
    bool contains(int id);
    //creates and sets current node
    void emplaceSourceNode(int id, string title);
    //sets current node to existing node
    void setSourceNode(int id);
    //creates an edge from current node to a new outgoing node
    void emplaceOutNode(int id, string title);
    //creates an edge from current node to existing node
    void connectOutNode(int id);
    //uses WikiAPI to get all outgoing links for the current node
    void connectToOutgoingLinks();
    //gets path from src to target by traversing *prev nodes from src
    vector<int> getPrevPathTo(Node* src, Node* dest);
public:
    Graph();
    Graph(int srcID, string srcTitle);
    //gets a page's title from its id
    const string& getTitle(int id);
    //performs bfs from current node to find all shortests paths to node with targetID
    //returns list of ids in path order
    vector<int> breadthFirstSearchOut(int srcID, string srcTitle, int targetID);
    vector<int> iterativeDeepeningDepthSearchOut(int srcID, string srcTitle, int targetID, int maxDepth);
};