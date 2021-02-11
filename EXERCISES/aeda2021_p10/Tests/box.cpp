#include "box.h"
#include <sstream>

Object::Object(unsigned i, unsigned w): id(i), weight(w)
{}

unsigned Object::getID() const {
    return id;
}

unsigned Object::getWeight() const {
    return weight;
}

Box::Box(unsigned cap): id(lastId++), capacity(cap), free(cap)
{}

unsigned Box::getID() const {
    return id;
}

unsigned Box::getFree() const {
    return free;
}

void Box::addObject(Object& obj) {
    free -= obj.getWeight();
    objects.push(obj);
}

void Box::resetID(){
    lastId = 1;
}

unsigned Box::getSize() const {
    return objects.size();
}


ostream& operator<<(ostream& os, Object obj) {
    os << "O" << obj.id << ":" << obj.weight;
    return os;
}

unsigned Box::lastId = 1;


// TODO
bool Object::operator<(const Object& o1) const {
	return weight < o1.getWeight();
}

// TODO
bool Box::operator<(const Box& b1) const {
	return free > b1.getFree();
}

// TODO
string Box::printContent() const {
    stringstream sofi;
    if(objects.empty()){
        sofi << "Box " << id <<" empty!\n";
    }
    else{
        sofi << "Box " << id << " [ ";
        StackObj temp = objects;
        while(!temp.empty()){
            sofi << temp.top() << " ";
            temp.pop();
        }
        sofi << "]";
    }
	return sofi.str();
}