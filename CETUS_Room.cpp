#include "CETUS_Room.hpp"
#include <iostream>

using std::endl;
using std::cout;
using std::string;


Room::Room(){

	this->visited = false;
	this->neighbors = NULL;
	return;
	
}

string Room::getName(){
	return this->Name;
}

void Room::addDescriptions(string longDesc, string shortDesc){
	
	this->longDesc = longDesc;
	this->shortDesc = shortDesc;
	return;	
	
}

void Room::addItem(Item* current){
	
	this->roomItems.push_back(current);
	
	return;
	
}

void Room::removeItem(Item* current){
	
	return;
	
}

/*void Room::addNeighbor(int direction, Room* neighbor){
	
	this->neighbors->addAdjacent(direction, neighbor);
	return;
	
}*/ //Returning error for using an incomplete type here, may need to move this functionality to the overall world. 

void Room::getLong(){

		cout << this->longDesc;
		return;
	
}

void Room::getShort(){

	cout << this->shortDesc;
	return;
	
}

void Room::createNeighbors(List* neighborList){
	
	this->neighbors = neighborList;
	return;
}

List* Room::getNeighbors(){
	
	return this->neighbors;
	
}

void Room::setName(string newName){
	
	this->Name = newName;
	return;
}

void Room::setVisited(bool visit){
	
	
	this->visited = visit;
	
}

Item* Room::findItem(string current){
	
	for (int i = 0; i < this->roomItems.size(); i++){
	
		if (this->roomItems[i]->getName().compare(0, roomItems[i]->getName().size()-1, current) == 0){
			
			return this->roomItems[i];
		}
	
	}

	return NULL;
		
}

int Room::getVisited(){
    return this->visited;
}
