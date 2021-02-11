#include "callCenterAgent.h"
#include <string>

using namespace std;

CallCenterAgent::CallCenterAgent(string nm, unsigned id): nameAgent(nm),idAgent(id)
{}

string CallCenterAgent::getName() const{
    return nameAgent;
}

unsigned  CallCenterAgent::getID() const {
    return idAgent;
}

queue<Call *> CallCenterAgent::getWaitingCalls() const {
    return myWaitingCalls;
}

void CallCenterAgent::addCall(Call *c) {
    myWaitingCalls.push(c);
}

void CallCenterAgent::remove() {
    myWaitingCalls.pop();
}

//---------------------------------------------------------------------

void CallCenterAgent::moveToFront(string codCall1) {
    queue<Call *> res;
    queue<Call *> final;
    bool found = false;
    while(!myWaitingCalls.empty()){
        if(myWaitingCalls.front()->getCodeCall() == codCall1){
            final.push(myWaitingCalls.front());
            found = true;
        }
        res.push(myWaitingCalls.front());
        myWaitingCalls.pop();
    }
    myWaitingCalls = res;
    if (found){
        while(!myWaitingCalls.empty()){
            if(myWaitingCalls.front()->getCodeCall() != codCall1){
                final.push(myWaitingCalls.front());
            }
            myWaitingCalls.pop();
        }
        myWaitingCalls = final;
    }
}

