/****************************************************************************
**Program Filename:  main.cpp
**Author:  Jason Fisher
**Date:  10/6/2017
**Description:  Used to test function of data.cpp and data.hpp
****************************************************************************/
#include "CETUS_data.hpp"

int main() {
	/*//test create and populate map from loadFile function
	std::map <std::string, std::string> testMap;
	testMap = loadFile("./source/room_test.txt");

	//Output map elements to confirm
	//code from https://www.tutorialspoint.com/cpp_standard_library/cpp_map_end.htm
	std::cout << "The following elements were imported to map" <<std::endl;
	std::map<std::string, std::string>::iterator x;//declare iterator for loop
	for (x = testMap.begin(); x != testMap.end(); x++) {
		std::cout << x->first << "=" << x->second << std::endl;
	}
	std::cout << std::endl;

	//test output to new file
	std::cout << "Testing output to new file" << std::endl;
	saveFile("./save/test_output.txt", testMap);


	std::cout << "Files compiled and ran correctly" << std::endl;*/

	//test Item creation
	/*std::cout << "Testing Item Creation" << std::endl;
	std::string location = "./source/item_test.txt";
	Item* testItem = loadItem(location);
	std::map<std::string, Item*> itemMap;
	itemMap["test"] = testItem;
	std::cout << "Name = " << itemMap["test"]->getName() << std::endl;
	std::cout << "Description = " << itemMap["test"]->getDescription() << std::endl;
	std::cout << "Power = " << itemMap["test"]->getPower() << std::endl;
	std::cout << "Healing = " << itemMap["test"]->getHealing() << std::endl;
	std::cout << "weapon = " << itemMap["test"]->getWeapon() << std::endl;
	std::cout << "roomFeature = " << itemMap["test"]->getRoomFeature() << std::endl;
	std::cout << "collectible = " << itemMap["test"]->getCollectible() << std::endl;*/

	std::string location = "source";
	const int itemNum = 8;//set number of item files for array access
	const int roomNum = 2;//set number of room files for array access
	Item* tempItem;//will be used to temporarily store created items
	Room* tempRoom;//will be used to temporarily store created rooms
	Player curPlayer;//to hold player object
	std::string fileLocation;//will hold file path for data loading
	std::map<std::string, Item*> itemMap;//will store Item pointers for assignment to Rooms
	std::map<std::string, Room*> roomMap;//will store Room pointers for assignment to World
	std::map<std::string, std::vector<std::string>> adj;//map of vectors to contain room neighbors prior to assigning Lists in Rooms
	std::string key;//used to set key values for maps

	//create array holding list of all Item files
	std::string itemList[] = {"Bar.txt", "Businesses.txt", "Church Gate.txt", "Church Sign.txt", "Old Church.txt", "Lead Pipe.txt", "Key.txt", "Shovel.txt"};
	//create Item objects and store pointers in map
	for (int x = 0; x < itemNum; x++) {
		fileLocation = "./" + location + "/" + itemList[x];
		tempItem = loadItem(fileLocation);
		key = tempItem->getName();
		itemMap[key] = tempItem;
	}


	//create array holding list of all Room files
	std::string roomList[] = {"Main Street.txt", "Churchyard.txt"};
	//create Room objects and store pointers in map
	for (int x = 0; x < roomNum; x++) {
		fileLocation = "./" + location + "/" + roomList[x];
		tempRoom = loadRoom(fileLocation, itemMap, &adj);
		key = tempRoom->getName();
		roomMap[key] = tempRoom;
	}

	//Populate Room neighbor Lists
	loadList(&adj, &roomMap);

	//create Player object
	fileLocation = "./" + location + "/player.txt";
	curPlayer = loadPlayer(fileLocation, &roomMap, itemMap);


	return 0;
}