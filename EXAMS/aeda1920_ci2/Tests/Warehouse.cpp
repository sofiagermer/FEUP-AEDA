#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(const Object& o1) {
    objects.push(o1);
}


int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    auto comp = [] (const Object& ob1, const Object& ob2){
        return (ob1.getSize() > ob2.getSize());
    };
    sort(obj.begin(), obj.end(), comp);
    for(const auto &x : obj){
        objects.push(x);
    }
    return obj.size();
}

Object Warehouse::RemoveObjectQueue(int maxSize){
    queue<Object> newQueue;
    Object current;
    size_t sizeOfQueue = objects.size();
    while (!objects.empty()){
        current = objects.front();
        objects.pop();
        if(current.getSize() <= maxSize)
            break;
        newQueue.push(current);
    }
    while (!objects.empty()){
        newQueue.push(objects.front());
        objects.pop();
    }
    objects = newQueue;
    if(newQueue.size() == sizeOfQueue)
        return Object("dummy", maxSize);
    else return current;

}

int Warehouse::addPackOfBoxes(const vector <ThinTallBox>& boV) {
    for(const auto &x : boV) {
        boxes.push(x);
    }
    return boxes.size();
}

vector<ThinTallBox>Warehouse::DailyProcessBoxes(){
    vector<ThinTallBox> sofi;
    vector<ThinTallBox> final;

    while(!boxes.empty()){
        sofi.push_back(boxes.front());
        boxes.pop();
    }
    vector <Object> obj;
    while(!objects.empty()){
        obj.push_back(objects.front());
        objects.pop();
    }
    for(auto o : obj){
        objects.push(o);
    }

    for(auto &x: sofi){
        bool found = false;
        if(x.getContentSize() == x.getCapacity()){
            final.push_back(x);
        }
        else if(x.getDays() == 0){
            int index = 0;
            for(auto &o : obj){
                if(o.getSize() + x.getContentSize() <= x.getCapacity()){
                    x.insert(o);
                    found = true;
                    index++;
                    break;
                }
            }
            if(!found){
                x.insert(Object("dummy", 0));
            }
            if(found){
                obj.erase(obj.begin()+index);
            }
            final.push_back(x);
        }
        else{
            int index = 0;
            for(auto &o : obj){
                if(o.getSize() + x.getContentSize() <= x.getCapacity()){
                    x.insert(o);
                    found = true;
                    index++;
                    break;
                }
            }
            if(!found){
                x.insert(Object("dummy", 0));
            }
            if(found){
                obj.erase(obj.begin()+index);
            }
            x.setDaysToSend(x.getDays()-1);
            boxes.push(x);
        }
    }
    return sofi;
}

