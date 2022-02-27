/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/


#include <fstream>
#include <string>
#include <sstream>
#include "../Headers/Map.h"

// MapLoader - Constructor/Destructor
MapLoader::MapLoader(std::string inputFileName) {
	this->mapFileName = inputFileName;
	this->fieldCount = 0;
}


// MapLoader - Validate map
bool MapLoader::validateMap() {
	std::cout << "\nValidating map file \"" << mapFileName << "\"...";
	std::ifstream mapFile(mapFileName);
	std::string currentLine;
	bool insideContinents = false, insideCountries = false, insideBorders = false;

	while (getline(mapFile, currentLine)) { // Get the current section of the map file
		if (currentLine == "[continents]") {
			fieldCount++;
			insideContinents = true;
			insideCountries = false;
			insideBorders = false;
			continue;
		}
		else if (currentLine == "[countries]") {
			fieldCount++;
			insideCountries = true;
			insideContinents = false;
			insideBorders = false;
			continue;
		}
		else if (currentLine == "[borders]") {
			fieldCount++;
			insideBorders = true;
			insideContinents = false;
			insideCountries = false;
			continue;
		}
		else if (currentLine.empty()) {
			insideContinents = false;
			insideCountries = false;
			insideBorders = false;
			continue;
		}
		else if (currentLine.at(0) == ';') { // A comment -> ignore
			continue;
		}

		if (insideContinents) { // Inside "Continents" section
			continents.push_back(currentLine);
		}
		else if (insideCountries) { // Inside "Countries" section
			countries.push_back(currentLine);
		}
		else if (insideBorders) { // Inside "Borders" section
			borders.push_back(currentLine);
		}
	}
	if (fieldCount == 3) { // All 3 fields has been found -> valid
		return true;
	}
	return false; // Invalid map
}

// MapLoader - Create territory
void MapLoader::createTerritory() {
	std::cout << "\nCreating territories...";
	for (int i = 0; i < countries.size(); i++) {
		std::string territoryName = extractWord(countries[i], 1);
		std::string continentName = extractWord(continents[extractInt(countries[i], 2) - 1], 0);
		std::string playerName = "example_player_name";
		int armyCount = 5;
		Territory tempTerritory(territoryName, continentName, playerName, armyCount);
		territories.push_back(tempTerritory);
	}
}

// MapLoader - Build the map
void MapLoader::buildMap() {
	createTerritory();

	std::cout << "\nBuilding the map...";
	Map map(territories.size());
	std::vector<int> edges;

	for (int i = 0; i < territories.size(); i++) {
		edges = extractAllInt(borders[i]);
		for (int j = 1; j < edges.size(); j++) {
			map.setEdge(i, edges[j] - 1);
		}
	}
}

// MapLoader - Get nth word/number in a string
std::string MapLoader::extractWord(std::string inputString, int index) {
	std::stringstream ss;
	ss << inputString;
	std::vector<std::string> words;
	std::string temp;
	while (!ss.eof()) {
		ss >> temp;
		words.push_back(temp);
		temp = "";
	}
	return words[index];
}
int MapLoader::extractInt(std::string inputString, int index) {
	std::stringstream ss;
	ss << inputString;
	std::vector<int> numbers;
	std::string temp;
	int temp2;
	while (!ss.eof()) {
		ss >> temp;
		std::stringstream(temp) >> temp2;
		numbers.push_back(temp2);
	}
	return numbers[index];
}
// MapLoader - Get all integers from a string
std::vector<int> MapLoader::extractAllInt(std::string inputString) {
	std::stringstream ss;
	ss << inputString;
	std::vector<int> numbers;
	std::string temp;
	int temp2;
	while (!ss.eof()) {
		ss >> temp;
		std::stringstream(temp) >> temp2;
		numbers.push_back(temp2);
	}
	return numbers;
}


// Map - Constructor/Destructor
Map::Map(int territoriesCount) {
	this->territoriesCount = territoriesCount;
	map = new std::list<int>[territoriesCount];
}

Map::~Map() {
	delete[] map;
}

// Map - Getters/Setters
std::list<int> Map::getEdge(int index) {
	return map[index];
}
void Map::setEdge(int edgeA, int edgeB) {
	this->map[edgeA].push_back(edgeB);
	this->map[edgeB].push_back(edgeA);
}

// Map - Validate



// Territory - Constructors/Destructor
Territory::Territory() {
	this->territoryName = "";
	this->continentName = "";
	this->playerName = "";
	this->armyCount = 0;
}
Territory::Territory(std::string territoryName, std::string continentName, std::string playerName, int armyCount) {
	this->territoryName = territoryName;
	this->continentName = continentName;
	this->playerName = playerName;
	this->armyCount = armyCount;
}
Territory::~Territory() {
	territoryName.clear();
	continentName.clear();
	playerName.clear();
}

// Territory - Getters/Setters
std::string Territory::getTerritoryName() {
	return this->territoryName;
}
std::string Territory::getContinentName() {
	return this->continentName;
}
std::string Territory::getPlayerName() {
	return this->playerName;
}
int Territory::getArmyCount() {
	return this->armyCount;
}
void Territory::setTerritoryName(std::string territoryName) {
	this->territoryName = territoryName;
}
void Territory::setContinentName(std::string continentName) {
	this->continentName = continentName;
}
void Territory::setPlayerName(std::string playerName) {
	this->playerName = playerName;
}
void Territory::setArmyCount(int armyCount) {
	this->armyCount = armyCount;
}
