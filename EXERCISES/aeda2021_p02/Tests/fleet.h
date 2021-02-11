#ifndef FLEET_H_
#define FLEET_H_
#include <iostream> 

#include <vector>
#include "vehicle.h"
using namespace std;

class Fleet {
	vector<Vehicle *> vehicles;
public:
    vector<Vehicle *> getVehicles() const;
	//friend ostream & operator<<(ostream & o, const Fleet & f);
    void addVehicle(Vehicle*v1);
    int numVehicles() const;
    int lowestYear() const;
    vector<Vehicle *> operator () (int yearM) const;
    float totalTax()const;
    unsigned removeOldVehicles(int y1);
};


#endif /*FLEET_H_*/
