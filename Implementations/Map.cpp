/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/


#include <fstream>
#include <string>
#include "../Headers/Map.h"

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

// MapLoader - Create territory
void MapLoader::createTerritory() {
	Map listofterr(territories.size());
	//map1.setTerritoryNames(territories);

	for (int i = 1; i <= territories.size(); i++) {
		std::string tempTerritoryName = territories[i].substr(getNthSpace(territories[i], 0), getNthSpace(territories[i], getNthSpace(territories[i], 0)));
		std::string tempContinentName = continents[i].substr(getNthSpace(continents[i], 0), getNthSpace(continents[i], getNthSpace(continents[i], 0)));
		std::string tempEdge = edges[i].substr(getNthSpace(edges[i], 0), getNthSpace(edges[i], getNthSpace(edges[i], 0)));
		Territory tempTerritory(tempTerritoryName, tempContinentName, tempEdge, tempEdge, 0);
		listofterr.setTerritory(tempTerritory);
	}


	std::cout << "Map \"" << mapFileName << "\" has created.";
}

int MapLoader::getNthSpace(std::string inputString, int index) {
	return inputString.find(' ', index) + 1;
}


// Map - Constructor
Map::Map(int territoriesCount) {
	this->territoriesCount = territoriesCount;
}

// Map - Getters/Setters
void Map::setTerritory(Territory objTerritory) {
	territoryObjects.push_back(objTerritory);
}


// Territory - Constructors
Territory::Territory(std::string territoryName, std::string continentName, std::string edges, std::string playerName, int armyCount) {
	territoryName = territoryName;
	continentName = continentName;
	edges = edges;
	playerName = playerName;
	armyCount = armyCount;
}

// Territory - Getters/Setters
std::string Territory::getTerritoryName() {
	return territoryName;
}
std::string Territory::getContinentName() {
	return continentName;
}
std::string Territory::getEdges() {
	return edges;
}
std::string Territory::getPlayerName() {
	return playerName;
}
int Territory::getArmyCount() {
	return armyCount;
}
void Territory::setTerritoryName(std::string territoryName) {
	territoryName = territoryName;
}
void Territory::setContinentName(std::string continentName) {
	continentName = continentName;
}
void Territory::setEdges(std::string edges) {
	territoryName = territoryName;
}
void Territory::setPlayerName(std::string playerName) {
	playerName = playerName;
}
void Territory::setArmyCount(int armyCount) {
	armyCount = armyCount;
}
