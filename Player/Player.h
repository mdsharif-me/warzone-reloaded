#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Player {
private:
	string name;
	vector<string*> territories;
	vector<string*> cards;
	vector<Order*> orderList;
public:
	Player();
	Player(string name, vector<string*> t, vector<string*> h, vector<Order*>);
	Player(const Player&);
	~Player();
	int toDefend();
	int toAttack();
	void issueOrder(string);
	vector<Order*> getOrderList();

	//assignment operator
	Player& operator=(const Player& player);

	//stream insertion operator for Player
	friend ostream& operator << (ostream& os, const Player& player);
};