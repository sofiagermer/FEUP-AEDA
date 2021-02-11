#include "fleet.h"
#include <string>
#include<bits/stdc++.h>
using namespace std;

vector<Vehicle *> Fleet::getVehicles() const {
    return vehicles;
}

// adiciona um veículo v1(automóvel, camião ou bicicleta) ao vetor vehicles
void Fleet::addVehicle(Vehicle*v1){
    vehicles.push_back(v1);
}
// retorna o nº de veículos no vector veiculo
int Fleet::numVehicles() const{
    if(vehicles.empty()){
        return 0;
    }
    return vehicles.size();
}
// retorna o menor ano dos veículos presentes no vetor veículos; retorna 0 se não existir nenhum veículo
int Fleet::lowestYear() const{
    int size = numVehicles();
    if(size == 0){
        return 0;
    }
    int aux = INT_MAX;
    for(auto c : vehicles){
        if (c-> getYear() < aux){
            aux = c-> getYear();
        }
    }
    return aux;
}
//retorna um vetor de apontadores para os veículos cujo ano de matrícula é igual a anoM
vector<Vehicle *> Fleet:: operator () (int yearM) const{
    vector <Vehicle*> v1;
    if(vehicles.size() == 0) { return v1;}
    for(auto it: vehicles){
        if(it -> getYear() == yearM){
            v1.push_back(it);
        }
    }
    return v1;
}

float Fleet::totalTax() const {
    float aux = 0;
    for(auto c : vehicles){
        aux += c -> calculateTax();
    }
    return aux;
}

unsigned Fleet::removeOldVehicles(int y1) {
    //Estafunção remove do vetor vehiclesos veículoscujo ano de fabrico é menor ou igual a y1.Retorna o numero de veículos removidos.
    /*int aux = 0;
    for(int i = 0 ; i < vehicles.size(); i++){
        if(vehicles.at(i)->getYear() <= y1){
            vehicles.erase(vehicles.begin() + i);
            i--;
            aux++;
        }
    }
    return aux;*/


    int aux=0;
    vector<Vehicle *>::const_iterator it = vehicles.begin();
    while(it != vehicles.end()) {
        if ((*it)->getYear()<= y1) {
            vehicles.erase(it);
            it--;
            aux++;
        }
        it++;
    }
    return aux;
}