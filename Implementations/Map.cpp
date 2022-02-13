/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/


#include <fstream>
#include <string>
#include "Map.h"

// MapLoader - Constructor
MapLoader::MapLoader(std::string inputFileName) {
	mapFileName = inputFileName;
	fieldCount = 0;
}

// MapLoader - Validate map
bool MapLoader::validateMap() {
	std::ifstream mapFile(mapFileName);
	std::string currentLine;
	bool insideContinents = false, insideCountries = false, insideBorders = false;

	while (getline(mapFile, currentLine)) {
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
			territories.push_back(currentLine);
		}
		else if (insideBorders) { // Inside "Borders" section
			edges.push_back(currentLine);
		}
	}
	if (fieldCount == 3) { // All 3 fields has been found -> valid
		return true;
	}
	return false; // Invalid map
}

// MapLoader - Create map
void MapLoader::createMap() {
	Map map1(territories.size());
	map1.setTerritoryNames(territories);


	std::cout << "Map \"" << mapFileName << "\" has created.";
}


// Map - Constructor
Map::Map(int territoriesCount) {
	this->territoriesCount = territoriesCount;
	territories = new std::list<int>[territoriesCount];
}

// Map - Getters/Setters
std::vector<std::string> Map::getTerritoryNames() {
	return territoryNames;
}
void Map::setTerritoryNames(std::vector<std::string> inputVector) {
	territoryNames = inputVector;
}

// Map - Add adjacency
void Map::addTerritoryEdge(int TerritoryA, int TerritoryB) {
	territories[TerritoryA].push_back(TerritoryB);
	territories[TerritoryB].push_back(TerritoryA);
}
