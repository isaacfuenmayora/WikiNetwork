#pragma once
#include <string>
using std::string;

class WikiAPI{
private:
    static string wiki, search_url, outgoing_url, thumbnail_url;
public:
    WikiAPI(string wikiEndpoint);
    static void setWiki(string wikiEndpoint);
    static string getSearchList(string query);
    static string getOutgoingLinks(int pageID);
    static string getThumbnail(int pageID);
//    void setWiki(string wikiEndpoint);
//    string getSearchList(string query);
//    string getOutgoingLinks(int pageID);
//    string getThumbnail(int pageID);
};