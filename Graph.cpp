#include "Graph.hpp";

Graph::Graph(int srcID, string srcTitle)
{
    currNode = adjList[srcID] = new Node(srcID, srcTitle);
}

void Graph::setCurrNode(int id) {
    currNode = adjList[id];
}

void Graph::connectOutNode(int id) {
    currNode->outgoingNodes.push_back(adjList[id]);
}

void Graph::insertOutNode(int id, string title) {
    currNode->outgoingNodes.push_back(new Node(id, title, currNode));
}

void Graph::breadthFirstSearch(int targetID) {
    queue<Node*> nodes({currNode});
    //TODO: finish this
}

Graph::Node::Node(int id, string title, Node* prev)
    : id(id),
      title(title),
      prev(prev)
{}