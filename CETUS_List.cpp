#include "CETUS_List.hpp"
#include <iostream>

/* 
NORTH 0
SOUTH 1
EAST 2sd
WEST 3
*/

using std::endl;
using std::cout;
using std::string;

List::List(){
	
	this->north = NULL;
	this->south = NULL;
	this->east = NULL;
	this->west = NULL;

}

List::~List(){

		if (this->north != NULL){ delete this->north;}
		
		if (this->south != NULL){ delete this->south;}
		
		if (this->east != NULL){ delete this->east;}
		
		if (this->west != NULL){ delete this->west;}
	
}

void List::addAdjacent(int direction, Room* current){
	
	switch(direction){
		
		case 0:
			this->north = current;
			break;
		
		case 1:
			this->south = current;
			break;
			
		case 2:
			this->east = current;
			break;
			
		case 3:
			this->west = current;
			break;
			
		default:
			break;		
		
	}
	
	return;
	
}

Room* List::printAdjacent(int direction){
	
	switch(direction){
		
	case 0:
		return this->north;
		break;
		
	case 1:
		return this->south;
		break;
			
	case 2:
		return this->east;
		break;
			
	case 3:
		return this->west;
		break;
			
	default:
		break;		
	
	}
	
	return NULL;	
	
}
//to be used when dimension changes, quick way to alter the adjacency list for each room
void List::switchAdjacent(int first, int second){
	
	Room* temp;
	
	switch(first){
		
	case 0:
	
		temp = this->north;
		switch(second){
			
			case 1:
				this->north = this->south;
				this->south = temp;
				break;
					
			case 2:
				this->north = this->east;
				this->east = temp;
				break;
					
			case 3:
				this->north = this->west;
				this->west = temp;
				break;
					
			default:
				break;					
			}
		break;
		
	case 1:
		temp = this->south;
			
		switch(second){
			
			case 0:
				this->south = this->north;
				this->north = temp;
				break;
					
			case 2:
				this->south = this->east;
				this->east = temp;
				break;
					
			case 3:
				this->south	= this->west;
				this->west = temp;
				break;
					
			default:
				break;					
		}
		break;
			
	case 2:
		temp = this->east;
		
		switch(second){
			
			case 0:
				this->east = this->north;
				this->north = temp;
				break;
					
			case 1:
				this->east = this->south;
				this->south	= temp;
				break;
					
			case 3:
				this->east	= this->west;
				this->west = temp;
				break;
					
			default:
				break;					
		}
		
		break;
			
	case 3:
		temp = this->west;
		
		switch(second){
			
			case 0:
				this->west = this->north;
				this->north = temp;
				break;
					
			case 1:
				this->west = this->south;
				this->south	= temp;
				break;
					
			case 2:
				this->west	= this->east;
				this->east = temp;
				break;
					
			default:
				break;					
		}		
		break;
			
	default:
		break;		
	
	}
	
	return;	
	
}

/*void List::printAllAdjacent(){
	
	if (this->north != NULL){ 
	
		cout<<"North - ";
		this->north->printShort();
		}
		
	if (this->south != NULL){ 
	
		cout<<"South - ";
		this->south->printShort();}
		
	if (this->east != NULL){ 
	
		cout<<"East - ";
		this->east->printShort();}
		
	if (this->west != NULL){ 
	
		cout<<"West - ";
		this->west->printShort();}
		
	return;
}*/