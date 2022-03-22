/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
class Player;

class Territory {
public:
	Territory();
    ~Territory();
	Territory(string territoryName, string continentName, int armyCount);
	Territory(string territoryName, string continentName);
    string getTerritoryName();
	string getContinentName();
	int getArmyCount();
    bool getIsVisited();
    vector<Territory*> getAdjTerritories();
	void setTerritoryName(string territoryName);
	void setContinentName(string continentName);
	void setArmyCount(int armyCount);
    void setIsVisited(bool visited);
    void addAdjTerritory(Territory* t);
    void addOwner(Player* player);
    void removeOwner();
    Player* getOwner();
    bool isAllied(Player* player);
    bool isEnemy(Player* player);

private:
	string territoryName;
    vector<Territory*> adjTerritories;
	string continentName;
    int armyCount;
    bool isVisited;
    Player* owner;
};

class Continent {
public:
    Continent();
    Continent(string name, int armies);
    Continent(string name, int armies, vector<Territory*> members);
    Continent(const Continent &continent);
    Continent& operator=(const Continent &continent);
    friend ostream& operator<<(ostream& out, Continent continent);
    void addTerritory(Territory* territory);
    string getName();
    vector<Territory*> getMembers();
    int getControlBonus();
private:
    string name;
    int controlBonus;
    vector<Territory*> members;
};

class Map {
public:
	~Map();
    Map(const Map& map);
    Map() = default;
    //list<int> getEdge(int index);
	void addEdge(Territory* edgeA, Territory* edgeB); //addBorder
    vector<Territory*> getTerritories();
    void addTerritory(Territory* t);
    vector<Continent*> getContinents();
    void addContinent(Continent* c);
    void addTerritoryToContinent(Territory* territory, int continentId);
    bool mapValidate();
    bool checkMapConnectedGraph();
    bool checkContinentGraphs();
    int visitNeighbours(Territory* territory, int visited);
    int visitContinentNeighbours(Territory* territory, string continent, int visited);
    void resetVisitedTerritories();
    bool checkIfValidContinent();
    int getContinentIndex(Continent* continent);
    void addEdgeIndex(int t1, int t2);

private:
	int territoriesCount;
    vector<Territory*> territories;
    vector<Continent*> continents;
};

class MapLoader {
public:
	MapLoader(string inputFileName);
    MapLoader(const MapLoader &mapLoader); // copy constructor
    ~MapLoader(); // destructor
    Map* createMap();
	bool extract();
    void buildMap();
    MapLoader& operator=(const MapLoader &mapLoader);
    friend ostream& operator<<(ostream& out, const MapLoader &mapLoader);

private:
	string mapFileName;
	int fieldCount;
	vector<string> continents;
	vector<string> countries;
	vector<string> borders;
    vector<string> simpleTokenizer(string s);
    bool isNumber(const string&);
};
