#include <string>
using namespace std;

class WikiAPI{
private:
    string wiki, search_url, links_url, thumbnail_url;
public:
    WikiAPI(string w){
        wiki=w;
        search_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=prefixsearch&gpslimit=10&prop=pageimages|pageterms&piprop=thumbnail&pithumbsize=50&pilimit=10&pilicense=any&wbptterms=description&redirects=&gpssearch=";
        links_url=wiki+"api.php?format=json&formatversion=2&action=query&generator=links&gpllimit=500&gplnamespace=0&redirects=&pageids=";
        thumbnail_url=wiki+"api.php?format=json&formatversion=2&action=query&prop=pageimages&piprop=original&pilicense=any&titles=";
    }
    
};