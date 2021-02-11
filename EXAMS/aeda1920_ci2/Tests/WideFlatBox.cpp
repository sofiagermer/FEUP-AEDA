#include <algorithm>
#include "WideFlatBox.h"

WideFlatBox::WideFlatBox(double capacity) : Box(capacity) {
}

void WideFlatBox::insert(Object object) {
	if(getContentSize()+object.getSize() <= getCapacity()) {
		objects.push_back(object);
		setContentSize(getContentSize()+object.getSize());
	} else {
		throw ObjectDoesNotFitException();
	}
}

const Object& WideFlatBox::next() const {
	return objects[0];
}

void WideFlatBox::sortObjects() {
	sort(objects.begin(), objects.end());
}


void WideFlatBox::remove(Object object) {
    bool not_found = true;
    int count = 0;
    for(const auto &x: objects){
        if(x == object){
            int size = x.getSize();
            objects.erase(objects.begin()+count);
            setContentSize(getContentSize()- size);
            not_found = false;
        }
        count++;
    }
    if(not_found){
        throw InaccessibleObjectException(object);
    }
}
