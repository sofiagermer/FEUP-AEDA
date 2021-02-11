#include "ThinTallBox.h"
#include "WideFlatBox.h"

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize()-next_object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if((getContentSize() + object.getSize()) <= getCapacity()){
        objects.push(object);
        setContentSize(getContentSize()+ object.getSize());
    }
    else{
        throw ObjectDoesNotFitException();
    }

}

void ThinTallBox::sortObjects() {
	stack<Object> tempstack;
	while(!objects.empty()){
	    Object aux = objects.top();
	    objects.pop();
	    while(!tempstack.empty() && tempstack.top().getSize() < aux.getSize() ){
	        objects.push(tempstack.top());
	        tempstack.pop();
	    }
	    tempstack.push(aux);
	}
	objects = tempstack;


}
