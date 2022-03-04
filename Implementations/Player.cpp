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

void Player::issueOrder(const string& orderName, Territory* targetTerritory, int nrOfArmies) {
    const string& nameOfOrder = orderName;
    if (nameOfOrder == "Deploy") {
        auto* deploy = new Deploy(this, targetTerritory, nrOfArmies);
        orderList->add(deploy);
    }
}


void Player::issueOrder(const string& orderName, Territory* targetTerritory) {
    const string& nameOfOrder = orderName;
    if (nameOfOrder == "Bomb") {
        Bomb* bomb = new Bomb(this, targetTerritory);
        orderList->add(bomb);
    } else if (nameOfOrder == "Blockade") {
        auto* blockade = new Blockade(this, targetTerritory);
        orderList->add(blockade);
    }
}


void Player::issueOrder(const string& orderName,Territory* startTerritory, Territory* targetTerritory,int nrOfArmies) {
    const string &nameOfOrder = orderName;
    if (nameOfOrder == "Advance") {
        auto *advance = new Advance(this, startTerritory, targetTerritory, nrOfArmies);
        orderList->add(advance);
    } else if (nameOfOrder == "Airlift") {
        auto *airlift = new Airlift(this, startTerritory, targetTerritory, nrOfArmies);
        orderList->add(airlift);
    }
}



void Player::issueOrder(const string& orderName, Player* targetPlayer) {
    const string &nameOfOrder = orderName;
    if (nameOfOrder == "Negotiate") {
        auto *negotiate = new Negotiate(this, targetPlayer);
        orderList->add(negotiate);
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
void Player::setReinforcementPool(int nrArmies) {
    reinforcementPool += nrArmies;
}
void Player::setName(const string &newName) {
    this->name = newName;

}
const string& Player::getName() const {
    return name;
}

vector<Territory*> Player::get_neighbour_territories(Player* p) {
    vector<Territory*> controlled = p->getTerritories();
    vector<Territory*> neighbouring_terrritories;

    // Get neighbour territories ( territories to attack )
    for (Territory* c : controlled) {
        vector<Territory*> attacking = c->getAdjTerritories();

        // for territories to attack find if it's controlled by you
        for (Territory* neighbour : attacking) {
            auto result = find(controlled.begin(), controlled.end(), neighbour);
            auto exists = find(neighbouring_terrritories.begin(), neighbouring_terrritories.end(), neighbour);
            // vector doesn't contain element and doesn't already exist in vector
            if (result == controlled.end() && exists == neighbouring_terrritories.end())
            {
                neighbouring_terrritories.push_back(neighbour); // push to neighbouring territories vector
            }
            else
            {
                continue;
            }
        }
    }
    return neighbouring_terrritories;
}

// returns neighbours controlled by player
vector<Territory*> Player::get_friendly_neighbour(Player* p) {
    vector<Territory*> controlled = p->getTerritories();
    vector<Territory*> friendly_neighbours;

    // Get neighbour territories ( territories to attack )
    for (Territory* c : controlled) {
        vector<Territory*> all_neighbours = c->getAdjTerritories();

        // for territories to attack find if it's controlled by you
        for (Territory* neighbour : all_neighbours) {
            auto result = find(controlled.begin(), controlled.end(), neighbour);
            if (result != controlled.end()) // vector contains the element
            {
                friendly_neighbours.push_back(neighbour); // push to neighbouring territories vector
            }
            else
            {
                continue;
            }
        }
    }
    return friendly_neighbours;
}

void Player::addTerritory(Territory *territory) {
    territories.push_back(territory);

}

void Player::removeTerritory(Territory *territory) {
    std::remove(territories.begin(), territories.end(), territory);

}
