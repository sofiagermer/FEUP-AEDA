#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"
using namespace std;

//TODO
Client::Client() {
    numGifts = rand()%5+1;
}

//TODO
unsigned Client::getNumGifts() const {
    return numGifts;
}


//TODO
Counter::Counter(unsigned wt): wrappingTime(wt) {
    actualTime = 0;
    nextEnter = rand()%20+1;
    nextLeave = 0;
    numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return nextLeave;
}

//TODO
Client & Counter::getNextClient() {
    if (clients.empty()) {
        throw EmptyQueue();
    }
    return clients.front();
}

//TODO
void Counter::enter()
{
    cout << "time= " << actualTime<< endl;
    Client cl1;
    if (clients.empty())
        nextLeave = actualTime + cl1.getNumGifts()*wrappingTime;
    clients.push(cl1);
    cout << "entering a new client with " << cl1.getNumGifts() << " gifts" << endl;
    nextEnter = actualTime + (rand()%20)+1;

}

//TODO
void Counter::leave()
{
    try{
        getNextClient();
    } catch (const EmptyQueue& e) {
        cout << "Tried to leave the queue, but the queue is empty.";
    }
    cout << "time = " << actualTime << "\n" << "the costumer who left had " << clients.front().getNumGifts() << " gifts" << endl;
    clients.pop();
    if(!clients.empty())
        nextLeave = actualTime + clients.front().getNumGifts()*wrappingTime;
    numAttendedClients++;
}

//TODO
void Counter:: nextEvent()
{
        if (nextEnter <= nextLeave || clients.empty()) {
            actualTime = nextEnter;
            enter();
        }else if (nextEnter >= nextLeave && !clients.empty()) {
            actualTime = nextLeave;
            leave();
        }
}


//TODO
ostream & operator << (ostream & out, const Counter & c2)
{
     out << c2.numAttendedClients << " " << c2.clients.size();
     return out;
}


