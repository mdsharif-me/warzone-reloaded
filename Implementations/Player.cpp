#include <vector>
#include <string>
#include "../Headers/Player.h"
using namespace std;

Player::Player(string name, vector<string*> ta, vector<string*> td, vector<string*> c)
{
    this->name = name;
    this->territoriesToAttack = ta;
    this->territoriesToDefend = td;
    this->cards = c;
    this->orderList = new OrdersList();
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
    delete orderList;
    orderList = NULL;
    //orderList= new OrdersList();
}


vector<string*> Player::toDefend()
{
    return territoriesToDefend;
}

vector<string*> Player::toAttack()
{
    return territoriesToAttack;
}

void Player::issueOrder(const std::string& orderName) {
    const string& nameOfOrder = orderName;
    if (nameOfOrder == "Deploy") {
        auto* deploy = new Deploy;
        orderList->add(deploy);
    } else if (nameOfOrder == "Advance") {
        auto* advance = new Advance();
        orderList->add(advance);
    } else if (nameOfOrder == "Bomb") {
        Bomb* bomb = new Bomb();
        orderList->add(bomb);
    } else if (nameOfOrder == "Blockade") {
        auto* blockade = new Blockade;
        orderList->add(blockade);
    } else if (nameOfOrder == "Airlift") {
        auto* airlift = new Airlift();
        orderList->add(airlift);

    } else if (nameOfOrder == "Negotiate") {
        auto* negotiate = new Negotiate();
        orderList->add(negotiate);
    } else {
        orderList->add(nullptr);
    }
}

OrdersList* Player::getOrderList() {
    return orderList;
}

Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    this->territoriesToDefend = player.territoriesToDefend;
    this->territoriesToAttack = player.territoriesToAttack;
    this->cards = player.cards;
    this->orderList = player.orderList;
    return *this;
}

string Player::getPlayerName() {
    return name;
}

/*
ostream& operator<<(ostream& os, const Player& player)
{
    // TODO: insert return statement here
}*/

