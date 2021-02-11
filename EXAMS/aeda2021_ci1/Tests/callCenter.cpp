#include <algorithm>
#include <iostream>
#include "callCenter.h"

using namespace std;
CallCenter::CallCenter()
{}

list<CallCenterAgent> CallCenter::getAgents() const {
    return agents;
}

void CallCenter::addAgent(const CallCenterAgent &cca) {
    agents.push_back(cca);
}

vector<stack<OrderCall *> >CallCenter::getOrders() const {
    return attendedOrderCalls;
}

void CallCenter::setOrders(vector<stack<OrderCall *> > stOrd1) {
    attendedOrderCalls = stOrd1;
}


//---------------------------------------------------------------------

queue<Call *> CallCenter::removeAgent(string name) {
    queue<Call *> res;
    list<CallCenterAgent> temp;
    bool not_found = true;
    while(!agents.empty()){
        if(agents.front().getName() == name){
            not_found = false;
            res = agents.front().getWaitingCalls();
        }
        else{
            temp.push_front(agents.front());
        }
        agents.pop_front();
    }
    agents = temp;
    if(not_found){
        throw NoAgentException();
    }
    return res;
}


void CallCenter::sortAgents() {
    auto comp = [] ( CallCenterAgent ag1, CallCenterAgent ag2){
        if(ag1.getWaitingCalls().size() != ag2.getWaitingCalls().size()){
            return ag1.getWaitingCalls().size() >  ag2.getWaitingCalls().size();
        }
        else if(ag1.getName() != ag2.getName()){
            return ag1.getName() < ag2.getName();
        }
        else{
            return ag1.getID() < ag2.getID();
        }

    };
    agents.sort(comp);
}


bool CallCenter::putInLessBusyAgent(Call * newCall) {
    if(agents.empty()){
        return false;
    }

    int mincall = 100000000;
    for(auto &x : agents){
        if(x.getWaitingCalls().size() < mincall){
            mincall = x.getWaitingCalls().size();
        }
    }
    for(auto &x : agents){
        if(x.getWaitingCalls().size() == mincall){
            x.addCall(newCall);
            break;
        }
    }
    return true;

}


void CallCenter::addAgent(string name, unsigned idAgent) {
    CallCenterAgent novo_ag (name, idAgent);
    for(auto &x : agents){
        if(x.getWaitingCalls().size() >= 2){
            novo_ag.addCall(x.getWaitingCalls().front());
            x.remove();
        }
    }
    agents.push_back(novo_ag);
}


void CallCenter::addOrder(OrderCall *call1) {
    bool found = false;
    for(auto & x: attendedOrderCalls) {
        if(x.top()->getZipCode() == call1->getZipCode()){
            x.push(call1);
            found = true;
        }
    }
    if(!found){
        stack <OrderCall*> newstack;
        newstack.push(call1);
        attendedOrderCalls.push_back(newstack);
    }
}


unsigned CallCenter::processOrderZip(string zip1, unsigned n)
{
    int counter = 0;
    int it_pos = 0;
    for(auto & x: attendedOrderCalls) {
        string sofi = "";
        if(!x.empty()){
            sofi = x.top()->getZipCode();
        }
        if (sofi == zip1) {
            int aux = x.size();
            while (aux > 0 && counter < n) {
                x.pop();
                counter++;
                aux--;
            }
            if (x.empty()) {
                attendedOrderCalls.erase(attendedOrderCalls.begin() + it_pos);
            }
        }
        it_pos++;
        if (counter == n) {
            return n;
        }
    }
        return counter;
}





