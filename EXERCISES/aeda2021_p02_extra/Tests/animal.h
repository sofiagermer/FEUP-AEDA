#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinary.h"
#include <string>
using namespace std;

class Animal {
protected:
    string name;
    int age;
    Veterinary *vet;
    static int youngest;
public:
    Animal(string name, int age);
    virtual ~Animal(){};
    string getName() const;
    int getAge() const;
    Veterinary *getVeterinary() const;
    void setVeterinary(Veterinary *vet);
    static int getYoungest();
    virtual string getInfo() const;  // info concerning name, age, name of the veterinary (if any)
    virtual bool isYoung() const = 0;
};


class Dog: public Animal {
    string breed;
public:
    bool isYoung() const;
    Dog(string name, int age, string breed);
    string getInfo() const;
// to complete
};


class Flying {
    int maxVelocity;
    int maxAltitude;
public:
   Flying(int maxv, int maxa);
   string getInfo() const;
//to complete
};


class Bat: public Animal, public Flying {
public:
    bool isYoung() const;
    Bat(string name, int age, int maxv, int maxa);
    string getInfo() const;
// to complete
};

#endif /* SRC_ANIMAL_H_ */
