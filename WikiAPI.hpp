#pragma once
#include <string>
using std::string;

class WikiAPI{
private:
    static string wiki, search_url, outgoing_url, thumbnail_url;
public:
    WikiAPI(const string& wikiEndpoint);
    static void setWiki(const string& wikiEndpoint);
    static void setWiki(string&& wikiEndpoint);
    static string getSearchList(string& query);
    static string getSearchList(string&& query);
    static string getOutgoingLinks(int pageID);
    static string getOutgoingLinks(int pageID, string&& gplcontinue);
    static string getOutgoingLinks(int pageID, string& gplcontinue);
    static string getThumbnail(int pageID);
    static string getPageURL(string& pageTitle);
    static string getPageURL(string&& pageTitle);
};