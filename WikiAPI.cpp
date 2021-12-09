#include "WikiAPI.hpp"

WikiAPI::WikiAPI(string wikiEndpoint) {
    setWiki(wikiEndpoint);
}

void WikiAPI::setWiki(string wikiEndpoint) {
    wiki=wikiEndpoint;
    search_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
    outgoing_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
    thumbnail_url=wiki+"api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";
}

string WikiAPI::getSearchList(string query) {
    
}

string WikiAPI::getOutgoingLinks(int pageID) {
    
}

string WikiAPI::getThumbnail(int pageID) {
    
}

