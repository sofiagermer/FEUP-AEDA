#ifndef SRC_HOTEL_H_
#define SRC_HOTEL_H_

#include <vector>
#include <list>
using namespace std;

template <class Chamber>
class Hotel {
	vector<Chamber *> chambers;
	const unsigned int maxCapacity;
	const std::string city;
    list<Chamber> reservationsDone;
public:
	Hotel(int size, std::string municipality);
	~Hotel();
	std::vector<Chamber *> getChambers() const;
	void setChambers(std::vector<Chamber *> chambers);
	int getCapacity() const;
    std::list<Chamber> getReservationsDone() const;
	bool addChamber(Chamber *chamber);
    void addReservationDone(Chamber chamber);
    Chamber* removeChamber(string code, int floor);
	float avgArea(int floor) const;
	void sortChambers();
	bool doReservation(std::string code, int floor);
    list<Chamber> roomsNeverReserved() const;
};

class NoSuchChamberException {
public:
	NoSuchChamberException() { }
};


class NoSuchFloorException {
private:
    int floor;
public:
    NoSuchFloorException(int floor) : floor(floor){};
    int getFloor() const {return floor;}
};


template <class Chamber>
Hotel<Chamber>::Hotel(int size, std::string municipality) : maxCapacity(size), city(municipality) {
}

template <class Chamber>
Hotel<Chamber>::~Hotel(){
	typename std::vector<Chamber *>::const_iterator it;
	for (it=chambers.begin(); it!=chambers.end(); it++) {
		delete *it;
	}
}

template<class Chamber>
std::vector<Chamber *> Hotel<Chamber>::getChambers() const {
	return chambers;
}

template<class Chamber>
void Hotel<Chamber>::setChambers(std::vector<Chamber*> chambers) {
	this->chambers = chambers;
}

template<class Chamber>
int Hotel<Chamber>::getCapacity() const {
	return maxCapacity;
}

template<class Chamber>
void Hotel<Chamber>::addReservationDone(Chamber chamber) {
    reservationsDone.push_back(chamber);
}

template<class Chamber>
std::list<Chamber> Hotel<Chamber>::getReservationsDone() const {
    return reservationsDone;
}

//------------------------------------------------------
//------------------------------------------------------

//TODO
template<class Chamber>
bool Hotel<Chamber>::addChamber(Chamber *chamber) {
    if (chambers.size() == maxCapacity) {
        return false;
    }
    for(auto &c : chambers){
        if(c->getCode() == chamber->getCode()){
            return false;
        }
    }
    chambers.push_back(chamber);
    return true;
}

template<class Chamber>
void Hotel<Chamber>::sortChambers() {
    typename vector<Room *>::const_iterator it;
    auto comp = [](const Room* c1, const Room* c2){
        return (c1->getCode() < c2->getCode()) || c1->getFloor() > c2->getFloor();
    };
    sort(chambers.begin(),chambers.end(),comp);
}


//TODO
template<class Chamber>
Chamber* Hotel<Chamber>::removeChamber(string code, int floor) {
    /*for (auto &c: chambers){
        if(c -> getCode()== code && c-> getFloor() == floor){
            chambers.erase(c);
            return c;
        }
    }
    NoSuchChamberException();*/
    /*Chamber *chams;
    for(int i= 0; i <= chambers.size(); i++){
        if(chambers.at(i) -> getCode() == code && chambers.at(i) -> getFloor() == floor){
            chams = chambers.at(i);
            chambers.erase(remove(chambers.begin(),chambers.end(),chams),chambers.end());
            return chams;
        }
    }
    throw NoSuchChamberException();*/
    for(const auto elem: chambers){
        if(elem->getCode() == code && elem->getFloor() == floor){
            chambers.erase(remove(chambers.begin(),chambers.end(),elem),chambers.end());
            return elem;
        }
    }
    throw NoSuchChamberException();
}

//TODO
template<class Chamber>
float Hotel<Chamber>::avgArea(int floor) const {
    float sum= 0;
    float nr = 0;
    bool found = false;
    for(const auto c : chambers)
        if(c->getFloor() == floor){
            sum += c->getArea();
            nr ++;
            found = true;
        }
    if(!found){
        throw NoSuchFloorException(floor);
    }
    return sum /nr;
}

//TODO
template<class Chamber>
bool Hotel<Chamber>::doReservation(string code, int floor){
    for(const auto c: chambers){
        if(c->getCode() == code && c->getFloor() == floor){
            for(const auto &aux : reservationsDone){
                if(aux.getCode() == code && aux.getFloor() == floor){
                    return false;
                }
            }
            Room romie(code, floor) ;
            romie.setReservation(true);
            reservationsDone.push_back(romie);
            return true;
        }
    }
    return false;
}

//TODO
template<class Chamber>
list<Chamber> Hotel<Chamber>::roomsNeverReserved() const {
    list<Chamber> res;
    for(const auto c: chambers){
        bool found = false;
        for(const auto &aux: reservationsDone){
            if(c->getCode() == aux.getCode() && c->getFloor() == aux.getFloor()){
                found = true;
            }
        }
        if(!found){
            Room romie(c->getCode(), c->getFloor());
            res.push_back(romie);
        }
    }

    return res;
}



#endif /* SRC_HOTEL_H_ */
