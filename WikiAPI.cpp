#include "WikiAPI.hpp"
#include <cpr/cpr.h>
using cpr::Get;
using cpr::Url;
using cpr::Response;
using std::to_string;

string WikiAPI::wiki="https://simple.wikipedia.org/";
string WikiAPI::outgoing_url="https://simple.wikipedia.org/w/api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
string WikiAPI::search_url="https://simple.wikipedia.org/w/api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
string WikiAPI::thumbnail_url="api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";

string formatTitle(string& title){
    string linkTitle;
    for(int i=0; i<title.size(); i++){
        if(title[i]==' ')
            linkTitle+="%20";
        else if(title[i]=='!')
            linkTitle+="%21";
        else if(title[i]=='\'')
            linkTitle+="%27";
        else if(title[i]=='(')
            linkTitle+="%28";
        else if(title[i]==')')
            linkTitle+="%29";
        else if(title[i]==',')
            linkTitle+="%2C";
        else
            linkTitle.push_back(title[i]);
    }
    return linkTitle;
}

WikiAPI::WikiAPI(const string& wikiEndpoint) {
    setWiki(wikiEndpoint);
}

void WikiAPI::setWiki(const string& wikiEndpoint) {
    wiki=wikiEndpoint;
    search_url=wiki+"w/api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
    outgoing_url=wiki+"w/api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
    thumbnail_url=wiki+"w/api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";
}
void WikiAPI::setWiki(string&& wikiEndpoint) {
    wiki=wikiEndpoint;
    search_url=wiki+"w/api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
    outgoing_url=wiki+"w/api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
    thumbnail_url=wiki+"w/api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";
}
//TODO: Implement handling errors
string WikiAPI::getSearchList(string& query) {
    Response r = Get(Url{search_url+formatTitle(query)});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}
string WikiAPI::getSearchList(string&& query) {
    Response r = Get(Url{search_url+formatTitle(query)});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}

string WikiAPI::getOutgoingLinks(int pageID) {
    Response r = Get(Url{outgoing_url+to_string(pageID)});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}
string WikiAPI::getOutgoingLinks(int pageID, string&& gplcontinue) {
    Response r = Get(Url{outgoing_url+to_string(pageID)+"&gplcontinue="+gplcontinue});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}

string WikiAPI::getOutgoingLinks(int pageID, string& gplcontinue) {
    Response r = Get(Url{outgoing_url+to_string(pageID)+"&gplcontinue="+gplcontinue});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}

string WikiAPI::getThumbnail(int pageID) {
    Response r = Get(Url{thumbnail_url+to_string(pageID)});
    switch(r.status_code) {
        case 200:
            return r.text;
        default:
            return "error";
    }
}

string WikiAPI::getPageURL(string& pageTitle) {
    pageTitle=formatTitle(pageTitle);
    return wiki+"wiki/"+pageTitle;
}
string WikiAPI::getPageURL(string&& pageTitle) {
    pageTitle=formatTitle(pageTitle);
    return wiki+"wiki/"+pageTitle;
}