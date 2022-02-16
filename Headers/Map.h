/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#pragma once
#include <iostream>
#include <vector>
#include <list>

class Territory {
public:
	Territory();
	~Territory();
	Territory(std::string territoryName, std::string continentName, std::string playerName, int armyCount);
	std::string getTerritoryName();
	std::string getContinentName();
	std::string getPlayerName();
	int getArmyCount();
	void setTerritoryName(std::string territoryName);
	void setContinentName(std::string continentName);
	void setPlayerName(std::string playerName);
	void setArmyCount(int armyCount);

private:
	std::string territoryName;
	std::string continentName;
	std::string playerName;
	int armyCount;
};

class Map {
public:
	Map(int territoriesCount);
	~Map();
	std::list<int> getEdge(int index);
	void setEdge(int edgeA, int edgeB);

private:
	int territoriesCount;
	std::list<int>* map;
};

class MapLoader {
public:
	MapLoader(std::string inputFileName);
	bool validateMap();
	void createTerritory();
	void buildMap();
	std::string extractWord(std::string inputString, int index);
	int extractInt(std::string inputString, int index);
	std::vector<int> extractAllInt(std::string inputString);

private:
	std::string mapFileName;
	int fieldCount;
	std::vector<std::string> continents;
	std::vector<std::string> countries;
	std::vector<std::string> borders;
	std::vector<Territory> territories;
};
