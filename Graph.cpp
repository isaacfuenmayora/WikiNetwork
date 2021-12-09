#include "Graph.hpp";

Graph::Graph(int srcID, string srcTitle)
{
    emplaceSourceNode(srcID,srcTitle);
}

void Graph::emplaceSourceNode(int id, string title) {
    currNode = adjList[id] = new Node(id, title);
}

void Graph::setSourceNode(int id) {
    currNode = adjList[id];
}

void Graph::connectOutNode(int id) {
    currNode->outgoingNodes.push_back(adjList[id]);
}

void Graph::emplaceOutNode(int id, string title) {
    currNode->outgoingNodes.push_back(adjList[id] = new Node(id, title, currNode));
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