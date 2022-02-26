#include <utility>
#include <vector>
#include <string>
#include "../Headers/Player.h"
using namespace std;

Player::Player(string& name, vector<Territory*> ta, vector<Territory*> td, Hand * c)
{
    this->name = name;
    this->territoriesToAttack = std::move(ta);
    this->territoriesToDefend = std::move(td);
    this->playerHand = c;
    this->orderList = new OrdersList();
}

//Shallow copy
Player::Player(const Player& p)
{
    this->name = p.name;
    this->territoriesToDefend = p.territoriesToDefend;
    this->territoriesToAttack = p.territoriesToAttack;
    this->playerHand = p.playerHand;
    this->orderList = p.orderList;
}

Player::~Player()
{
    name.clear();
    for (auto t : territoriesToAttack)
    {
        delete t;
    }
    territoriesToAttack.clear();
    for (auto t : territoriesToDefend)
    {
        delete t;
    }
    territoriesToDefend.clear();
    delete orderList;
    orderList = nullptr;
}

vector<Territory*> Player::toDefend()
{
    return territoriesToDefend;
}

vector<Territory*> Player::toAttack()
{
    return territoriesToAttack;
}

vector<Territory *> Player::getTerritories() {
    return territories;
}

void Player::issueOrder(const string& orderName) {
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

Hand* Player::getPlayerHand() {
    return playerHand;
}

string Player::getPlayerName() {
    return name;
}

void Player::setOrderList(OrdersList *newOrderList) {
    Player::orderList = orderList;
}

void Player::setPlayerHand(Hand *newPlayerHand) {
    Player::playerHand = playerHand;
}


Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    this->territoriesToDefend = player.territoriesToDefend;
    this->territoriesToAttack = player.territoriesToAttack;
    this->playerHand = player.playerHand;
    this->orderList = player.orderList;
    return *this;
}

ostream& operator<<(ostream& os, const Player& player)
{
    os << "Player Name: " << player.name << endl;
    return os;
}


int Player::getReinforcementPool() {
    return reinforcementPool;
}

void Player::setReinforcementPoll(int nrArmies) {
    reinforcementPool += nrArmies;
}

void Player::setName(const string &newName) {
    this->name = newName;

}

const string& Player::getName() const {
    return name;
}

