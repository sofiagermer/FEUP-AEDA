#include "animal.h"
#include <sstream>
using namespace std;

Animal::Animal(string name, int age){
    this -> name = name;
    this -> age = age;
    if(age < youngest){
       youngest =age;
    }
    this -> vet = 0;
}
Dog::Dog(string name, int age, string breed) : Animal(name,age)
{
    this -> breed = breed;
}

Flying::Flying(int maxv, int maxa) : maxVelocity(maxv), maxAltitude(maxa)
{
}


Bat::Bat(string name, int age, int maxv, int maxa): Animal(name,age), Flying(maxv,maxa)
{}
string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

int Animal:: youngest = 100000;
int Animal::getYoungest() {
    return youngest;
}

string Animal::getInfo() const {
    stringstream ss;
    ss << name << ", " << age;
    if (vet != NULL) ss << ", " << vet->getInfo();
    return ss.str();
}

bool Dog::isYoung() const {
    if(getAge() < 5){
        return true;
    }
    return false;
}

string Dog::getInfo() const {
    stringstream ss;
    ss << Animal::getInfo() << ", " <<breed;
    return ss.str();
}

bool Bat::isYoung() const{
    if(getAge() < 4){
        return true;
    }
    return false;
}
string Flying::getInfo() const {
    stringstream ss;
    ss << maxVelocity << ", " << maxAltitude;
    return ss.str();
}

string Bat::getInfo() const {
    stringstream ss;
    ss << Animal::getInfo() << ", " << Flying::getInfo();
    return ss.str();
}




