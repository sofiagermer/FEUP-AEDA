/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>



Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double total = 0;
	for(const auto a : accounts){
	    if(a->getCodH() == cod1){
            total += a->getWithdraw();
	    }
	}
	return total;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
    vector <Account * > myaccounts;
    int aux = 0;
	for( auto &bo : bankOfficers){
	    if( bo.getName() == name){
	        for(auto *ac : bo.getAccounts()){
	            myaccounts.push_back(ac);
	        }
	        bankOfficers.erase(bankOfficers.begin() + aux);
	        aux++;
	    }
	}
	return myaccounts;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    for(auto &ba : bankOfficers){
        if(ba.getName() == name){
            ba.addAccount(ac);
            return ba;
        }
    }
    throw NoBankOfficerException(name);

}


// a alterar
void Bank::sortAccounts() {
    auto comp = [] ( Account *ac1, Account *ac2){
        if(ac1->getBalance() == ac2->getBalance()){
            return ac1->getCodIBAN() < ac2->getCodIBAN();
        }
        return ac1->getBalance() < ac2->getBalance();
    };
    sort(accounts.begin(), accounts.end(), comp);
}
