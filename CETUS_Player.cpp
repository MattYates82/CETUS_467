#include <iostream>
#include <string>
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5

using std::endl;
using std::cout;
using std::string;

	Player::Player(){
		
		this->health = 100;
		this->movesCompleted = 0;
		this->currentRoom = NULL;
		this->currentNeighbors = NULL;
		this->specialItemCount = 0;
		return;
	}
	
	Player::Player(Room* current, int currentHealth, int currentMoves, int currentSpecialCount){
		
		this->health = currentHealth;
		this->movesCompleted = currentMoves;
		this->currentRoom = current;
		this->currentNeighbors = current->getNeighbors();
		this->specialItemCount = currentSpecialCount;
		return;
	}
	
	string Player::getName(){
		
		return this->Name;
		
	}
	int Player::getHealth(){
		
		return this->health;
		
	}
	int Player::getMovesCompleted(){
		
		return this->movesCompleted;
		
	}
	
	void Player::setCurrentRoom(Room* current){
		
		this->currentRoom = current;
		return;
	}
	
	Room* Player::getCurrentRoom(){
		
		return this->currentRoom;
		
	}
	
	int Player::getSpecialItemCount(){
		
		return this->specialItemCount;
		
	}
	
	int Player::addItem(Item* current){
		
		this->inventory.push_back(current);
		
	}
	
	int Player::dropItem(string current){
		
		
		Item* temp = findItem(current, true);
		
		if (temp != NULL){
		
			this->currentRoom->addItem(temp);
			return 0; 
		}
		
		return 1;
		
	}
	
	Item* Player::findItem(string current, bool drop){
		
		for (int i = 0; i < this->inventory.size(); i++){
			
			if (this->inventory[i]->getName().compare(current)){
				
				Item* temp = this->inventory[i];
				
				if(drop == true){
					this->inventory[i] = NULL;
				}
				
				return temp;
			}
			
		}
		
		return NULL;
		
	}
	
	int Player::incrementMoves(){
		
		this->movesCompleted++;
		return 0;
		
	}
	int Player::decrementMoves(){
		
		this->movesCompleted--;
		return 0;
		
	}
	int Player::resurrectPlayer(Room* current){
		
		this->health = 100;
		this->movesCompleted = 0;
		this->currentRoom = current;
		this->currentNeighbors = current->getNeighbors();
		this->specialItemCount = 0;
		return 0;
		
	}
	int Player::damagePlayer(int damage){
		
		this->health -= damage;

		if(this->health < 0){
			
			this->health = 0;
			
		}
		
		return 0;
		
	}
	int Player::healPlayer(int health){
		
		this->health += health;

		if(this->health > 100){
			
			this->health = 100;
			
		}
		
		return 0;		
		
	}
	void Player::printAllAdjacent(){
		
		if (this->currentRoom->neighbors->north != NULL){
			
			cout << this->currentRoom->neighbors->north->Name << endl;
			
		}
		
		if (this->currentRoom->neighbors->south != NULL){
			
			cout << this->currentRoom->neighbors->south->Name << endl;
			
		}
		
		if (this->currentRoom->neighbors->east != NULL){
			
			cout << this->currentRoom->neighbors->east->Name << endl;
			
		}
		
		if (this->currentRoom->neighbors->west != NULL){
			
			cout << this->currentRoom->neighbors->west->Name << endl;
			
		}
		
		
		if (this->currentRoom->neighbors->up != NULL){
			
			cout << this->currentRoom->neighbors->up->Name << endl;
			
		}
		
		if (this->currentRoom->neighbors->down != NULL){
			
			cout << this->currentRoom->neighbors->down->Name << endl;
			
		}
		
		return;
	}
	
	void Player::printInventory(){
		
		if (this->inventory.size() == 0) { 
		
			cout << "Player has no items in inventory." << endl;
			return;
		}
		
		for (int i = 0; i < this->inventory.size(); i++){
			
			if (this->inventory[i] != NULL){
				cout << inventory[i]->getName();
			}
		}
		
		return;
		
	}
	void Player::printRoomInventory(){
		
		if (this->currentRoom->roomItems.size() == 0) { 
		
			cout << "Player has no items in inventory." << endl;
			return;
		}
		
		for (int i = 0; i < currentRoom->roomItems.size(); i++){
			
			if (currentRoom->roomItems[i] != NULL){
				cout << currentRoom->roomItems[i]->getName();
			}
		}
		
		return;		
		
	}
	void Player::printAdjacent(int direction){
		
		switch(direction){
			
			case NORTH:
				cout << this->currentRoom->neighbors->north->Name << endl;
				break;
			
			case SOUTH:
				cout << this->currentRoom->neighbors->south->Name << endl;
				break;
			
			case EAST:
				cout << this->currentRoom->neighbors->east->Name << endl;
				break;
			
			case WEST:
				cout << this->currentRoom->neighbors->west->Name << endl;
				break;
			
			case UP:
				cout << this->currentRoom->neighbors->up->Name << endl;
				break;
			
			case DOWN:
				cout << this->currentRoom->neighbors->down->Name << endl;
				break;
			
			default:
				break;
			
		}		
		return;		
		
	}
	
	void Player::move(int direction){
		
		switch(direction){
			
			case NORTH:
				this->currentRoom = this->currentRoom->neighbors->north;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case SOUTH:
				this->currentRoom = this->currentRoom->neighbors->south;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case EAST:
				this->currentRoom = this->currentRoom->neighbors->east;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case WEST:
				this->currentRoom = this->currentRoom->neighbors->west;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case UP:
				this->currentRoom = this->currentRoom->neighbors->up;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			case DOWN:
				this->currentRoom = this->currentRoom->neighbors->down;
				this->currentNeighbors = this->currentRoom->getNeighbors();
				break;
			
			default:
				break;
			
		}		
		return;
	}