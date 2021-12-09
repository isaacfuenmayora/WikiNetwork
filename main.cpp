#include "WikiAPI.hpp"
#include "Graph.hpp"
#include <iostream>
using std::cout;
using std::endl;

int main(){
    WikiAPI::setWiki("https://en.wikipedia.org/w/");
    cout << WikiAPI::getSearchList("Spider-M");
    return 0;
}
