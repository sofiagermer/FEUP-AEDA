#include "Gallery.h"
#include <ostream>
#include <algorithm>

using namespace std;

Gallery::Gallery(vector<Paint*> c): catalog(PaintCatalogItem("", "", 0, 0.00)), collection(c) {

}

vector<Paint*> Gallery::getCollection() const {
    return collection;
}

void Gallery::setCollection(vector<Paint*> c) {
    collection = c;
}

priority_queue<ExhibitionItem> Gallery::getPaintsToShow() const {
    return paintsToShow;
}
HashTableAuthorRecord Gallery::getAuthorRecords () const {
    return  authorRecords;
}

void Gallery::addAuthorRecord(AuthorRecord ar) {
    authorRecords.insert(ar);
}

void Gallery::generateCatalog() {
    catalog.makeEmpty();
    for(int i = 0; i < collection.size(); i++) {
        catalog.insert(collection[i]);
    }
}

BST<PaintCatalogItem> Gallery::getCatalog() const {
    return catalog;
}


void Gallery::prepareExhibition() {
    while( !paintsToShow.empty())
        paintsToShow.pop();
    for(int i = 0; i < collection.size(); i++) {
        ExhibitionItem ei(collection[i]);
        paintsToShow.push(ei);
    }
}

//-------------------------------------------------------------------------------

//TODO

vector<Paint*> Gallery::getPaintsBy(string a) const {
    vector<Paint*> pinturas_a;
    if(catalog.isEmpty()){
        return pinturas_a;
    }
    BSTItrIn<PaintCatalogItem> it (catalog);
    while(!it.isAtEnd()){
        if(it.retrieve().getAuthor() == a){
            pinturas_a.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    /*
    auto comp = [] (Paint *pci1, Paint *pci2){
        if(pci1->getYear() == pci2->getYear() && pci1->getAuthor() == pci2->getAuthor()){
            return pci1->getTitle() < pci2->getTitle();
        }
        if(pci1->getYear() == pci2->getYear()){
            return pci1->getAuthor() < pci2->getAuthor();
        }
        return pci1->getYear() >pci2->getYear();
    };
    sort(pinturas_a.begin(), pinturas_a.end(), comp);*/
    return pinturas_a;

}

//TODO
vector<Paint*> Gallery::getPaintsBetween(int y1, int y2) const {
    vector<Paint*> tmp;
    if(catalog.isEmpty()){
        return tmp;
    }
    BSTItrLevel<PaintCatalogItem> it (catalog);
    while(!it.isAtEnd()){
        if(it.retrieve().getYear() > y1 && it.retrieve().getYear() < y2){
            tmp.push_back(it.retrieve().getPaint());
        }
        it.advance();
    }
    auto comp = [] (Paint *pci1, Paint *pci2){
        if(pci1->getYear() == pci2->getYear() && pci1->getAuthor() == pci2->getAuthor()){
            return pci1->getTitle() < pci2->getTitle();
        }
        if(pci1->getYear() == pci2->getYear()){
            return pci1->getAuthor() < pci2->getAuthor();
        }
        return pci1->getYear() >pci2->getYear();
    };
    sort(tmp.begin(), tmp.end(), comp);
    return tmp;
}

//TODO
bool Gallery::updateTitle(Paint* p, string tnew) {
    PaintCatalogItem sofi(p);
    if(!catalog.remove(sofi)){
        return false;
    }
    PaintCatalogItem new_paint(p->getAuthor(),tnew,p->getYear(),p->getPrice());
    catalog.insert(new_paint);
    return true;
}


//TODO
int Gallery::recordAvailablePainters() { //carrega a tabela de dispersao com AuthorRecords
    for(auto x: collection){
        auto it = authorRecords.find(x->getAuthor());
        if(it != authorRecords.end()) {
            AuthorRecord novo(it->getAuthor(), it->getAvailablePaints() + 1, it->getTotalSells());
            authorRecords.erase(it);
            authorRecords.insert(novo);
        }
        else{
            AuthorRecord novo(x->getAuthor(), 1, 0);
            authorRecords.insert(novo);
        }
    }
    return authorRecords.size();
}

//TODO
double Gallery::totalSells() const {
    double total_sells = 0;
    auto it = authorRecords.begin();
    while(it != authorRecords.end()){
        total_sells += it->getTotalSells();
        it++;
    }
    return total_sells;

}

//TODO
double Gallery::sellPaint(string a, string t) {
    double total_price = 0;
    for(auto it= collection.begin(); it != collection.end();){
       if((*it)->getAuthor() == a && (*it)->getTitle() == t){
           auto rec = authorRecords.find(a);
           if(rec != authorRecords.end()) {
               AuthorRecord novo(a, rec->getAvailablePaints() + 1, rec->getTotalSells() +  (*it)->getPrice());
               authorRecords.erase(rec);
               authorRecords.insert(novo);
               total_price += (*it)->getPrice();
           }
           else{
               AuthorRecord novo(a, 1, 0);
               authorRecords.insert(novo);
               total_price += (*it)->getPrice();
           }
           collection.erase(it);
       }
       else{
           it++;
       }
    }
    return total_price;
}

//TODO
vector<Paint*> Gallery::nBestExibition(int n, int maxPerYear) {  //escolhe as N mais caras pinturas, dos anos mais antigos, para realizar uma exposição
    vector<Paint*> temp;
    if(paintsToShow.empty()){
        return temp;
    }
    priority_queue<ExhibitionItem> tmp_queue;
    int counter = 0;
    int year = paintsToShow.top().getYear();
    int paint_that_year = 0;
    while(!paintsToShow.empty()){
        if(counter < n){
            if(paintsToShow.top().getYear() != year){
                year = paintsToShow.top().getYear();
                paint_that_year = 0;
            }
            if(paint_that_year < maxPerYear){
                counter++;
                paint_that_year++;
                temp.push_back(paintsToShow.top().getPaint());
                paintsToShow.pop();
            }
            else{
                tmp_queue.push(paintsToShow.top());
                paintsToShow.pop();
            }

        }
        else{
            tmp_queue.push(paintsToShow.top());
            paintsToShow.pop();
        }
    }
    paintsToShow = tmp_queue;
    return temp;
}

//TODO
int Gallery::itemExibitionOrder(string a, string t) {
    int order = 0;
    int counter = 1;
    priority_queue<ExhibitionItem> temp;
    while(!paintsToShow.empty()){
        if(paintsToShow.top().getAuthor() == a && paintsToShow.top().getTitle() == t){
            order = counter;
        }
        temp.push(paintsToShow.top());
        paintsToShow.pop();
        counter++;
    }
    paintsToShow = temp;
    return order;
}


/*
int Gallery::itemExibitionOrder(string a, string t) {
    int order = 0;
    int counter = 1;
    priority_queue<ExhibitionItem> tmpPrioQ;
    while(!paintsToShow.empty()){
        auto elem = paintsToShow.top();
        tmpPrioQ.push(elem);
        paintsToShow.pop();
        if(elem.getAuthor() == a && elem.getTitle() == t){
            order = counter;
        }
        counter++;
    }
    paintsToShow = tmpPrioQ;
    return order;
}
*/
