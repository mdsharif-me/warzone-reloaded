/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/


#include <fstream>
#include <string>
#include <sstream>
#include "../Headers/Map.h"
using namespace std;

// MapLoader - Constructor/Destructor
MapLoader::MapLoader(string inputFileName) {
	this->mapFileName = inputFileName;
	this->fieldCount = 0;
}
MapLoader::~MapLoader() {
    delete m;
}
// MapLoader - Validate map
bool MapLoader::validateMap() {
	cout << "\nValidating map file \"" << mapFileName << "\"...";
	ifstream mapFile(mapFileName);
	string currentLine;
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
	cout << "\nCreating territories...";
	for (int i = 0; i < countries.size(); i++) {
		string territoryName = extractWord(countries[i], 1);
		string continentName = extractWord(continents[extractInt(countries[i], 2) - 1], 0);
		Territory* tempTerritory = new Territory(territoryName, continentName);
		//territories.push_back(tempTerritory);
        m->addTerritory(tempTerritory);
	}
}
// MapLoader - Build the map
void MapLoader::buildMap() {
	createTerritory();

	cout << "\nBuilding the map...";
	Map map(territories.size());
	vector<int> edges;

	for (int i = 0; i < territories.size(); i++) {
		edges = extractAllInt(borders[i]);
		for (int j = 1; j < edges.size(); j++) {
			map.setEdge(i, edges[j] - 1);
		}
	}
}
// MapLoader - Get nth word/number in a string
string MapLoader::extractWord(string inputString, int index) {
	stringstream ss;
	ss << inputString;
	vector<string> words;
	string temp;
	while (!ss.eof()) {
		ss >> temp;
		words.push_back(temp);
		temp = "";
	}
	return words[index];
}
int MapLoader::extractInt(string inputString, int index) {
	stringstream ss;
	ss << inputString;
	vector<int> numbers;
	string temp;
	int temp2;
	while (!ss.eof()) {
		ss >> temp;
		stringstream(temp) >> temp2;
		numbers.push_back(temp2);
	}
	return numbers[index];
}
// MapLoader - Get all integers from a string
vector<int> MapLoader::extractAllInt(string inputString) {
	stringstream ss;
	ss << inputString;
	vector<int> numbers;
	string temp;
	int temp2;
	while (!ss.eof()) {
		ss >> temp;
		stringstream(temp) >> temp2;
		numbers.push_back(temp2);
	}
	return numbers;
}


// Map - Constructor/Destructor
Map::Map(int territoriesCount) {
	this->territoriesCount = territoriesCount;
	map = new list<int>[territoriesCount];
}
Map::Map(const Map &map) {
    //TODO:
}
Map::~Map() {
	delete[] map;
    for (auto t : territories)
    {
        delete t;
    }
    this->territories.clear();
    for (auto c : continents)
    {
        delete c;
    }
    this->continents.clear();
}
// Map - Getters/Setters
/*list<int> Map::getEdge(int index) {
	return map[index];
}*/
void Map::addEdge(Territory *edgeA, Territory *edgeB) {
    edgeA->getAdjTerritories().push_back(edgeB);
    edgeB->getAdjTerritories().push_back(edgeA);
}
void Map::addTerritoryToContinent(Territory *territory, int continentId) {
    this->getContinents()[continentId]->addTerritory(territory);
}
// Map - Validate TODO:
vector<Territory *> Map::getTerritories() {
    return this->territories;
}
void Map::addTerritory(Territory *t) {
    this->territories.push_back(t);
}
vector<Continent *> Map::getContinents() {
    return this->continents;
}
void Map::addContinent(Continent *c) {
    this->continents.push_back(c);
}
int Map::visitNeighbours(Territory *territory, int visited) {
    vector<Territory*> adjacentNodes = territory->getAdjTerritories();
    for (size_t i = 0; i < adjacentNodes.size(); i++) {
        if (adjacentNodes[i]->getIsVisited() == false) {
            adjacentNodes[i]->setIsVisited(true);
            visited = visitNeighbours(adjacentNodes[i], visited);
        }
    }
    cout << "\nVisiting " + territory->getTerritoryName() + "..." << endl;
    cout << "Total territories visited: " + to_string(visited + 1) << endl;
    return visited + 1;
}
void Map::resetVisitedTerritories() {
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->getIsVisited() == true) {
            territories[i]->setIsVisited(false);
        }
    }
}
bool Map::checkMapConnectedGraph() {
    resetVisitedTerritories();
    int visited = 0;
    for (size_t i = 0; i < territories.size(); i++) {
        if (territories[i]->getIsVisited() == false) {
            territories[i]->setIsVisited(true);
            if (territories[i]->getAdjTerritories().size() == 0) {
                cout << "\nThis Map does not represented a connected graph" << endl;
                return false;
            }
            visited = visitNeighbours(territories[i], visited);
        }
    }
    cout << "\nNumber of territories in the map: " + to_string(visited) << endl;
    if (visited == territories.size()) {
        cout << "\nThis Map represents a connected graph!" << endl;
        return true;
    }
    else {
        cout << "\nThis Map is does not represented as a connected graph!***" << endl;
        return false;
    }
}
bool Map::mapValidate() {
    return true;
}
bool Map::checkContinentGraphs() {
    return false;
}
bool Map::checkIfValidContinent() {
    map<string, string> listOfCountries;
    for (size_t i = 0; i < continents.size(); i++) {
        vector<Territory*> allTerritoriesInContinent = continents[i]->getMembers();
        for (size_t j = 0; j < allTerritoriesInContinent.size(); j++)
            if (listOfCountries.count(allTerritoriesInContinent[j]->getTerritoryName()) > 0) {
                cout << "\n***Territory " + allTerritoriesInContinent[j]->getTerritoryName() + " DOES NOT have unique membership!" << endl;
                return false;
            }
            else {
                listOfCountries[allTerritoriesInContinent[j]->getTerritoryName()] = allTerritoriesInContinent[j]->getContinentName();
            }
    }
    cout << "\n***Territories have unique membership!***" << endl;
    return true;
}
int Map::visitContinentNeighbours(Territory *territory, string continent, int visited) {
    vector<Territory*> adjacentTerritories = territory->getAdjTerritories();
    for (size_t i = 0; i < adjacentTerritories.size(); i++) {
        if (adjacentTerritories[i]->getIsVisited() == false && adjacentTerritories[i]->getContinentName() == continent) {
            adjacentTerritories[i]->setIsVisited(true);
            visited = visitContinentNeighbours(adjacentTerritories[i], continent, visited);
        }
    }
    cout << "\nVisiting " + territory->getTerritoryName() + "..." << endl;
    cout << "Total territories visited: " + to_string(visited + 1) << endl;
    return visited + 1;
}


// Territory - Constructors/Destructor
Territory::Territory() {
	this->territoryName = "";
	this->continentName = "";
	this->playerOwnedBy = new Player();
	this->armyCount = 0;
}
Territory::Territory(string territoryName, string continentName, string playerName, int armyCount) {
	this->territoryName = territoryName;
	this->continentName = continentName;
	this->playerOwnedBy->setName(playerName);
	this->armyCount = armyCount;
}
Territory::Territory(string territoryName, string continentName) {
    this->territoryName = territoryName;
    this->continentName = continentName;
}
Territory::~Territory() {
	territoryName.clear();
	continentName.clear();
	delete playerOwnedBy;
}
bool Territory::getIsVisited() {
    return this->isVisited;
}
void Territory::setIsVisited(bool visited) {
    this->isVisited = visited;
}
// Territory - Getters/Setters
string Territory::getTerritoryName() {
	return this->territoryName;
}
string Territory::getContinentName() {
	return this->continentName;
}
string Territory::getPlayerName() {
	return this->playerName;
}
int Territory::getArmyCount() {
	return this->armyCount;
}
void Territory::setTerritoryName(string territoryName) {
	this->territoryName = territoryName;
}
void Territory::setContinentName(string continentName) {
	this->continentName = continentName;
}
void Territory::setPlayerName(string playerName) {
	this->playerName = playerName;
}
void Territory::setArmyCount(int armyCount) {
	this->armyCount = armyCount;
}
void Territory::addAdjTerritory(Territory *t) {
    this->adjTerritories.push_back(t);
}
vector<Territory *> Territory::getAdjTerritories() {
    return this->adjTerritories;
}

//Default Constructor
Continent::Continent() {};
Continent::Continent(string name, int armies) {
    this->name = name;
    controlBonus = armies;
}
Continent::Continent(string name, int armies, vector<Territory*> members) {
    this->name = name;
    controlBonus = armies;
    this->members = members;
}
// Copy constructor
Continent::Continent(const Continent &continent) {
    this->name = continent.name;
    this->controlBonus = continent.controlBonus;
    this->members = continent.members;
}
// Assignment operator
Continent& Continent::operator=(const Continent &continent) {
    this->name = continent.name;
    this->controlBonus = continent.controlBonus;
    this->members = continent.members;
    return *this;
}
// Stream insertion operator
ostream& operator << (ostream &out, Continent continent) {
    out << "Name: " << continent.getName();
    return out;
}
// Add territory as a member of the continent
void Continent::addTerritory(Territory* territory) {
    members.push_back(territory);
}
// Return name of continent
string Continent::getName() {
    return name;
}
// Return list of territories that are a part of continent
vector<Territory*> Continent::getMembers() {
    return members;
}
int Continent::getControlBonus() {
    return controlBonus;
}


