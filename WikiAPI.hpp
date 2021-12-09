#pragma once
#include <string>
using std::string;

class WikiAPI{
private:
    static string wiki, search_url, outgoing_url, thumbnail_url;
public:
    WikiAPI(const string& wikiEndpoint);
    static void setWiki(const string& wikiEndpoint);
    static string getSearchList(const string& query);
    static string getOutgoingLinks(int pageID);
    static string getThumbnail(int pageID);
    static string getPageURL(const string& pageTitle);
};