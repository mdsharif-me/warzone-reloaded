/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#include <string>
#include "Map.h"

int main() {
	std::cout << "------------------\n";
	std::cout << "| MapLoader v1.0 |\n";
	std::cout << "------------------\n";
	std::cout << "\nThe map loader has started.\n" << std::endl;

	std::vector<std::string> mapFileList = { "europass.map", "MyMap.map", "artic.map" };

	// Check the map files and build maps
	for (int i = 0; i < mapFileList.size(); i++) {
		MapLoader map(mapFileList[i]);
		if (map.validateMap()) {
			map.buildMap();
			std::cout << "\nSuccess: Map \"" << mapFileList[i] << "\" has been built.\n\n";
		}
		else {
			std::cout << "\nError: Map file \"" << mapFileList[i] << "\" is invalid.\n\n";
		}
	}

	std::cout << "\n\n" << std::endl;
	return 0;
}
