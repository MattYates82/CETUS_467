
#include <iostream>
#include <string>
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_World.hpp"



#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5
#define LINESIZE 80

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");


using std::endl;
using std::cout;
using std::string;

	World::World(){
		
		
		this->Name = ' ';
		this->Description = ' ';
		this->currentPlayer = NULL;
		this->realWorld = true;
		this->currentPlayer->setCurrentRoom(NULL);
		this->currentPlayer->setNeighbors(NULL);		
		
	}
	
	string World::getName(){
		
		return this->Name;
		
	}
	
	string World::getDescription(){
		
		this->Description;
		
	}
	
	Player* World::getPlayer(){
		
		return this->currentPlayer;
		
	}
	
	
	bool World::getRealWorld(){
		
		return this->realWorld;
		
	}
	
	Room* World::getCurrentRoom(){
		
		return this->currentPlayer->getCurrentRoom();
		
	}
	
	
	void World::setName(string current){
		
		this->Name = current;
		return;
		
	}
	
	void World::setDescription(string current){
		
		this->Description = current;
		return;		
		
	}
	
	void World::setPlayer(Player* current){
		
		this->currentPlayer = current;
		return;
		
		
	}
	
	void World::setRealWorld(bool current){
		
		this->realWorld = current;
		return;
		
	}
		
	void World::setCurrentRoom(Room* current){
		
		this->currentPlayer->setCurrentRoom(current);
		return;		
		
	}
	
	void World::dropItems(){}

	void World::addItem(Item* current){
		
		this->currentPlayer->inventory.push_back(current);
		return;
		
	}
	void World::dropItem(string current){
		
		Item* temp = findItem(current, true);
		if (temp != NULL){
			this->currentPlayer->currentRoom->addItem(temp);
		}
		
		return;		
	}
	
	Item* World::findItem(string current){
		
		for (int i = 0; i < this->currentPlayer->inventory.size(); i++){
			
			if (this->currentPlayer->inventory[i]->getName().compare(current)){
				
				return this->currentPlayer->inventory[i];
			}
			
		}
		
		return NULL;
		
	}
	
	Item* World::findItem(string current, bool drop){
		
		string tempString;
		
		Player* temp = this->currentPlayer;
		
		for (int i = 0; i < temp->inventory.size(); i++){
			
			tempString = temp->inventory[i]->getName();
			std::transform(tempString.begin(), tempString.end(), tempString.begin(), ::tolower);
			
			if (tempString.compare(0, tempString.size() -1, current)){
				
				Item* currentItem = temp->inventory[i];
				
				if(drop == true){
					temp->inventory[i] = NULL;
				}
				
				return currentItem;
			}
			
		}
		
		return NULL;
		
	}
	
	Item* World::findRoomItem(string current){
		
		for (int i = 0; i < this->currentPlayer->currentRoom->roomItems.size(); i++){
			
			if (this->currentPlayer->currentRoom->roomItems[i]->getName().compare(current)){
				
				return this->currentPlayer->inventory[i];
			}
			
		}
		
		return NULL;
		
	}
	void World::printAllAdjacent(){
		
		Player* temp = this->currentPlayer;
		
		if (temp->currentRoom->neighbors->north != NULL){
			
            cout << "North: "<< temp->currentRoom->neighbors->north->Name << endl;
			
		}
		
		if (temp->currentRoom->neighbors->south != NULL){
			
			cout << "South: "<< temp->currentRoom->neighbors->south->Name << endl;
			
		}
		
		if (temp->currentRoom->neighbors->east != NULL){
			
			cout <<  "East: "<<temp->currentRoom->neighbors->east->Name << endl;
			
		}
		
		if (temp->currentRoom->neighbors->west != NULL){
			
			cout << "West: "<< temp->currentRoom->neighbors->west->Name << endl;
			
		}
		
		
		if (temp->currentRoom->neighbors->up != NULL){
			
			cout << "Up: "<< temp->currentRoom->neighbors->up->Name << endl;
			
		}
		
		if (temp->currentRoom->neighbors->down != NULL){
			
			cout << "Down: "<< temp->currentRoom->neighbors->down->Name << endl;
			
		}
		
		return;
	}
	
	void World::printInventory(){
		Player* temp = this->currentPlayer;
		if (temp->inventory.size() == 0) { 
		
			cout << "Player has no items in inventory." << endl;
			return;
		}
		
		for (int i = 0; i < temp->inventory.size(); i++){
			
			if (temp->inventory[i] != NULL){
				cout << temp->inventory[i]->getName();
			}
		}
		
		return;
		
	}
	void World::printRoomInventory(){
		Player* temp = this->currentPlayer;
		if (temp->currentRoom->roomItems.size() == 0) { 
		
			cout << "Player has no items in inventory." << endl;
			return;
		}
		
		for (int i = 0; i < temp->currentRoom->roomItems.size(); i++){
			
			if (temp->currentRoom->roomItems[i] != NULL){
				cout << temp->currentRoom->roomItems[i]->getName();
			}
		}
		
		return;		
		
	}
	void World::printAdjacent(int direction){
		
		Player* temp = this->currentPlayer;
		switch(direction){
			
			case NORTH:
				cout << temp->currentRoom->neighbors->north->Name << endl;
				break;
			
			case SOUTH:
				cout << temp->currentRoom->neighbors->south->Name << endl;
				break;
			
			case EAST:
				cout << temp->currentRoom->neighbors->east->Name << endl;
				break;
			
			case WEST:
				cout << temp->currentRoom->neighbors->west->Name << endl;
				break;
			
			case UP:
				cout << temp->currentRoom->neighbors->up->Name << endl;
				break;
			
			case DOWN:
				cout << temp->currentRoom->neighbors->down->Name << endl;
				break;
			
			default:
				break;
			
		}		
		return;		
		
	}
	
	void World::move(int direction){
		
		Player* temp = this->currentPlayer;
		
		switch(direction){
			
			case NORTH:
				temp->setCurrentRoom(temp->currentRoom->neighbors->north);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			case SOUTH:
				temp->setCurrentRoom(temp->currentRoom->neighbors->south);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			case EAST:
				temp->setCurrentRoom(temp->currentRoom->neighbors->east);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			case WEST:
				temp->setCurrentRoom(temp->currentRoom->neighbors->east);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			case UP:
				temp->setCurrentRoom(temp->currentRoom->neighbors->up);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			case DOWN:
				temp->setCurrentRoom(temp->currentRoom->neighbors->down);
				temp->setNeighbors(temp->currentRoom->getNeighbors());
				break;
			
			default:
				break;
			
		}
        
		return;
	}
	
	

	void World::printLogo(){

	//source - https://www.uow.edu.au/~lukes/TEXTBOOK/notes-cpp/io/readtextfile.html

		cout << green;
		ifstream inFile;
		inFile.unsetf(std::ios_base::skipws);
		inFile.open("./cetus.txt");

		char temp;

		while(inFile >> temp){

			cout << temp;

		}
		cout << endl;
		cout << reset;
	}

	void World::ClearScreen(){

		//This is the least complex way to clear the screen and remain system agnostic

		for(int i = 0; i < 75; i++){

			cout << endl;

		}

	}

	void World::cetusPrint(string* inText, int color){
		
		switch(color){

			case 0:
				cout << red;
				break;

			case 1:

				cout << green;
				break;

			case 2:

				cout << yellow;
				break;

			case 3:

				cout << cyan;
				break;

			case 4:

				cout << magenta;
				break;

			default:

				break;

		}

		int count = 0;

		for (size_t i = 0; i < inText->length(); i++){

			if(count <= LINESIZE){


				cout << inText->at(i);
				count++;
				if(inText->at(i) == '\n'){
		
					count = 0;

				}

			}

			else{

						if(inText->at(i) != ' ' && inText->at(i) != '\n'){
					
					cout << inText->at(i);
								count++;
					
							}
				else{

									cout << endl;
									count = 0;

							}
							
			}
		
		}
		cout << reset;
		
		return;

}
