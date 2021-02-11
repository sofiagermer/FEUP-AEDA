#include "packagingMachine.h"
#include <sstream>
#include <algorithm>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {

    unsigned removed = 0;
    //pirority queues são desenhadas para o maior objeto ficar no topo por isso no overload defenimos como ver qual é o maior objeto
    for(auto it = objs.begin(); it != objs.end();){
        if(it->getWeight() <= boxCapacity){
            objects.push(*it);
            objs.erase(it);
            removed++;
        }
        else{
            it++;
        }
    }
    return removed;
}

// TODO

Box PackagingMachine::searchBox(Object& obj){
    HeapBox temp;
    Box sofi (10) ;
    bool found = false;
    while(!boxes.empty()){
        if(!found) {
            if (boxes.top().getFree() >= obj.getWeight()) {
                sofi = boxes.top();
                boxes.pop();
                found = true;
            }
            else{
                temp.push(boxes.top());
                boxes.pop();
            }
        }
        else{
            temp.push(boxes.top());
            boxes.pop();
        }
    }
    boxes = temp;
    return sofi;
}


// TODO
unsigned PackagingMachine::packObjects() {
	while(!objects.empty()){
	    Object c = objects.top();
        objects.pop();
        Box b =searchBox(c);
        b.addObject(c);
        boxes.push(b);
	}
	return boxes.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
	stringstream sofi;
	HeapObj temp = objects;
	if(temp.empty()){
	    sofi << "No objects!\n";
	}
	while(!temp.empty()){
	    sofi << temp.top() << endl;
	    temp.pop();
	}
	return sofi.str();
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
    HeapBox temp = boxes;
    if(temp.empty()){
        throw MachineWithoutBoxes();
    }
    Box maximo = boxes.top();
    while(!temp.empty()){
        if(temp.top().getSize() > maximo.getSize()){
            maximo = temp.top();
        }
        temp.pop();
    }
    return maximo;
}