#include <string>
#include "CETUS_Room.hpp"

#ifndef CETUS_WORLD_HPP
#define CETUS_WORLD_HPP

class Room;
class Item;
class Player;

class World {
	
	private:
	
		string	Name;
		string	Description;
		Player	currentPlayer;
		bool	realWorld;
		std::vector<Room*> worldRooms; 
	
	public:
	
		World();
		int	createRooms();
		int	createPlayer();
		int dropItems();
			
};
#endif