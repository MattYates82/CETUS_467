#include <string>
#include <algorithm>
#include <vector>

#ifndef CETUS_ROOM_HPP
#define CETUS_ROOM_HPP

using std::string;

class Item;
class List;


class Room {
	
	private:
	
		friend class Player;
		string 	Name;
		string	longDesc;
		string	shortDesc;
		bool	visited;
		std::vector<Item*> roomItems;
		List* 	neighbors;
			
	public:
	
		Room();
		~Room();
		string getName();
		void addDescriptions(string longDesc, string shortDesc);
		void addItem(Item* current);
		void removeItem(Item* current);
		//void addNeighbor(int direction, Room* neigbor);
		void createNeighbors(List* neighborList);
		void getLong();
		void getShort();
		void setName(string currentName);
		void setVisited(bool visit);
		List* getNeighbors();
		Item* findItem(string current);
};
#endif