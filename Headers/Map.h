/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#pragma once
#include <iostream>
#include <vector>
#include <list>

class MapLoader {
public:
	MapLoader(std::string inputFileName);
	bool validateMap();
	void createTerritory();
	int getNthSpace(std::string inputString, int index);

private:
	std::string mapFileName;
	int fieldCount;
	std::vector<std::string> continents;
	std::vector<std::string> territories;
	std::vector<std::string> edges;
};

class Map {
public:
	Map(int territoriesCount);
	void setTerritory(Territory objTerritory);

private:
	int territoriesCount;
	std::vector<Territory> territoryObjects;
};

class Territory {
public:
	Territory(std::string territoryName, std::string continentName, std::string edges, std::string playerName, int armyCount);
	std::string getTerritoryName();
	std::string getContinentName();
	std::string getEdges();
	std::string getPlayerName();
	int getArmyCount();
	void setTerritoryName(std::string territoryName);
	void setContinentName(std::string continentName);
	void setEdges(std::string edges);
	void setPlayerName(std::string playerName);
	void setArmyCount(int armyCount);

private:
	std::string territoryName;
	std::string continentName;
	std::string edges;
	std::string playerName;
	int armyCount;
};
