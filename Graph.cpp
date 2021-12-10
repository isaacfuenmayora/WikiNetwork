#include "Graph.hpp"
#include "WikiAPI.hpp"
#include <queue>
#include <stack>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <utility>
using std::move;
using std::queue;
using std::stack;
using std::unordered_set;
using std::pair;
using std::cout;
using std::endl;

Graph::Graph():currNode(nullptr) {}

Graph::Graph(int srcID, string srcTitle)
{
    emplaceSourceNode(srcID,move(srcTitle));
}

Graph::~Graph() {
    for(auto& idNode: adjList)
        delete idNode.second;
}

const string& Graph::getTitle(int id) {
    return adjList[id]->title;
}

bool Graph::contains(int id) {
    return adjList.find(id)!=adjList.end();
}

void Graph::emplaceSourceNode(int id, string title) {
    currNode = adjList[id] = new Node(id, move(title));
}

void Graph::setSourceNode(int id) {
    currNode = adjList[id];
}

void Graph::connectOutNode(int id) {
    currNode->outgoingNodes.push_back(adjList[id]);
}

void Graph::connectToOutgoingLinks(bool displayPages) { //TODO: implement showing pages
    currNode->hasAllOutgoing=true;
    if(displayPages && currNode->prev) cout<< currNode->prev->title+" -> "+currNode->title <<endl;
    string text=WikiAPI::getOutgoingLinks(currNode->id);
    string g="\"gplcontinue\"";
    string p = "\"pageid\"";
    string t = "\"title\"";
    bool hasCont=false;
    string gplcont;
    int loc = text.find(g,0);
    do{
        if(loc!=string::npos) {
            loc=loc+15;
            hasCont = true;
            gplcont = text.substr(loc,text.find('\"', loc) - loc);
        }
        else
            hasCont=false;
        loc = text.find(p,0);
        while (loc != string::npos) {
            int pos = loc + 9;
            int id = stoi(text.substr(pos, text.find(',', pos) - pos));
            loc=text.find(t, pos);
            pos = loc + 9;
            if(adjList.find(id)==adjList.end()) {
                string title = text.substr(pos, text.find('\"', pos) - pos);
                emplaceOutNode(id, title);
            }
            else
                connectOutNode(id);
            loc = text.find(p,pos);
        }
        if(hasCont) {
            text = WikiAPI::getOutgoingLinks(currNode->id, gplcont);
            loc=text.find(g,0);
        }
    }while(hasCont);
}

vector<int> Graph::getPrevPathTo(Node* src, Node* dest) {
    vector<int> path;
    while(src!=dest){//TODO: explore efficiency
        path.push_back(src->id);
        src=src->prev;
    }
    path.push_back(src->id);
    std::reverse(path.begin(),path.end());
    return path;
}

void Graph::emplaceOutNode(int id, string title) {
    currNode->outgoingNodes.push_back(adjList[id] = new Node(id, move(title), currNode));
}

vector<int> Graph::breadthFirstSearchOut(int srcID, string srcTitle, int targetID, bool displayPages) {
    if(contains(srcID))
        setSourceNode(srcID);
    else
        emplaceSourceNode(srcID,move(srcTitle));
    queue<Node*> nodes({currNode});
    unordered_set<Node*> visited({currNode});
    while(!nodes.empty()){
        currNode = nodes.front(); nodes.pop();
        //if this node hasn't gotten its outgoing links, get them first
        if(!currNode->hasAllOutgoing)
            connectToOutgoingLinks(displayPages);
        //iterate through the current Node's outgoing links
        for(Node* out: currNode->outgoingNodes){
            //if found, get path and return it
            if(out->id==targetID)
                return move(getPrevPathTo(out, adjList[srcID]));
            //if we haven't encountered it,make its prev the currNode and add it to visited
            if(visited.insert(out).second){
                nodes.push(out);
                out->prev=currNode;
            }
        }
    }
    return {};
}

vector<int> Graph::iterativeDeepeningDepthSearchOut(int srcID, string srcTitle, int targetID, int maxDepth, bool displayPages) {
    if(contains(srcID))
        setSourceNode(srcID);
    else
        emplaceSourceNode(srcID,move(srcTitle));
    stack<pair<Node*,int>> nodeDepths;
    nodeDepths.push({currNode, 0});
    unordered_set<Node*> visited({currNode});
    while(!nodeDepths.empty()){
        currNode = nodeDepths.top().first;
        int depth = nodeDepths.top().second;
        nodeDepths.pop();
        //if this node hasn't gotten its outgoing links, get them first
        if(!currNode->hasAllOutgoing)
            connectToOutgoingLinks(displayPages);
        //iterate through the current Node's outgoing links
        if(depth<maxDepth) for(Node* out: currNode->outgoingNodes){
            //if found, get path and return it
            if(out->id==targetID)
                return move(getPrevPathTo(out, adjList[srcID]));
            //if we haven't encountered it,make its prev the currNode and add it to visited
            if(visited.insert(out).second){
                nodeDepths.push({out,depth+1});
                out->prev=currNode;
            }
        }
    }
    return {};
}

Graph::Node::Node(int id, string title, Node* prev)
    : id(id),
      title(title),
      prev(prev)
{}