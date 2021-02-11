#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    vector<Animal *> :: const_iterator it;
    for(it = animals.begin(); it != animals.end(); it++){
        (*it)->getInfo();
    }
}

bool Zoo::isYoung(string nameA) {
    vector<Animal *> :: iterator it;
    for(it = animals.begin(); it != animals.end(); it++){
        if((*it) -> getName() == nameA){
            if((*it)->isYoung()){
                return true;
            }
            return false;
        }
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name, cod;

    while(!isV.eof()) {
        getline(isV,name);
        getline(isV,cod);
        Veterinary *v1=new Veterinary(name, stoi(cod));
        veterinarians.push_back(v1);
    }
    vector<Animal *> ::iterator it;
    int i = 0;
    for(it = animals.begin(); it != animals.end(); it++){
        (*it) -> setVeterinary(*veterinarians.begin() + i);
        i++;
        if(i == veterinarians.size()){
            i = 0;
        }
    }
}
/*
bool Zoo::removeVeterinary(string nameV) {
    vector<Veterinary *> :: iterator it;
    vector< Animal*> :: iterator it2;
    for(it = veterinarians.begin(); it != veterinarians.end(); it++){
        if(nameV == (*it)->getName()){
            for(it2= animals.begin(); it2!= animals.end(); it2++){
                if((*it2) -> getVeterinary() ->getName() == nameV){
                    if(it == veterinarians.end()--){
                        (*it2)->setVeterinary(*(veterinarians.begin()));
                    }
                    (*it2)->setVeterinary(*(it++));
                }
            }
            return true;
        }
    }
    return false;
}
*/

bool Zoo::removeVeterinary(string nameV) {
    for(unsigned int i = 0; i < veterinarians.size(); i++) {
        if( veterinarians[i]->getName() == nameV ) {
            //look for animals treated by Veterinary with name nameV
            for(unsigned int j = 0; j < animals.size(); j++) {
                if( animals[j]->getVeterinary() == veterinarians[i] )
                    //replaces with the next veterinary in the vector
                    animals[j]->setVeterinary( veterinarians[(i + 1)%veterinarians.size()] );
            }
            veterinarians.erase( veterinarians.begin() + i );

            return true;
        }
    }
    return false;
}