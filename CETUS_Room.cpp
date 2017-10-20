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

void Room::addNeighbor(int direction, Room* neighbor){
	
	this->neighbors->addAdjacent(direction, neighbor);
	return;
	
}

void Room::printLong(){

		cout<<this->longDesc;
		return;
	
}

void Room::printShort(){

	cout<<this->shortDesc;
	return;
	
}

void Room::createNeighbors(List* neighborList){
	
	this->neighbors = neighborList;
	
}

List* Room::getNeighbors(){
	
	return this->neighbors;
	
}

