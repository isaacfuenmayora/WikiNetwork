#include "WikiAPI.hpp"
#include "Graph.hpp"
#include <iostream>
#define NUMWIKIS 12
using std::cout;
using std::cin;
using std::endl;
using std::stoi;
using std::pair;

string takeStringInput(){
    string x;
    getline(cin, x);
    return x;
}

int takeIntInput(int a, int b) {
    string input;
    int num;
    while(true) {
        try {
            getline(cin, input);
            num = stoi(input);
            while (num <= a && num >= b) {
                cout << "Input must be an integer in the range [" << a << ", " << b << "]" << endl;
                getline(cin, input);
                num = stoi(input);
            }
            return num;
        }
        catch (...) {
            cout << "Input must be an integer in the range [" << a << ", " << b << "]" << endl;
        }
    }
}


string displayWikiMenu(const vector<string>& wikis){
    cout << "Please enter the corresponding number for which wiki you would like to choose." << endl;
    for(int i=1; i<wikis.size(); i++){
        cout << '\t' << i <<  (i>=10 ? ". ":".  ") << wikis[i] << endl;
    }
    int wikiIndex= takeIntInput(1, wikis.size()-1);
    return wikis[wikiIndex];
}

pair<int,string> chooseArticle(string articleTitle){
    vector<pair<int, string>> v;
    string text=WikiAPI::getSearchList(articleTitle);
    string p = "\"pageid\"";
    string t = "\"title\"";
    int loc = text.find(p,0);
    while(loc!=string::npos){
        int pos = loc + 9;
        int id = stoi(text.substr(pos, text.find(',', pos) - pos));
        loc=text.find(t, pos);
        pos = loc + 9;
        string title = text.substr(pos, text.find('\"', pos)-pos);
        v.emplace_back(id,title);
        loc = text.find(p,pos);
    }
    cout << "Please enter the corresponding number for which article you would like to choose." << endl;
    for(unsigned int i=1; i<=v.size(); i++){
        cout << '\t' << i <<  (i>=10 ? ". ":".  ") << v[i-1].second << endl;
    }
    int articleIndex=takeIntInput(1, v.size());
    return v[articleIndex-1];
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
        string article = takeStringInput();
        pair<int, string> srcPage = chooseArticle(article);
        cout << "Search for your ending article:" << endl;
        article=takeStringInput();
        pair<int, string> endPage = chooseArticle(article);
        cout << "Would you like to conduct a breadth first (0) or iterative deepening depth first (1) search for the shortest path?" << endl;
        int search = takeIntInput(0,1);
        vector<int> path;
        if(search==0)
            path = g.breadthFirstSearchOut(srcPage.first,srcPage.second,endPage.first);
        else {
            cout << "Enter value for max depth:" << endl;
            int depth = takeIntInput(1,20);
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