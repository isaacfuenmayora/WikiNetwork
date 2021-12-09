#include "Graph.hpp"
#include "WikiAPI.hpp"
#include <queue>
#include <unordered_set>
using std::move;

Graph::Graph(int srcID, string srcTitle)
{
    emplaceSourceNode(srcID,srcTitle);
}

const string& Graph::getTitle(int id) {
    return adjList[id]->title;
}

bool Graph::contains(int id) {
    return adjList.find(id)!=adjList.end();
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

void Graph::connectToOutgoingLinks() { //TODO: finish
    
}

vector<int> Graph::getPrevPathTo(Node* src, Node* dest) {
    vector<int> path;
    while(src!=dest){
        path.push_back(src->id);
        src=src->prev;
    }
    path.push_back(src->id);
    return path;
}

void Graph::emplaceOutNode(int id, string title) {
    currNode->outgoingNodes.push_back(adjList[id] = new Node(id, title, currNode));
}

vector<int> Graph::breadthFirstSearchOut(int srcID, int targetID) {
    setSourceNode(srcID);
//    queue<Node*> nodes({currNode});
//    unordered_set<Node*> visited({currNode});
//    while(!nodes.empty()){
//        currNode = nodes.front(); nodes.pop();
//        //if this node hasn't gotten its outgoing links, get them first
//        if(currNode->outgoingNodes.empty())
//            connectToOutgoingLinks();
//        //iterate through the current Node's outgoing links
//        for(Node* out: currNode->outgoingNodes){
//            //if found, get path and return it
//            if(out->id=targetID)
//                return move(getPrevPathTo(out, adjList[srcID]));
//            //if we haven't encountered it,make its prev the currNode and add it to visited
//            if(visited.insert(out).second){
//                nodes.push(out);
//                out->prev=currNode;
//            }
//        }
//    }
    return {};
}

Graph::Node::Node(int id, string title, Node* prev)
    : id(id),
      title(title),
      prev(prev)
{}