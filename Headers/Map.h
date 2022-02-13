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
	void createMap();

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
	std::vector<std::string> getTerritoryNames();
	void setTerritoryNames(std::vector<std::string>);
	void addTerritoryEdge(int TerritoryA, int TerritoryB);

private:
	int territoriesCount;
	std::list<int>* territories;
	std::vector<std::string> territoryNames;
	std::vector<std::string> continents;
	std::string players;
};
