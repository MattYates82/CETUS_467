/****************************************************************************
**Program Filename:  main.cpp
**Author:  Jason Fisher and Josh Sears
**Date:  10/6/2017
**Description:  Used to test function of data.cpp and data.hpp and NOW contains parser
****************************************************************************/

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <string.h>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include <cstdlib>
//#include <windows.h>

#include "CETUS_data.hpp"
#include "CETUS_Items.hpp"
#include "CETUS_Player.hpp"
#include "CETUS_Room.hpp"
#include "CETUS_World.hpp"
#include "creature.hpp"
#include "ghost.hpp"
#include "battle.hpp"

const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

/*
 Required verbs:
 look - repeats the long form explanation of the room
 look at <feature/object> - gives a fictionally interesting explanation of the specified feature/object. Player should be able to “look at” items in inventory
 Directional verbs - player should be able to specify “go north” or “north” to be able to move north. Other room travel verbs should be considered, such as “jump north”
 take - acquire an object and place it in player’s inventory
 help - list a set of verbs the game understands. Not all verbs must be disclosed within this action in case some actions should remain fictionally hidden.
 inventory - list contents of inventory
 savegame - saves the state of the current game to a file
 Loadgame - confirms with the user that this really is desired, then loads the game state from the file
 */

//functions to create verb and noun lists for searching

void helper(){

    cout << yellow; 
    string spacer = "\t\t\t\t[";
    cout << "\nCommand Help List\n----------------------------------------------------------------------------------\n";
    cout << "Quit" << spacer << "Exits the game.]\n";
    cout << "Look" << spacer << "View the room and objects in the current area.]\n";
    cout << "Look At <object>" << "\t\t["  << "Inspect the <object>.]\n";
    cout << "Attack <target>" << "\t\t\t[" << "Tries to punch <target> with fists.]\n";
    cout << "Attack <target> with <object>\t[" << "Hit <target> with <object>.]\n";
    cout << "North/South/East/West/Up/Down\t[" << "Move in that direction.]\n";
    cout << "Take <object>" << "\t\t\t[" << "Try to pick up <object>.]\n";
    cout << "Drop <object>" << "\t\t\t[" << "Drop <object> from inventory.]\n";
    cout << "Inventory" << "\t\t\t[" << "Browse contents of inventory.]\n";
    cout << "Savegame" << "\t\t\t[" << "Saves current game progress.]\n";
    cout << "Loadgame" << "\t\t\t[" << "Loads last saved state.]\n";
    cout << "----------------------------------------------------------------------------------\n";
    cout << reset;

}

void mapMaker(std::map<std::string, int> *map){
    map->insert (std::pair<std::string, int>("quit", 0));
    map->insert (std::pair<std::string, int>("attack", 1));
    map->insert (std::pair<std::string, int>("hit", 1));
    map->insert (std::pair<std::string, int>("north", 2));
    map->insert (std::pair<std::string, int>("n", 2));
    map->insert (std::pair<std::string, int>("south", 3));
    map->insert (std::pair<std::string, int>("s", 3));
    map->insert (std::pair<std::string, int>("east", 4));
    map->insert (std::pair<std::string, int>("e", 4));
    map->insert (std::pair<std::string, int>("west", 5));
    map->insert (std::pair<std::string, int>("w", 5));
    map->insert (std::pair<std::string, int>("up", 6));
    map->insert (std::pair<std::string, int>("u", 6));
    map->insert (std::pair<std::string, int>("down", 7));
    map->insert (std::pair<std::string, int>("d", 7));
    map->insert (std::pair<std::string, int>("take", 8));
    map->insert (std::pair<std::string, int>("grab", 8));
    map->insert (std::pair<std::string, int>("inv", 9));
    map->insert (std::pair<std::string, int>("inventory", 9));
    map->insert (std::pair<std::string, int>("help", 10));
    map->insert (std::pair<std::string, int>("savegame", 11));
    map->insert (std::pair<std::string, int>("loadgame", 12));
    map->insert (std::pair<std::string, int>("l", 13));
    map->insert (std::pair<std::string, int>("look", 13));
    map->insert (std::pair<std::string, int>("look_at", 14));
    map->insert (std::pair<std::string, int>("inspect", 14));
    map->insert (std::pair<std::string, int>("drop", 15));
    return;
}

void displayRoom(Player* player, int look){
    
    string temp;
	cout << red;
    cout << "\n" << player->getCurrentRoom()->getName() << std::endl << std::endl;
    if((player->getCurrentRoom()->getVisited()==true) && (look==0)){
        player->getCurrentRoom()->getShort();
    }else {
        player->getCurrentRoom()->getLong();
        player->getCurrentRoom()->setVisited(true);
    }
    std::cout << "\n\nExits:\n";
    player->printAllAdjacent();
    std::cout << "\n";
	
	cout << reset;
}



int parser(World* game){
    
    
    //create variables to simulate a room, actions, items, etc
    std::string input, first, verb;
    Item* noun1 = new Item;
    Item* noun2 = new Item;
    //Creature* baddie = new Ghost;
    int choice;
    
    //Item* tester = new Item("tester", "testItem", 0, 0, true);
    
    std::vector <Item*> playerInv;
    std::map<std::string, int> mymap;
    mapMaker(&mymap);
    
    std::stringstream sstream;
    displayRoom(player, 0);
    
    
    
    while(1){
        
        sstream.str("");
        sstream.clear();
        first.clear();
        verb.clear();
        
        choice = -1;
        bool foundVerb = false;
        bool foundEnemy = false;
        bool foundNoun1 = false;
        bool foundNoun2 = false;
        bool withFlag = false;
        bool foundInv = false;
        bool foundRoom = false;
        bool found=false;
        Item* temp;
        printf("\nWhat are you going to do?\n");
        
        //Parse the input
        
        input.clear();
        std::cin.seekg(0,std::ios::end);
        std::cin.clear();
        
        
        std::getline(std::cin, input);
        
        //move to uppercase for matching purposes
        for(int i=0; i<input.size(); i++){
            input.at(i) = std::tolower(input.at(i));
        }
        sstream.str(input);
        
        //Look through all words for key verbs or nouns
        while(sstream >> first){
            found = false;
            if(mymap.count(first)>0){
                //printf("Found a verb match!\n");
                foundVerb = true;
                verb = first;
                found = true;
            }
            
            /*std::vector<Creature*> eList = player->getCurrentRoom()->getEnemies();
             for(int i = 0; i<eList.size();++i){
             if(first == eList[i]->getName()){
             if(!foundNoun1){
             //printf("Found a noun match!\n");
             foundNoun1=true;
             foundEnemy=true;
             baddie = eList[i];
             }
             }
             }
             */
            if(!found){
                temp = game->findItem(first,0);
                if(temp != NULL){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        noun1 = temp;
                        foundInv = true;
                        found=true;
                    } else {
                        //printf("Found a second noun match!\n");
                        foundNoun2=true;
                        noun2 = temp;
                        foundInv = true;
                        found = true;
                    }
                }
            }
            
            if(!found){
                temp = game->getCurrentRoom()->findItem(first);
                if(temp != NULL){
                    if(!foundNoun1){
                        //printf("Found a noun match!\n");
                        foundNoun1=true;
                        noun1 = temp;
                        foundRoom = true;
                    } else {
                        //printf("Found a second noun match!\n");
                        foundNoun2=true;
                        noun2 = temp;
                        foundRoom = true;
                    }
                }
            }
            
            
            
            if(first == "with"){
                withFlag = true;
            }
            if(verb == "look" && first == "at"){
                verb="look_at";
            }
            
        }
        
        if(mymap.count(verb) > 0){
            
            choice = mymap.find(verb)->second;
        }
        cout << cyan;
        switch(choice){
            case 0:  //Quit game
                std::cout << "So sad to see you leave...\n";
                return 0;
            case 1:  //Attack, Hit
                if(foundNoun2 && withFlag && foundEnemy){
                    //battle(player, ghost1, noun2->getPower());
                } else if (foundEnemy){
                    //   battle(player, ghost1, 0);
                } else {
                    cout << "What do you want to attack?\n";
                    
                }
                break;
            case 2: //North, n
                game->move(0);
                displayRoom(game, 0);
                break;
            case 3:  //South, s
                game->move(1);
                displayRoom(game, 0);
                break;
                
            case 4:  //East, e
                game->move(2);
                displayRoom(game, 0);
                break;
            case 5:  //West, w
                game->move(3);
                displayRoom(game, 0);
                break;
            case 6:  //Up, u
                game->move(4);
                displayRoom(game, 0);
                break;
            case 7:  //Down, d
                game->move(5);
                displayRoom(game, 0);
                break;
            case 8:  //Grab, Take
                if(foundRoom && foundNoun1){
                    game->addItem(noun1);
                    game->getCurrentRoom()->removeItem(noun1);
                }else {
                    cout << "I don't see that in the room.\n";
                }
                break;
            case 9:  //Inventory, inv
                game->printInventory();
                break;
            case 10:  //Help
                helper();
                break;
            case 11:  //Savegame
                std::cout << "Your game was saved succesfully.\n";
                break;
            case 12:  //Loadgame
                std::cout << "Your game was successfully loaded!\n";
                break;
            case 13:  //Look
                //Display the correct room description.
                displayRoom(game, 1);
                
                break;
            case 14:  //Look At
                if(foundNoun1){
                    cout << noun1->getDescription();
                } else {
                    cout << "I don't know what you want to look at.\n";
                }
                break;
            case 15: //Drop
                if(foundInv && foundNoun1){
                    game->getCurrentRoom()->addItem(noun1);
                    game->dropItem(noun2->getName());
                } else {
                    cout << "I don't see that in your inventory.\n";
                }
                break;
            default:
                std::cout << "I don't know what you are asking for.\n";
				cout << reset;
        }
		cout << reset;
    }
    cout << reset;
    return 0;
    
    
}

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
    const int itemNum = 9;//set number of item files for array access
    const int roomNum = 5;//set number of room files for array access
    Item* tempItem;//will be used to temporarily store created items
    Room* tempRoom;//will be used to temporarily store created rooms
    World curGame;//to hold player object
    std::string fileLocation;//will hold file path for data loading
    std::map<std::string, Item*> itemMap;//will store Item pointers for assignment to Rooms
    std::map<std::string, Room*> roomMap;//will store Room pointers for assignment to World
    std::map<std::string, std::vector<std::string>> adj;//map of vectors to contain room neighbors prior to assigning Lists in Rooms
    std::string key;//used to set key values for maps
    
    //create array holding list of all Item files
    std::string itemList[] = {"Bar.txt", "Businesses.txt", "Corpse.txt", "Church Gate.txt", "Church Sign.txt", "Old Church.txt", "Lead Pipe.txt", "Key.txt", "Shovel.txt"};
    //create Item objects and store pointers in map
    for (int x = 0; x < itemNum; x++) {
        fileLocation = "./" + location + "/" + itemList[x];
        tempItem = loadItem(fileLocation);
        key = tempItem->getName();
        itemMap[key] = tempItem;
    }
    
    
    //create array holding list of all Room files
    std::string roomList[] = {"Main Street.txt", "Churchyard.txt", "Stables.txt", "Training.txt", "Studio.txt"};
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
    curGame = loadPlayer(fileLocation, &roomMap, itemMap);
    curGame.ClearScreen();
    string intro = "Welcome to the CETUS CMD1 Midpoint demonstration! Today, you will be able to see our data parser, command parser and data structures in action; however, full functionality won't be available at this time. Some features that will be coming soon include: \n-Save option\n-Scary creatures and other unknown entities\n-Combat system\n-World flipping alternate dimensions\n-Additional items and rooms\n-Plot enhancements & more!\n";
    string* temp = &intro;

    curGame.printLogo();
    curGame.cetusPrint(temp, 3);
   
    parser(&curGame);
    cout << reset;
    return 0;
}

