#include <string>
#include "CETUS_Room.hpp"

#ifndef CETUS_WORLD_HPP
#define CETUS_WORLD_HPP

class Room;
class Item;
class Player;
class List;

class World {
	
	private:
	
		string	Name;
		string	Description;
		Player*	currentPlayer;
		bool	realWorld;
		std::vector<Room*> worldRooms; 
	
	public:
	
		World();
		int	createRooms();
		int	createPlayer();
		void dropItems();
		void dropItem(Item* current);
		string getName();
		string getDescription();
		Player* getPlayer();
		bool getRealWorld();
		Room* getCurrentRoom();
		void setName(string newName);
		void setDescription(string newDesc);
		void setPlayer(Player* currentP);
		void setRealWorld(bool real);
		void setCurrentRoom(Room* currentR);
		void addItem(Item* current);
		void dropItem(string current);	
		Item* findItem(string);
		Item* findItem(string current, bool drop);	
		Item* findRoomItem(string current);
		void printAllAdjacent();	
		void printInventory();
		void printRoomInventory();
		void printAdjacent(int direction);
		void move(int direction);
		void printLogo();
		void ClearScreen();
		void cetusPrint(string* inText, int color);
	
};
#endif