#include <utility>
#include <vector>
#include <string>
#include "../Headers/Player.h"
using namespace std;

Player::Player() {
    this->playerHand = new Hand();
    this->orderList = new OrdersList();
}
Player::Player(string& name, vector<Territory*> ta, vector<Territory*> td, Hand * c)
{
    this->name = name;
    this->territoriesToAttack = std::move(ta);
    this->territoriesToDefend = std::move(td);
    this->playerHand = c;
    this->orderList = new OrdersList();
    this->newTerritoryConquered = false;
}
Player::Player(string &name) {
    this->name = name;
    this->playerHand = new Hand();
    this->orderList = new OrdersList();
    this->newTerritoryConquered = false;
    this->playerWasAttacked = false;
}
Player::Player(const Player& p)
{
    this->name = p.name;
    this->territoriesToDefend = p.territoriesToDefend;
    this->territoriesToAttack = p.territoriesToAttack;
    this->playerHand = p.playerHand;
    this->orderList = p.orderList;
    this->newTerritoryConquered = false;
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
    delete playerHand;
    orderList = nullptr;
    playerHand = nullptr;
}
vector<Territory *> Player::getTerritories() {
    return territories;
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
int Player::getReinforcementPool() {
    return reinforcementPool;
}
const string& Player::getName() const {
    return name;
}
bool Player::isNewTerritoryConquered() const {
    return newTerritoryConquered;
}
vector<Player *> Player::getNegotiatePlayersList() {
    return negotiatePlayersList;
}
vector<Territory *> Player::getTerritoriesToAttack() {
    return territoriesToAttack;
}
vector<Territory *> Player::getTerritoriesToDefend() {
    return territoriesToDefend;
}
PlayerStrategy *Player::getPlayerStrategy() const {
    return playerStrategy;
}

void Player::setOrderList(OrdersList *newOrderList) {
    Player::orderList = newOrderList;
}
void Player::setPlayerHand(Hand *newPlayerHand) {
    Player::playerHand = newPlayerHand;
}
void Player::setReinforcementPool(int nrArmies) {
    reinforcementPool = nrArmies;
}
void Player::setName(const string &newName) {
    this->name = newName;
}
void Player::addTerritory(Territory *territory) {
    // if someone owns the territory, remove it from them
    if (territory->getOwner() != nullptr){
        territory->getOwner()->removeTerritory(territory);
        territory->removeOwner();
    }
    // add this to this player
    territory->addOwner(this);
    territories.push_back(territory);

}
void Player::removeTerritory(Territory *territory) {
    // find the territory and remove it
    for(int i = 0; i < territories.size(); i++){
        if (territories[i] == territory){
            territories.erase(territories.begin()+i);
        }
    }
    //std::remove(territories.begin(), territories.end(), territory);

}
void Player::setNewTerritoryConquered(bool arg) {
    Player::newTerritoryConquered = arg;
}
void Player::addPlayerToNegotiatePlayersList(Player *player) {
    negotiatePlayersList.push_back(player);
}
void Player::removePlayerFromNegotiatePlayersList(Player *player) {
    std::remove(negotiatePlayersList.begin(), negotiatePlayersList.end(), player);

}
void Player::setTerritoriesToAttack(vector<Territory *> &terrToAttack) {
    Player::territoriesToAttack = terrToAttack;
}
void Player::setTerritoriesToDefend(vector<Territory *> &terrToDefend) {
    territoriesToDefend = terrToDefend;
}
void Player::setTerritories(vector<Territory *> terr) {
    territories = std::move(terr);

}
void Player::setPlayerStrategy(PlayerStrategy* playerStrategy) {
    Player::playerStrategy = playerStrategy;
}
void Player::setPlayerWasAttacked(bool wasAttacked) {
    this->playerWasAttacked = wasAttacked;
}

void Player::toDefend()
{
    playerStrategy->toDefend();
}
void Player::toAttack(){
    playerStrategy->toAttack();
}
void Player::issueOrder(Deck* deck, vector<Player*> players_list){
    // 1. The decision-marking code must be implemented within this method.
    // 1. Finding neighbouring territories that can be attacked. (toAttack() method)
    // 2. Finding which from your own territories that can be defended. (toDefend() method)
    // 3. First Deploy order should be called on territories from toDefend().
    // 4. Once all the armies of a player are used, he can now call other orders.
    // 5. Advance Order: Player can move armies to one of his own territories (using toDefend() to make the decision)
    // 5. Advance Order: Player can move armies to one of the NEIGHBOURING enemy territory to attack them (using toAttack() to make the decision)
    // 6. Cards in Hand: Issue the corresponding order.
    // 7. Validating whether they are executed, is not part of this function.
    // ToAttack()
    // ToDefend()
    // Deployment Ordering
    // playerStrategy->issueOrder(deck, players_list);
    toDefend();
    toAttack();
    playerStrategy->issueOrder(deck, players_list);
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

// returns neighbours not controlled by player
vector<Territory*> Player::get_neighbour_territories(Player* p) {
    vector<Territory*> controlled = p->getTerritories();
    vector<Territory*> neighbouring_terrritories;

    // Get neighbour territories ( territories to attack )
    for (Territory* c : controlled) {
        vector<Territory*> adjTerritories = c->getAdjTerritories();

        // for territories to attack find if it's controlled by you
        for (Territory* neighbour : adjTerritories) {
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
void Player::resetNegotiatePlayersList() {
    negotiatePlayersList.clear();
}
bool Player::checkIfAlreadyExists(Territory* territory, vector<Territory *> territories) {
    for(auto t:territories){
        if(t->getTerritoryName()==territory->getTerritoryName()) {
            return true;
        }
    }
    return false;
}
bool Player::isPlayerWasAttacked() {
    return this->playerWasAttacked;
}
