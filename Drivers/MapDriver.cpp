/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#include <string>
#include "Map.h"

int main() {
	std::string mapFileName = "europass.map";
	MapLoader map(mapFileName);
	if (map.validateMap()) {
		std::cout << "Creating map \"" << mapFileName << "\"...\n";
		map.createTerritory();
	}
	else {
		std::cout << "Error: Map file \"" << mapFileName << "\" is not a valid map.";
	}
	;
}
