#pragma once
#include <string>
#include <iostream>
using namespace std;

class Player {
private:
	string *territories;
	string *cards;
	string *orderlist;
public:
	Player();
	Player(string name, string t[], string c[], string o[]);
	Player(const Player&);
	int toDefend();
	int toAttack();
	void issueOrder(string);
	string *getOrderList();
};