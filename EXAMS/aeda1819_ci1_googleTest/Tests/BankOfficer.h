/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>

class BankOfficer {

    unsigned int id;
	string name;
	vector<Account *> myAccounts;
    static unsigned int ID;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
	bool operator>(BankOfficer &ba);

    //-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);

};


template <class T>
unsigned int numberDifferent(const vector<T> & v1){
    vector <T> aux;
    for(const auto x: v1){
        bool found = false;
        if(aux.size() == 0){
            aux.push_back(x);
        }
        for(const auto y: aux){
            if(y == x){
                found = true;
            }
        }
        if(!found){
            aux.push_back(x);
        }
    }
    return aux.size();
}
#endif /* SRC_BANKOFFICER_H_ */
