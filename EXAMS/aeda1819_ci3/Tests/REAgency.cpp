#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//

void REAgency::generateCatalog() {
    for(auto &elem:properties) {
        string address = elem->getAddress();
        string postalCode = elem->getPostalCode();
        string typology = elem->getTypology();
        int maxPrice = elem->getPrice();
        PropertyTypeItem nova = PropertyTypeItem(address,postalCode,typology,maxPrice);
        PropertyTypeItem sofi = catalogItems.find(PropertyTypeItem(address,  postalCode, typology, maxPrice));
        if(nova == sofi){
            if(maxPrice > sofi.getMaxPrice()){
                nova.setItems(sofi.getItems());
                nova.addItems(elem);
                catalogItems.remove(sofi);
                catalogItems.insert(nova);
            }
            else{
                sofi.addItems(elem);
                catalogItems.remove(nova);
                catalogItems.insert(sofi);
            }
        }
        else{
            nova.addItems(elem);
            catalogItems.insert(nova);
        }
    }
}
vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	PropertyTypeItem sofi = catalogItems.find(PropertyTypeItem(property->getAddress(), property->getPostalCode(), property->getTypology(),property->getPrice()));
	vector<Property*> temp;
	for(auto x: sofi.getItems()){
	    if(get <0> (x->getReservation()) == NULL) {
            temp.push_back(x);
	    }
	}
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage){
    string address = property->getAddress();
    string postalCode = property->getPostalCode();
    string typology = property->getTypology();
    PropertyTypeItem wanted(address,postalCode,typology,0);
    PropertyTypeItem founded = catalogItems.find(wanted);
    vector<Property*> copy = founded.getItems();
    bool done_reservation = false;
    if(wanted == founded){
        for(auto &property: copy){
            if(get<0> (property->getReservation()) == NULL){
                client->addVisiting(address, postalCode, typology,to_string(property->getPrice()));
                property->setReservation(make_tuple(client,property->getPrice() - property->getPrice() * (percentage * 0.01)));
                done_reservation = true;
                break;
            }
        }
        if(done_reservation){
            /*int new_max_price = 0;
            for(auto x: copy){
                if(x->getPrice() > new_max_price){
                    new_max_price = x->getPrice();
                }
            }*/
            PropertyTypeItem nova(address,postalCode,typology,founded.getMaxPrice());
            nova.setItems(copy);
            catalogItems.remove(founded);
            catalogItems.insert(nova);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    listingRecords.insert(client);
}

void REAgency::deleteClients() {
    auto it = listingRecords.begin();
    while(it != listingRecords.end()){
        if(it->getClientPointer()->getVisitedProperties().empty()){
            listingRecords.erase(it);
            break;
        }
        else{
            it++;
        }
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
    for(auto &x : candidates){
        double counter_person_x = 0;
        for(auto y: properties) {
            if ((get<0>(y->getReservation()))->getName() == x.getName()) {
                counter_person_x++;
            }
        }
        if((counter_person_x / x.getVisitedProperties().size()) > min){
            clientProfiles.push(x);
        }
    }
    priority_queue<Client> temp = clientProfiles;
    cout << "clientes " << endl;
    while(!temp.empty()){
        cout << get<3> (temp.top().getVisiting()) << endl;
        temp.pop();
    }
}

vector<Property*> REAgency::suggestProperties() {
	//TODO: G
	vector<Property*> tempProperties;
    priority_queue<Client> temp = clientProfiles;
    vector<Property*> no_reserved;
    for(auto y: properties) {
        if ((get<0>(y->getReservation())) == NULL){
            no_reserved.push_back(y);
        }
    }
    if(no_reserved.empty()){
        return tempProperties;
    }
    while(!temp.empty()){
        Client client  = temp.top();
        if(get<0> (client.getVisiting()) != ""){
            tuple<string, string, string, string> last_one = client.getVisiting();
            int min = 100000000000;
            for(auto &x : no_reserved){
               if((stoi(x->getPostalCode()) - stoi(get<1>(last_one))) < min){
                   min = stoi(x->getPostalCode());
               }
            }
            for(auto &x : no_reserved){
                if(min == stoi(x->getPostalCode())){
                    tempProperties.push_back(x);
                }
            }
        }
        temp.pop();
    }
	return tempProperties;
}
