#include "WikiAPI.hpp"
#include "Graph.hpp"
#include <iostream>
#define NUMWIKIS 12
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::pair;

string displayWikiMenu(const vector<string>& wikis){
    cout << "Please enter the corresponding number for which wiki you would like to choose." << endl;
    for(int i=1; i<wikis.size(); i++){
        cout << i <<  (i>=10 ? ". ":".  ") << wikis[i] << endl;
    }
    string wikiIndex;
    getline(cin,wikiIndex);
    return wikis[stoi(wikiIndex)];
}

pair<int,string> chooseArticle(string articleTitle){
    vector<pair<int, string>> v;
    string text=WikiAPI::getSearchList(articleTitle);
    string p = "\"pageid\"";
    string t = "\"title\"";
    int loc = text.find(p,0);
    while(loc!=string::npos){
        int pos = loc + 9;
        int id = stoi(text.substr(pos, text.find(",", pos) - pos));
        loc=text.find(t, pos);
        pos = loc + 9;
        string title = text.substr(pos, text.find("\"", pos)-pos);
        v.emplace_back(id,title);
        loc = text.find(p,pos);
    }
    cout << "Please enter the corresponding number for which article you would like to choose." << endl;
    for(unsigned int i=1; i<=v.size(); i++){
        cout << i <<  (i>=10 ? ". ":".  ") << v[i-1].second << endl;
    }
    string articleIndexstr;
    getline(cin, articleIndexstr);
    return v[stoi(articleIndexstr)-1];
}

int main(){
    vector<string> wikis(NUMWIKIS);
    wikis[1]="https://en.wikipedia.org/";
    wikis[2]="https://simple.wikipedia.org/";
    wikis[3]="https://en.wiktionary.org/";
    wikis[4]="https://simple.wiktionary.org/";
    wikis[5]="https://en.wikiquote.org/";
    wikis[6]="https://en.wikinews.org/";
    wikis[7]="https://en.wikisource.org/";
    wikis[8]="https://en.wikibooks.org/";
    wikis[9]="https://en.wikiversity.org/";
    wikis[10]="https://species.wikimedia.org/";
    wikis[11]="https://en.wikivoyage.org/";
    WikiAPI::setWiki(displayWikiMenu(wikis));
    Graph g;
    string cont="Y";
    while(cont[0]=='Y') {
        cout << "Search for your starting article:" << endl;
        string article;
        getline(cin, article);
        pair<int, string> srcPage = chooseArticle(article);
        cout << "Search for your ending article:" << endl;
        getline(cin, article);
        pair<int, string> endPage = chooseArticle(article);
        cout << "Would you like to conduct a breadth first (0) or iterative deepening depth first (1) search for the shortest path?" << endl;
        string searchstr;
        int search;
        getline(cin, searchstr);
        search=stoi(searchstr);
        vector<int> path;
        if(search==0)
            path = g.breadthFirstSearchOut(srcPage.first,srcPage.second,endPage.first);
        else {
            cout << "Enter value for max depth:" << endl;
            string depthstr;
            int depth;
            getline(cin, depthstr);
            depth=stoi(depthstr);
            path = g.iterativeDeepeningDepthSearchOut(srcPage.first,srcPage.second,endPage.first, depth);
        }
        cout << "This is the shortest path:" << endl;
        for(int id:path){
            string title=g.getTitle(id);
            cout << title << " (" << WikiAPI::getPageURL(title) << ")" << endl;
        }
        cout << endl << "Would you like to make another shortest path search? (Y/N)" << endl;
        getline(cin, cont);
    }
    return 0;
}