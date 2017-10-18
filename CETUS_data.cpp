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
**Post-Condition:  new Item object is created and returned
****************************************************************************/
Item* loadItem(std::string location) {
	//declare variables
	std::map <std::string, std::string> tempMap;

	tempMap = loadFile(location);//load file data into tempMap

	Item* tempItem = new Item(tempMap["Name"], tempMap["Description"], std::stoi(tempMap["Power"]), std::stoi(tempMap["Healing"]), std::stoi(tempMap["weapon"]));

	return tempItem;
}