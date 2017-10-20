#include <string>
#include <iostream>
#include <algorithm>
#include "CETUS_Room.hpp"
#include "CETUS_List.hpp"
#include "CETUS_Items.hpp"


using std::endl;
using std::cout;
using std::cin;
using std::string;

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define UP 4
#define DOWN 5

int main(){
	
	//test run to display data structure and room class
	
	cout<<"Welcome to the short demo of the CETUS command line adventure game!\n\nToday, we will be demonstrating the List data structure that keeps track of all the adjacent rooms \n\nfor each room, as well as showing the details of the Room class\n\nLet's begin!\n"<<endl;
	
	string longDesc = "You are in a library, there are spiderwebs covering everything. You don't know how you got here, but you notice a cleaver in the\n\nfar corner. Also, there is a familiar odor and slight light emanating\n\nfrom behind one of the bookshelves.\n\n_________________________________________";
					
	string shortDesc = "Library - Covered in spiderwebs, cleaver in far corner, and smell/light coming from behind a bookshelf.\n\n";
	
	
	string Name = "cleaver\n";
	string Description = "heavy, blunt blade with strange etchings in the handle\n";
	int Power = 100;
	int Healing = 0;
	bool weapon = true;
	
	Item* cleaver = new Item(Name, Description, Power, Healing, weapon);
	Item* book = new Item("dingy book", "antique book with demonic writing and art", Power, Healing, false);
	
	Room* Library = new Room();
	Library->addItem(cleaver);
	Library->addItem(book);
	longDesc = "You are in a Library, there are spiderwebs covering everything. You don't know how you got here, but you notice\n\na cleaver in the far corner. Also, there is a familiar odor and slight light emanating from behind one of the bookshelves.\n\n";
					
	shortDesc = "Library - Covered in spiderwebs, cleaver in far corner, and smell/light coming from behind a bookshelf.\n\n";	
	Library->addDescriptions(longDesc, shortDesc);
	
	Room* Hallway = new Room();
	Hallway->addItem(cleaver);
	Hallway->addItem(book);
	
	longDesc = "You are in a Hallway, there are spiderwebs covering everything\n\nYou don't know how you got here, but you notice\n\na cleaver in the far corner. Also, there is a familiar odor and slight light emanating\n\nfrom behind one of the bookshelves.\n\n";
					
	shortDesc = "Hallway - Covered in spiderwebs, cleaver in far corner, and smell/light coming from behind a bookshelf.\n\n";	
	Hallway->addDescriptions(longDesc, shortDesc);
	
	Room* Foyer = new Room();
	Foyer->addItem(cleaver);
	Foyer->addItem(book);	
	longDesc = "You are in a Foyer, there are spiderwebs covering everything\nYou don't know how you got here, but you notice\n\na cleaver in the far corner. Also, there is a familiar odor and slight light emanating\n\nfrom behind one of the bookshelves.\n\n";
					
	shortDesc = "Foyer - Covered in spiderwebs, cleaver in far corner, and smell/light coming from behind a bookshelf.\n\n";	
	Foyer->addDescriptions(longDesc, shortDesc);	
	
	Room* Basement = new Room();
	Basement->addItem(cleaver);
	Basement->addItem(book);
	longDesc = "You are in a Basement, there are spiderwebs covering everything\nYou don't know how you got here, but you notice\n\na cleaver in the far corner. Also, there is a familiar odor and slight light emanating\n\nfrom behind one of the bookshelves.\n\n";
				
					
	shortDesc = "Basement - Covered in spiderwebs, cleaver in far corner, and smell/light coming from behind a bookshelf.\n\n";	
	Basement->addDescriptions(longDesc, shortDesc);

	List* neighborList = new List();
	neighborList->addAdjacent(NORTH, Hallway);
	neighborList->addAdjacent(SOUTH, Foyer);
	neighborList->addAdjacent(EAST, Basement);
	
	Library->createNeighbors(neighborList);
	
	Library->printLong();
	
	cout<<"Now we will be showing you the adjacent rooms and their descriptions!\n" << endl;
	
	cout<<"To the north - ";
	Library->neighbors->north->printShort();
	cout<<"\nTo the south - ";
	Library->neighbors->south->printShort();
	cout<<"\nTo the east - ";
	Library->neighbors->east->printShort();
		
	cout<<"Thanks for checking out the demo! Stay tuned for much more in the weeks to come!"<<endl;
	
	return 0;
	
}