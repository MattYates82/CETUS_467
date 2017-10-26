#include <string>
#include <vector>
#define numItems 10
//#include "CETUS_Room.hpp"

#ifndef CETUS_PLAYER_HPP
#define CETUS_PLAYER_HPP

using std::string;

class Item;
class Room;
class List;

class Player{

	private:
	
		string Name;
		int	health;
		int movesCompleted;
		Room* currentRoom;
		std::vector<Item*> inventory;
		int specialItemCount;
		List* currentNeighbors;
	
	public:
	
		Player();
		Player(Room* current, int currentHealth, int currentMoves, int currentSpecialCount);
		string getName();
		int getHealth();
		int getMovesCompleted();
		Room*	getCurrentRoom();
		int getSpecialItemCount();
		void setCurrentRoom(Room* current);
		int addItem(Item* current);
		int dropItem(string current);
		int incrementMoves();
		int decrementMoves();
		int resurrectPlayer(Room* current);
		int damagePlayer(int damage);
		int healPlayer(int health);
		void printAllAdjacent();
		void printInventory();
		void printRoomInventory();
		void printAdjacent(int direction);
		void move(int direction);
		Item* findItem(string current, bool drop);
	
};

#endif