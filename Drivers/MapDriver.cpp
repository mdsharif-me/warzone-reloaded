/*
Author: Mohammad Shariful Islam
Date: 12 Feb, 2022
*/

#include <string>
#include "../Headers/Map.h"
using namespace std;

int main() {
	cout << "------------------\n";
	cout << "| MapLoader v1.0 |\n";
	cout << "------------------\n";
	cout << "\nThe map loader has started.\n" << endl;

	vector<string> mapFileList = { "europass.map", "MyMap.map", "artic.map" };

	// Check the map files and build maps
	for (int i = 0; i < mapFileList.size(); i++) {
		MapLoader map(mapFileList[i]);
		if (map.validateMap()) {
			map.buildMap();
			cout << "\nSuccess: Map \"" << mapFileList[i] << "\" has been built.\n\n";
		}
		else {
			cout << "\nError: Map file \"" << mapFileList[i] << "\" is invalid.\n\n";
		}
	}

	cout << "\n\n" << endl;
	return 0;
}
