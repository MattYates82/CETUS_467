/****************************************************************************
**Program Filename:  data.cpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  data.cpp file for CMD1 project.  Data files will control game
**data input from source files and data output to save files
****************************************************************************/
#include "CETUS_data.hpp"


/***************************************************************************
**Function:  loadFile
**Description:  Opens input source file, parses file data into map, and
**				returns the map
**Parameters:  std::string fileName
**Pre-Condition:  File exists and correct fileName is passed to function
**Post-Condition:  Map containing the source file data returned
**
**Code for parsing source file input from 
**https://stackoverflow.com/questions/31103883/reading-key-value-pairs-from-a-file-and-ignoring-comment-lines
****************************************************************************/
std::map<std::string, std::string> loadFile(std::string fileName) {
	//declare variables
	std::ifstream inputFile;
	std::string line;
	std::map<std::string, std::string> myMap;

	//open file
	inputFile.open(fileName.c_str());

	if (inputFile) {//if inputFile was opened correctly
		//parse inputFile to map
		while (std::getline(inputFile, line)){
			std::istringstream istring_line(line);
			std::string key;
			std::string value;
			if (std::getline(istring_line, key, '=')) {
				if (std::getline(istring_line, value)) {
					myMap[key] = value;
				}
			}
		}
	}
	else {//file was not opened correctly
		std::cout << fileName << " did not load correctly." << std::endl;
	}

	//close file
	inputFile.close();

	return myMap;
}




/***************************************************************************
**Function:  saveFile
**Description:  Opens or creates .txt save file based on path passed as string.
**				save map data to .txt save file, and closes file
**Parameters:  std::string fileName, std::map myMap
**Pre-Condition:  map exists and passed to function
**Post-Condition:  new save file is created or old save file is updated
**
**map output code based on the following source
**https://www.tutorialspoint.com/cpp_standard_library/cpp_map_end.htm
****************************************************************************/
void saveFile(std::string fileName, std::map<std::string, std::string> myMap) {
	//open or create output file
	std::ofstream outFile;
	outFile.open(fileName.c_str());

	if (outFile) {//if file opened correctly
		std::map<std::string, std::string>::iterator x;//declare iterator for loop
		//write values to file
		for (x = myMap.begin(); x != myMap.end(); x++) {
			outFile << x->first << "=" << x->second << std::endl;
		}
	}
	else {//if the file did not open
		std::cout << fileName << " did not save correctly." << std::endl;
	}

	//close file
	outFile.close();
}


/***************************************************************************
**Function:  loadItem
**Description:  Creates Item object based on .txt source file data
**Parameters:  std::string location
**Pre-Condition:  .txt source file exists
**Post-Condition:  new Item object is created and pointer is returned
****************************************************************************/
Item* loadItem(std::string location) {
	//declare variables
	std::map <std::string, std::string> tempMap;

	tempMap = loadFile(location);//load file data into tempMap

	Item* tempItem = new Item(tempMap["Name"], tempMap["Description"], tempMap["roomDescription"], std::stoi(tempMap["Power"]), std::stoi(tempMap["Healing"]), 
		std::stoi(tempMap["weapon"]), std::stoi(tempMap["roomFeature"]), std::stoi(tempMap["collectible"]));

	return tempItem;
}


/***************************************************************************
**Function:  loadRoom
**Description:  Creates Room object based on .txt source file data
**Parameters:  std::string location, map of Item pointers, map of string vectors by reference
**Pre-Condition:  .txt source file exists, itemMap has already been filled
**Post-Condition:  new Room object is created and pointer is returned
**		Also, will add adjacency list to map of string vectors
****************************************************************************/
Room* loadRoom(std::string location, std::map<std::string, Item*> itemMap, std::map<std::string, std::vector<std::string>> *adj) {
	//declare variables
	std::map<std::string, std::string> tempMap;
	std::map<std::string, std::string>::iterator it;//will be used to find Items in map
	std::vector<std::string> list;//will hold list of adjacent rooms to add to adj

	tempMap = loadFile(location);//load file data into tempMap

	Room* tempRoom = new Room;//create new Room with default constructor
	tempRoom->addDescriptions(tempMap["longDesc"], tempMap["shortDesc"]);//populate descriptions from tempMap
	tempRoom->setName(tempMap["Name"]);//set room name from map
	tempRoom->setVisited(std::stoi(tempMap["visited"]));//set room visited bool from map


	//Place items in Room
	//set map iterator to first item in map
	it = tempMap.find("Item01");
	while (it->first.compare(0, 4, "Item") == 0) {
		std::string itemName = it->second;
		tempRoom->addItem(itemMap[itemName]);
		it++;
	}


	//save adjacent Rooms to map of vectors to populate List later
	//List must be populated after all Rooms have been created
	//set map iterator to first adjacent room in map
	it = tempMap.find("adj0");
	while (it->first.compare(0, 3, "adj") == 0) {
		list.push_back(it->second);
		it++;
	}

	adj->insert(std::pair<string, std::vector<std::string>>(tempMap["Name"], list));


	return tempRoom;
}


/***************************************************************************
**Function:  loadList
**Description:  Populates Room objects with neighbor Lists
**Parameters:  map of string vectors holding adjacency lists, map of existing Room pointers, vector of Room pointers
**Pre-Condition:  Rooms have been created, adjacency list has been filled
**Post-Condition:  Rooms have populated neighbor Lists
****************************************************************************/
//commented out code below can be deleted if not needed
/*void loadList(const std::map<std::string, std::vector<std::string>> *adj, const std::map<std::string, Room*> *roomMap, std::vector<Room*> &rooms){
	std::string curRoom;//will hold a string denoting the current room being worked on
	std::string adjRoom;//will hold string denoting an adjacent room to the current room
	//loop through vector of Room* to fill adjacency lists
	for (int x = 0; x < rooms.size(); x++) {
		curRoom = rooms[x]->getName();//assign name of Room being accessed to curRoom
		List* tempList = new List();
		rooms[x]->createNeighbors(tempList);
		//loop through vector in adj
		//use Name for adj vector to place correct neighbors into rooms[x]
		for (int y = 0; y < adj->at(curRoom).size(); y++) {
			adjRoom = adj->at(curRoom)[y];//place an adjacent room name in adjRoom
			rooms[x]->addNeighbor(y, roomMap->at(adjRoom));
		}
	}
}*/

void loadList(std::map<std::string, std::vector<std::string>> *adj, std::map<std::string, Room*> *roomMap){

	std::string curRoom;//will hold a string denoting the current room being worked on
	std::string adjRoom;//will hold string denoting an adjacent room to the current room
	std::map <std::string, Room*>::iterator it;//iterator for roomMap
	std::map <std::string, std::vector<std::string>>::iterator aI;//iterator for adj
	//loop through vector of Room* to fill adjacency lists
	for (it = roomMap->begin(); it != roomMap->end(); it++) {
		curRoom = it->first;//assign name of Room being accessed to curRoom
		aI = adj->find(curRoom);
		List* tempList = new List;
		//loop through vector in adj
		//use Name for adj vector to place correct neighbors into rooms[x]
		for (int y = 0; y < aI->second.size(); y++) {
			adjRoom = aI->second[y];//place an adjacent room name in adjRoom
			if (adjRoom.compare(0, 4, "NULL") != 0) {
				tempList->addAdjacent(y, roomMap->at(adjRoom));
			}
		roomMap->at(curRoom)->createNeighbors(tempList);
		}
	}
}


/***************************************************************************
**Function:  loadPlayer
**Description:  Creates Player object based on .txt source file data
**Parameters:  std::string location, map of Item pointers, map of Room pointers
**Pre-Condition:  .txt source file exists, itemMap has already been filled, Rooms have been created
**Post-Condition:  new Player object is created returned
****************************************************************************/
Player loadPlayer(std::string location, const std::map<std::string, Room*> *rooms, std::map<std::string, Item*> itemMap) {
	//declare variables
	std::map <std::string, std::string> tempMap;
	std::map <std::string, std::string>::iterator it;//will be used to find Items in map

	tempMap = loadFile(location);//load file data into tempMap

	//call player constructor using tempMap to find current room from map of Room pointers
	Player tempPlayer(rooms->at(tempMap["currentRoom"]), std::stoi(tempMap["health"]), std::stoi(tempMap["movesCompleted"]), std::stoi(tempMap["specialItemCount"]));

	//Add functions to populate Name when available

	//Populate player inventory with Items
	//set map iterator to first item in map
	it = tempMap.find("Item01");
	while (it->first.compare(0, 4, "Item") == 0) {
		std::string itemName = it->second;
		tempPlayer.addItem(itemMap[itemName]);
		it++;
	}

	return tempPlayer;
}



/***************************************************************************
**Function:  loadWorld
**Description:  Control function to create World object, load all data for world from 
**		files, and return World object to game engine
**Parameters:  std::string location
**Pre-Condition:  .txt source files exist
**Post-Condition:  new World object is created and returned
****************************************************************************/
/*World loadWorld(std::string location) {
	const int itemNum = 3;//set number of item files for array access
	const int roomNum = 2;//set number of room files for array access
	Item* tempItem;//will be used to temporarily store created items
	Room* tempRoom;//will be used to temporarily store created rooms
	Player curPlayer;//to hold player object
	World gameWorld;//will be returned with full game data
	std::string fileLocation;//will hold file path for data loading
	std::map<std::string, Item*> itemMap;//will store Item pointers for assignment to Rooms
	std::map<std::string, Room*> roomMap;//will store Room pointers for assignment to World
	std::map<std::string, std::vector<std::string>> adj;//map of vectors to contain room neighbors prior to assigning Lists in Rooms
	std::string key;//used to set key values for maps

	//create array holding list of all Item files
	std::string itemList[] = {"Lead_Pipe.txt", "Key.txt", "Shovel.txt"};
	//create Item objects and store pointers in map
	for (int x = 0; x < itemNum; x++) {
		fileLocation = "./" + location + "/" + itemList[x];
		tempItem = loadItem(fileLocation);
		key = tempItem->getName();
		itemMap[key] = tempItem;
	}

	//create array holding list of all Room files
	std::string roomList[] = {"normStart.txt", "normBar.txt"};
	//create Room objects and store pointers in map
	for (int x = 0; x < roomNum; x++) {
		fileLocation = "./" + location + "/" + roomList[x];
		tempRoom = loadRoom(fileLocation, &itemMap, &adj);
		key = tempRoom->getName();
		roomMap[key] = tempRoom;
	}

	//Populate Room neighbor Lists
	loadList(&adj, &roomMap);

	//create Player object
	fileLocation = "./" + location + "/Player.txt";
	curPlayer = loadPlayer(fileLocation, &roomMap, &itemMap);

	//create and populate world with all above loaded data

	return gameWorld;
}*/