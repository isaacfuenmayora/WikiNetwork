#include "WikiAPI.hpp"
#include <cpr/cpr.h>
using cpr::Get;
using cpr::Url;
using cpr::Response;
WikiAPI::WikiAPI(string wikiEndpoint) {
    setWiki(wikiEndpoint);
}

void WikiAPI::setWiki(string wikiEndpoint) {
    wiki=wikiEndpoint;
    search_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
    outgoing_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
    thumbnail_url=wiki+"api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";
}
//TODO: Implement handling errors
string WikiAPI::getSearchList(string query) {
    Response r = Get(Url{search_url+query});
    if(r.status_code==200)
        return r.text;
    else
        return "error";
}

string WikiAPI::getOutgoingLinks(int pageID) {
    Response r = Get(Url{outgoing_url+to_string(pageID)});
    if(r.status_code==200)
        return r.text;
    else
        return "error";
}

string WikiAPI::getThumbnail(int pageID) {
    Response r = Get(Url{thumbnail_url+to_string(pageID)});
    if(r.status_code==200)
        return r.text;
    else
        return "error";
}


