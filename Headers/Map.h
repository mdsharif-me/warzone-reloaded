/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#pragma once
#include <iostream>
#include <vector>
#include "Player.h"
#include <map>
using namespace std;

class Territory {
public:
	Territory();
    ~Territory();
	Territory(string territoryName, string continentName, string playerName, int armyCount);
	Territory(string territoryName, string continentName);
    string getTerritoryName();
	string getContinentName();
	string getPlayerName();
	int getArmyCount();
    bool getIsVisited();
    vector<Territory*> getAdjTerritories();
	void setTerritoryName(string territoryName);
	void setContinentName(string continentName);
	void setPlayerName(string playerName);
	void setArmyCount(int armyCount);
    void setIsVisited(bool visited);

private:
    void addAdjTerritory(Territory* t);
	string territoryName;
    vector<Territory*> adjTerritories;
	string continentName;
	string playerName;
    int armyCount;
    bool isVisited;
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
	Map(int territoriesCount);
	~Map();
    Map(const Map& map);
	list<int> getEdge(int index);
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

private:
	int territoriesCount;
    vector<Territory*> territories;
    vector<Continent*> continents;
	// list<int>* map;
};

class MapLoader {
public:
	MapLoader(string inputFileName);
    MapLoader(const MapLoader &mapLoader); // copy constructor
    ~MapLoader(); // destructor
	bool validateMap();
	void createTerritory();
	void buildMap();
	string extractWord(string inputString, int index);
	int extractInt(string inputString, int index);
	vector<int> extractAllInt(string inputString);
    MapLoader& operator=(const MapLoader &mapLoader);
    friend ostream& operator<<(ostream& out, const MapLoader &mapLoader);

private:
	string mapFileName;
	int fieldCount;
	vector<string> continents;
	vector<string> countries;
	vector<string> borders;
    Map* m;
};
