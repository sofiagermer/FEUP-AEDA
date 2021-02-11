#include "vehicle.h"
#include <iostream>

using namespace std;

Vehicle::Vehicle(string b, int m, int y) : brand(b), month(m), year(y)
{}

MotorVehicle::MotorVehicle(string b, int m, int y, string f, int cyl) : Vehicle(b, m, y), fuel(f), cylinder(cyl)
{}

Car::Car(string b, int m, int y, string f, int cyl) : MotorVehicle(b, m, y,f,cyl)
{}

Truck::Truck(string b, int m, int y, string f, int cyl, int ml) : MotorVehicle(b,m,y,f,cyl)
{}

Bicycle::Bicycle(string b, int m, int y, string t) :Vehicle(b,m,y), type(t)
{}

string MotorVehicle::getFuel() const {
    return fuel;
}

string Vehicle::getBrand() const {
    return brand;
}

int Vehicle::getYear() const {
    return year;
}
//Um veículo é menor que outro se é mais antigo (verificar ano e mês de fabrico).
bool Vehicle::operator<(const Vehicle &v) const {
    if(year < v.year){
        return true;
    }
    if(year == v.year){
        if(month > v.month){
            return false;
        }
        return true;
    }
    return false;
}

int Vehicle::info() const {
    cout << brand << "," << month << "," << year;
    return 3;
}

float Vehicle::calculateTax() const {}
int MotorVehicle::info() const {
    cout << brand << "," << month << "," << year << fuel <<"," << cylinder;
    return 5;
}
int MotorVehicle::info(ostream&o) const {
    o << brand << "," << month << "," << year << fuel <<"," << cylinder;
    return 5;
}
float MotorVehicle::calculateTax() const {
    if(fuel == "gas"){
        if(cylinder <= 1000 && year > 1995){
            return 14.56;
        }
        if(cylinder > 1000 && cylinder <=1300 && year > 1995){
            return 29.06;
        }
        if(cylinder > 1300 && cylinder <=1750 && year > 1995){
            return 45.15;
        }
        if(cylinder > 1750 && cylinder <=2600 && year > 1995){
            return 113.98;
        }
        if(cylinder > 2600 && cylinder <=3500 && year > 1995){
            return 181.17;
        }
        if(cylinder > 3500 && year > 1995){
            return 320.89;
        }
        if(cylinder <= 1000 && year <= 1995){
            return 8.10;
        }
        if(cylinder > 1000 && cylinder <=1300 && year <= 1995){
            return 14.56;
        }
        if(cylinder > 1300 && cylinder <=1750 && year <= 1995){
            return 22.65;
        }
        if(cylinder > 1750 && cylinder <=2600 && year <= 1995){
            return 54.89;
        }
        if(cylinder > 2600 && cylinder <=3500 && year <= 1995){
            return 87.13;
        }
        if(cylinder > 3500 && year <= 1995){
            return 148.37;
        }
    }
    if(fuel != "gas"){
        if(cylinder <= 1500 && year > 1995){
            return 14.56;
        }
        if(cylinder > 1500 && cylinder <=2000 && year > 1995){
            return 29.06;
        }
        if(cylinder > 2000 && cylinder <=3000 && year > 1995){
            return 45.15;
        }
        if(cylinder > 3000 && year > 1995){
            return 113.98;
        }
        if(cylinder <= 1500 && year <= 1995){
            return 8.10;
        }
        if(cylinder > 1500 && cylinder <=2000 && year <= 1995){
            return 14.56;
        }
        if(cylinder > 2000 && cylinder <=3000 && year <= 1995){
            return 22.65;
        }
        if(cylinder > 3000 && year <= 1995){
            return 54.89;
        }
    }
}
int Car::info() const {
    return MotorVehicle::info();
}
int Car::info(ostream&o) const {
    return MotorVehicle::info(o);
}

float Car::calculateTax() const {
    return MotorVehicle::calculateTax();
}
int Truck::info() const {
    int aux = MotorVehicle::info();
    cout << maximumLoad;
    aux++;
    return aux;
}
int Truck::info(ostream&o) const {
    int aux = MotorVehicle::info(o);
    o << maximumLoad;
    aux++;
   return aux;
}
float Truck::calculateTax() const {
    return MotorVehicle::calculateTax();
}
int Bicycle::info() const {
    cout << brand << "," << month <<"," << year << "," << type;
    return 4;
}
int Bicycle::info(ostream &o) const {
    o << brand << "," << month <<"," << year << "," << type;
    return 4;
}
float Bicycle::calculateTax() const {
    return 0;
}