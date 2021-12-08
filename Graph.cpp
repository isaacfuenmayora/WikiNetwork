#include "Graph.hpp";

Graph::Graph(int srcID, string srcTitle)
{
    currNode = adjList[srcID] = new Node(srcID, srcTitle);
}

void Graph::setCurrNode(int id) {
    currNode = adjList[id];
}

void Graph::insertNode(int id, string title, bool outgoing) {
    if(outgoing)
        currNode->outgoingNodes.push_back(new Node(id, title, currNode));
    //TODO: implement incomingNodes
    // else
    //     currNode->incomingNodes.push_back(new Node(id, title));
}

Graph::Node::Node(int id, string title, Node* prev)
    : id(id),
      title(title),
      prev(prev)
{}