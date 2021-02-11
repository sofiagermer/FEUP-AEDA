#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>
using namespace std;

CarPark::CarPark(unsigned cap, unsigned nMaxCli): capacity(cap), numMaxClients(nMaxCli)
{
    freePlaces=cap;
}
ClientDoesNotExist::ClientDoesNotExist(string name)
{
    this->name=name; //para no objeto da classe do cliente que não existe dar o nome do cliente "inexistente" à variável name da classe :)
};

vector<InfoCard> CarPark::getClients() const
{
    return clients;
}

unsigned CarPark::getNumPlaces() const
{
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const
{
    return capacity-freePlaces;
}

unsigned CarPark::getNumMaxClients() const
{
    return numMaxClients;
}

unsigned CarPark::getNumClients() const
{
    return clients.size();
}

// TODO

int CarPark::clientPosition(const string & name) const
{
    vector<string> nomes;

    for(int i=0;i< clients.size();++i)
        nomes.push_back(clients.at(i).name);

    return(sequentialSearch(nomes,name));
}

// TODO
unsigned CarPark::getFrequency(const string &name) const
{
    int pos = clientPosition(name);
    if(pos == -1) throw ClientDoesNotExist(name);
    else return (clients.at(pos).frequency);
}

// TODO: to modify
bool CarPark::addClient(const string & name)
{
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name=name;
    info.present=false;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string & name)
{
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ( (*it).name == name ) {
            if ( (*it).present == false ) {
                clients.erase(it);
                return true;
            }
            else return false;
        }
    return false;
}

// TODO: to modify
bool CarPark::enter(const string & name)
{
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == true) return false;
    clients[pos].present = true;
    clients[pos].frequency++;
    freePlaces--;
    return true;
}

// TODO: to modify
bool CarPark::leave(const string & name)
{
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present == false) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}
unsigned PositionDoesNotExist::getPosition() {
    return position;
}

// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const
{
    if(p >= clients.size()) throw PositionDoesNotExist;
    return clients[p];
}

// TODO

void CarPark::sortClientsByFrequency()
{
    insertionSort(clients);
}

// TODO
bool compName(const InfoCard &c1, const InfoCard &c2)
{
    return c1.name < c2.name;
}

//criei aqui esta função auxiliar que não foi declarada dentro da função
void CarPark::sortClientsByName()
{
    return sort(clients.begin(), clients.end(), compName);
}

// TODO
vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2)
{
    sortClientsByFrequency();
    vector<string> names;
    for(int i = 0; i <= clients.size(); i++){
        if((clients[i].frequency < f2 || clients[i].frequency == f2) && (!(clients[i].frequency < f1) || clients[i].frequency == f1)){
            names.push_back(clients[i].name);
        }
    }

    return names;
}


// TODO
ostream & operator<<(ostream & os, const CarPark & cp)
{
    for(int i = 0; i <= cp.clients.size() ; i++){
        os << cp.clients[i].name << " " << cp.clients[i].present << " " << cp.clients[i].frequency << endl;
    }
    return os;
}

string ClientDoesNotExist::getName() const {
    return name;
}


bool InfoCard::operator < (const InfoCard &ic1) const
{
    if(frequency==ic1.frequency) //quando tem a mesma frequência -> critério de comparação : ordem alfabética
        return name<ic1.name;

    else
        return frequency > ic1.frequency;
}

bool InfoCard::operator==(const InfoCard &ic2) const {
    if(frequency== ic2.frequency)
        return true;
    return false;
}

