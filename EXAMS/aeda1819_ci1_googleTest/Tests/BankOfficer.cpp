/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

unsigned int BankOfficer::ID= 0;

// a alterar
BankOfficer::BankOfficer(string name) {
    ID++;
    id = ID;
}

bool BankOfficer::operator>(BankOfficer &ba) {
    if( myAccounts.size() > ba.myAccounts.size() ){
        return true;
    }
    else if(myAccounts.size() < ba.myAccounts.size()){
        return false;
    }
    else{
        if(name > ba.getName()){
            return true;
        }
        return false;
    }
}



