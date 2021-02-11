/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(int i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {
    for(auto &b: books){
        BookCatalogItem wanted (b->getTitle(),b->getAuthor(),b->getYear());
        BookCatalogItem existent = catalogItems.find(wanted);
        if(existent == wanted){
            wanted.setItems(existent.getItems());
            wanted.addItems(b);
            catalogItems.remove(wanted);
            catalogItems.insert(wanted);
        }
        else{
            wanted.addItems(b);
            catalogItems.insert(wanted);
        }
    }
}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;
    BSTItrIn<BookCatalogItem> it (catalogItems);
    while(!it.isAtEnd()){
        if(it.retrieve().getAuthor() == book->getAuthor() && it.retrieve().getTitle() == book->getTitle()){
            for(auto b: it.retrieve().getItems()){
                if(b->getReader() == NULL){
                    temp.push_back(b);
                }
            }
        }
        it.advance();
    }

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
    BookCatalogItem wanted (book->getTitle(),book->getAuthor(),book->getYear());
    BookCatalogItem existent = catalogItems.find(wanted);
    if(wanted == existent){
        for(auto x: existent.getItems()){
            if(x->getReader() == NULL){
                reader->addReading(x->getTitle(),x->getAuthor());
                book->setReader(reader);
                return true;
            }
        }
        return false;
    }
    else{
        return false;
    }
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
        userRecords.insert(UserRecord(user));
}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
    user->setEMail(newEMail);
    auto it = userRecords.find(UserRecord(user));
    if(it != userRecords.end()){
        userRecords.erase(it);
    }
    userRecords.insert(user);
}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
    for(auto c: candidates){
        if(c.numReadings() >= min){
            readerCandidates.push(c);
        }
    }
}

int ReadingClub::awardReaderChampion(User& champion) {
	priority_queue<User> temp = readerCandidates;
	User one = temp.top();
	temp.pop();
	User two = temp.top();
	if(one.numReadings() == two.numReadings()){
	    return 0;
	}
	champion = one;
	return readerCandidates.size();
}
























