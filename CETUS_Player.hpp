#include <string>

#define numItems 10

#ifndef CETUS_PLAYER_HPP
#define CETUS_PLAYER_HPP

using std::string;

class Item;
class Room;

class Player{
	
	private:
	
		string Name;
		int	health;
		int movesCompleted;
		Room* currentRoom;
		std::vector<Item*> inventory;
		int specialItemCount;
	
	public:
	
		Player();
		string getName();
		int getHealth();
		int getMovesCompleted();
		Room*	getCurrentRoom();
		int addItem(Item* current);
		int dropItem(Item* current);
		int incrementMoves();
		int decrementMoves();
		int resurrectPlayer(Room* current);
		int damagePlayer(int damage);
		int healPlayer(int health);
		void printAllAdjacent();
		void printInventory();
		void printRoomInventory();
		void printAdjacent(int direction);
	
};

#endif