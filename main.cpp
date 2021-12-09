#include "WikiAPI.hpp"
#include "Graph.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    string wiki="https://simple.wikipedia.org/w/";
    WikiAPI wa(wiki);
    string body=wa.getOutgoingLinks(22654);
    cout << body << endl;
    return 0;
}
