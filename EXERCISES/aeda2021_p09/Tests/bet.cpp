#include "bet.h"
#include <iostream>
#include <sstream>
using namespace std;


//TODO
bool Bet::contains(unsigned num) const
{
	if(numbers.find(num) != numbers.end()){
	    return true;
	}
	return false;
}

//TODO
/*
void Bet::generateBet(const vector<unsigned>& values, unsigned n)
{
    vector <unsigned> temp;
    bool found = false;
    for(auto x: values){
        for(auto y: temp){
            if(x == y){
                found = true;
                break;
            }
        }
        if(!found){
            temp.push_back(x);
        }
        found = false;
    }
    for(int i = 0; i < n; i++){
        numbers.insert(temp.at(i));
    }
}
*/
void Bet::generateBet(const vector<unsigned>& values, unsigned n){
    for(const auto& elem:values){
        if(numbers.size() < n) numbers.insert(elem);
        else return;
    }
}
//TODO
unsigned Bet::countRights(const tabHInt& draw) const
{
    unsigned counter = 0;
	for(auto &x : draw){
	    if(numbers.find(x) != numbers.end()){
	        counter++;
	    }
	}
	return counter;
}
