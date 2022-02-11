#include <vector>
#include <string>
#include <iostream>
#include "../headers/Player.h"
using namespace std;

Player::Player()
{
	string name;
    vector<string*> territoriesToAttack;
    vector<string*> territoriesToDefend;
	vector<string*> cards;
	vector<Order*> orderList;
}


Player::Player(string name, vector<string*> ta, vector<string*> td, vector<string*> c, vector<Order*> o)
{
	this->name = name;
	this->territoriesToAttack = ta;
    this->territoriesToDefend = td;
	this->cards = c;
	this->orderList = o;
}

//Shallow copy
Player::Player(const Player& p)
{
	this->name = p.name;
	this->territoriesToDefend = p.territoriesToDefend;
    this->territoriesToAttack = p.territoriesToAttack;
	this->cards = p.cards;
	this->orderList = p.orderList;
}

Player::~Player()
{
    name.clear();
    territoriesToAttack.clear();
    territoriesToDefend.clear();
    cards.clear();
    for (auto order : orderList)
    {
        delete order;
    }
    orderList.clear();
}

vector<string*> Player::toDefend()
{
	return territoriesToDefend;
}

vector<string*> Player::toAttack()
{
	return territoriesToAttack;
}

vector<Order*> Player::getOrderList()
{
	return orderList;
}

void Player::issueOrder(string order)
{
    Order* o = new Order(order);
	orderList.push_back(o);
}

Player& Player::operator=(const Player& player)
{
	// TODO: insert return statement here
}


ostream& operator<<(ostream& os, const Player& player)
{
	// TODO: insert return statement here
}
