/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/
#include "../Headers/Map.h"
using namespace std;

class Territory;

// MapLoader - Constructor/Destructor
MapLoader::MapLoader(string inputFileName) {
	this->mapFileName = inputFileName;
	this->fieldCount = 0;
}
MapLoader::MapLoader(const MapLoader &mapLoader) {
    this->fieldCount = mapLoader.fieldCount;
    this->borders = mapLoader.borders;
    this->countries = mapLoader.countries;
    this->continents = mapLoader.continents;
}
MapLoader::~MapLoader() {
    continents.clear();
    countries.clear();
    borders.clear();
}
// MapLoader - Validate map
bool MapLoader::extract() {
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
		fieldCount = 0;
        return true;
	}
	return false; // Invalid map
}
// MapLoader - Create territory
Map *MapLoader::createMap() {
    Map *map = new Map(); // new Map
    for (int i = 0; i < continents.size(); i++){
        vector<string> singleContinentInfo = simpleTokenizer(continents[i]);
        string continentName = singleContinentInfo[0];
        string armies = singleContinentInfo[1];
        Continent* tempContinent = new Continent(continentName, stoi(armies));
        map->addContinent(tempContinent);
    }
    for (int i = 0; i < countries.size(); i++) {
        vector<string> singleCountryInfo = simpleTokenizer(countries[i]);
        string territoryName = singleCountryInfo[1];
        //string territoryName = extractWord(countries[i], 1);
        //string continentName = extractWord(continents[extractInt(countries[i], 2) - 1], 0);
        string continentName = map->getContinents()[stoi(singleCountryInfo[2])-1]->getName();
        Territory* tempTerritory = new Territory(territoryName, continentName);
        //territories.push_back(tempTerritory);
        map->getContinents()[stoi(singleCountryInfo[2])-1]->addTerritory(tempTerritory);
        map->addTerritory(tempTerritory);
    }
    for(int i = 0; i < borders.size(); i++){
        vector<string> singleBorderInfo = simpleTokenizer(borders[i]);
        int countryID = stoi(singleBorderInfo[0]);
        for (int j = 1; j < singleBorderInfo.size(); j++){
            Territory* territory1 = map->getTerritories()[countryID - 1];
            Territory* territory2 = map->getTerritories()[stoi(singleBorderInfo[j]) -1];
            map->addEdge(territory1, territory2);
        }
    }
    return map;
}
// MapLoader - Build the map
void MapLoader::buildMap() {
	Map* map = createMap();
	cout << "\nBuilding the map...";
	//Map map(territories.size());
	//vector<int> edges;

	//for (int i = 0; i < territories.size(); i++) {
	//	edges = extractAllInt(borders[i]);
	//	for (int j = 1; j < edges.size(); j++) {
	//		map.setEdge(i, edges[j] - 1);
	//	}
	//}
}
// MapLoader - Get nth word/number in a string
// MapLoader - Get all integers from a string
vector<string> MapLoader::simpleTokenizer(string s) {
    vector<string> results;
    stringstream ss(s);
    string word;
    while (ss >> word) {
        results.push_back(word);
    }
    return results;
}
bool MapLoader::isNumber(const string& number)
{
    for (char const &c : number) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
MapLoader &MapLoader::operator=(const MapLoader &mapLoader) {
    this->fieldCount = mapLoader.fieldCount;
    this->continents = mapLoader.continents;
    this->countries = mapLoader.countries;
    this->borders = mapLoader.borders;

    return *this;
}
ostream &operator<<(ostream &out, const MapLoader &mapLoader) {
    out << "Map Name: " << mapLoader.mapFileName << endl;
    return out;
}


// Map - Constructor/Destructor
Map::Map(const Map &map) {
    //TODO:
}
Map::~Map() {
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
void Map::addEdge(Territory *edgeA, Territory *edgeB) {
    edgeA->addAdjTerritory(edgeB);
    edgeB->addAdjTerritory(edgeA);
}

void Map::addTerritoryToContinent(Territory *territory, int continentId) {
    this->getContinents()[continentId]->addTerritory(territory);
}

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
    cout << visited << endl;
    cout << territories.size() << endl;
    if (visited == territories.size()) {
        cout << "\nThis Map represents a connected graph!" << endl;
        return true;
    }
    else {
        cout << "\nThis Map does not represented a connected graph!***" << endl;
        return false;
    }
}
bool Map::mapValidate() {
    if (checkIfValidContinent()) {
        if (checkMapConnectedGraph()) {
            if (checkContinentGraphs()) {
                cout << "\n***Map is valid!***" << endl;
                return true;
            }
        }
    }
    else {
        cout << "\n***Map is not valid!***" << endl;
        return false;
    }
}
bool Map::checkContinentGraphs() {
    resetVisitedTerritories();
    for (size_t i = 0; i < continents.size(); i++) {
        string continentName = continents[i]->getName();
        vector<Territory*> continentMembers = continents[i]->getMembers();
        cout << "\nChecking " + continentName + " which has " + to_string(continentMembers.size()) + " members..." << endl;
        int visited = 0;
        for (size_t j = 0; j < continentMembers.size(); j++) {
            if (!continentMembers[j]->getIsVisited()) {
                continentMembers[j]->setIsVisited(true);
                if (continentMembers[j]->getAdjTerritories().empty()) {
                    cout << "\n***Continent " + continents[i]->getName() + " is NOT a connected subgraph!***" << endl;
                    return false;
                }
                visited = visitContinentNeighbours(continentMembers[j], continentName, visited);
            }
        }
        cout << "\nTotal territories in continent: " + to_string(visited) << endl;
        if (visited == continentMembers.size()) {
            cout << "\n***Continent " + continents[i]->getName() + " is a connected subgraph!***" << endl;
        }
        else {
            cout << "\n***Continent " + continents[i]->getName() + " is NOT a connected subgraph!***" << endl;
            return false;
        }
    }
    cout << "\n***All continents are connected subgraphs!***" << endl;
    return true;
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
        if (!adjacentTerritories[i]->getIsVisited() && adjacentTerritories[i]->getContinentName() == continent) {
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
	this->owner = new Player();
	this->armyCount = 0;
}
Territory::Territory(string territoryName, string continentName, int armyCount) {
	this->territoryName = territoryName;
	this->continentName = continentName;
	this->armyCount = armyCount;
}
Territory::Territory(string territoryName, string continentName) {
    this->territoryName = territoryName;
    this->continentName = continentName;
}
Territory::~Territory() {
	territoryName.clear();
	continentName.clear();
    delete owner;
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

int Territory::getArmyCount() {
	return this->armyCount;
}
void Territory::setTerritoryName(string territoryName) {
	this->territoryName = territoryName;
}
void Territory::setContinentName(string continentName) {
	this->continentName = continentName;
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

void Territory::removeOwner() {
    owner = nullptr;
}

Player *Territory::getOwner() {
    return owner;
}

void Territory::addOwner(Player* player) {
    owner = player;

}

bool Territory::isAllied(Player* player) {
    if (this->getOwner()->getPlayerName() == player->getPlayerName()) {
        return true;
    } else {
        return false;
    }
}

bool Territory::isEnemy(Player *player) {
    if (this->getOwner()->getPlayerName() != player->getPlayerName()) {
        return true;
    } else {
        return false;
    }
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
