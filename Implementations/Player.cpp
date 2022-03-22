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
    this->newTerritoryConquered = false;
}
//Shallow copy
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

void Player::issueOrder(Deck* deck, vector<Player*> players_list){ //const string& orderName, Player* targetPlayer) {
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
    cout << "The following are enemy territories, decide priority of the territories to be attacked:" << endl;
    vector<Territory*> enemyTerritories = get_neighbour_territories(this);
    for(int i = 1; i <= enemyTerritories.size(); i++){
        cout << i  << ": "<< this->getTerritories()[i-1]->getTerritoryName() << endl;
    }
    cout <<"Select the order of priority by writing the number (type 0 to stop)" << endl;
    do{
        int numberOrder; cin >> numberOrder;
        if(numberOrder == 0){
            break;
        }
        if (numberOrder > enemyTerritories.size()){
            cout << "Invalid request, try again" << endl;
        }
        else{
            if(!checkIfAlreadyExists(enemyTerritories[numberOrder-1], this->territoriesToAttack)) {
                this->territoriesToAttack.push_back(enemyTerritories[numberOrder-1]);
                cout << "Territory successfully added";
            }
            else{
                cout << "Territory already in the list";
            }
        }
    }
    while(enemyTerritories.size() != this->territoriesToAttack.size());

    // ToDefend()
    cout << "The following are your territories, decide priority of the territories to be defended:" << endl;
    for(int i = 1; i <= this->getTerritories().size(); i++){
        cout << i  << ": "<< this->getTerritories()[i-1]->getTerritoryName() << endl;
    }
    cout <<"Select the order of priority by writing the number (type 0 to stop)" << endl;
    do{
        int numberOrder; cin >> numberOrder;
        if(numberOrder == 0){
            break;
        }
        if (numberOrder > this->getTerritories().size()){
            cout << "Invalid request, try again" << endl;
        }
        else{
            if(!checkIfAlreadyExists(this->getTerritories()[numberOrder-1], this->territoriesToDefend)) {
                this->territoriesToDefend.push_back(this->getTerritories()[numberOrder-1]);
                cout << "Territory successfully added";
            }
            else{
                cout << "Territory already in the list";
            }
        }
    }
    while(this->getTerritories().size() != this->territoriesToDefend.size());

    // Deployment Ordering
    cout << this->getPlayerName() << endl;
    cout << "Territories to Defend in priority. " << endl;
    cout << "Please deploy Army to each territory:" << endl;
    do{
        if(reinforcementPool==0) {
            cout << "No more armies to deploy!";
            break;
        }
        cout << "Be sure to deploy all your armies to be able to issue other orders" << endl;
        for(Territory* territory: this->toDefend()) {
            cout << "Available number of Deployable Army: " << this->reinforcementPool << endl;
            cout << territory->getTerritoryName() << ":";
            int numberOfArmies; cin >> numberOfArmies;
            if (numberOfArmies <= this->reinforcementPool){
                int index = this->playerHand->findCard("reinforcement");
                // playing the card from hand
                if(index != this->playerHand->getHandCards().size())
                    playerHand->getHandCards()[index]->play(this, deck, territory, numberOfArmies);
                    //auto* deploy = new Deploy(this, territory, numberOfArmies);
                    //orderList->add(deploy);
                else
                    cout << "You do not have any reinforcement cards!" << endl;
            }
            else{
                cout << "Sorry you do not have enough Army to Deploy" << endl;
            }
        }
    }
    while (reinforcementPool!=0);
    cout << "Deployment Order is complete, now other orders can be issued" << endl;
    // Other orders
    cout << "Available Orders: Advance, Bomb, Airlift, Blockade, Negotiate" << endl;
    while(true) {
        cout << "Select your next order (type 'end' to end your turn)." << endl;
        string orderString; cin >> orderString;
        if (orderString == "end"){
            cout << "Your turn has now ended." << endl;
            break;
        }
        else if (orderString == "Advance") {
            cout << "Select the source territories number from the following territories" << endl;
            for (int i = 0; i < this->toDefend().size(); i++) {
                cout << i << ": " << this->toDefend()[i] << endl;
            }
            int sourceIndex;
            cin >> sourceIndex;
            vector<Territory *> adjacentTerritories;
            if (sourceIndex < this->toDefend().size() && sourceIndex >= 0) {
                adjacentTerritories = this->toDefend()[sourceIndex]->getAdjTerritories();
                cout << "Select the adjacent territories number to which the army should be moved to." << endl;
                for (int i = 0; i < adjacentTerritories.size(); i++) {
                    cout << i << ": " << adjacentTerritories[i] << endl;
                }
                int targetIndex;
                cin >> targetIndex;
                if (targetIndex < adjacentTerritories.size() && targetIndex >= 0) {
                    cout << "Enter number of armies:" << endl;
                    int armynum;
                    cin >> armynum;
                    if (armynum <= this->toDefend()[sourceIndex]->getArmyCount() && armynum >= 0) {
                       //Advance does not require a card.
                       auto *advance = new Advance(this, this->toDefend()[sourceIndex],
                                                    adjacentTerritories[targetIndex], armynum);
                       orderList->add(advance);
                    }
                    else{
                        cout << "Invalid number of armies" << endl;
                    }
                }
            }
        }
        else if (orderString == "Bomb") {
            cout << "Select the target territories number from the following territories" << endl;
            for (int i = 0; i < this->toAttack().size(); i++) {
                cout << i << ": " << this->toAttack()[i] << endl;
            }
            int indexToBomb;
            cin >> indexToBomb;
            if (indexToBomb < this->toAttack().size() && indexToBomb >= 0) {
                int index = this->playerHand->findCard("bomb");
                // playing the card from hand
                if(index != -1)
                    // the order is issued by the play method in card class
                    playerHand->getHandCards()[index]->play(this, deck, this->toAttack()[indexToBomb]);
                    //Bomb *bomb = new Bomb(this, this->toAttack()[indexToBomb]);
                    //orderList->add(bomb);
                else
                    cout << "You do not have any bomb cards!" << endl;
            } else {
                cout << "Invalid Bomb order" << endl;
            }
        }
        else if(orderString == "Airlift"){
            cout << "Select the source and target territories number from the following territories" << endl;
            for (int i = 0; i < this->toDefend().size(); i++) {
                cout << i << ": " << this->toDefend()[i] << endl;
            }
            int indexToAirliftFrom;
            cout << "From: " << endl;
            cin >> indexToAirliftFrom;
            int indexToAirliftTo;
            cout << "To: " << endl;
            cin >> indexToAirliftTo;
            int armyNo;
            cout << "Number of army " << endl;
            cin >> armyNo;
            if (indexToAirliftFrom < this->toDefend().size() && indexToAirliftFrom >= 0
                && indexToAirliftTo < this->toDefend().size() && indexToAirliftTo >= 0 &&
                armyNo <= this->toDefend()[indexToAirliftFrom]->getArmyCount() && armyNo >= 0) {
                int index = this->playerHand->findCard("airlift");
                // playing the card from hand
                if(index != -1)
                    // the order is issued in the play method on card class
                    playerHand->getHandCards()[index]->play(this, deck, this->toDefend()[indexToAirliftFrom],
                                                            this->toDefend()[indexToAirliftTo], armyNo);
                //auto *airlift = new Airlift(this, this->toDefend()[indexToAirliftFrom],
                //                            this->toDefend()[indexToAirliftTo], armyNo);
                //orderList->add(airlift);
                else
                    cout << "You do not have any Airlift cards!" << endl;
            } else {
                cout << "Invalid Airlift order" << endl;
            }
        }
        else if(orderString == "Blockade") {
            cout << "Select the target territories number from the following territories" << endl;
            for (int i = 0; i < this->toDefend().size(); i++) {
                cout << i << ": " << this->toDefend()[i] << endl;
            }
            int indexToBlockade;
            cin >> indexToBlockade;
            if (indexToBlockade < this->toDefend().size() && indexToBlockade >= 0) {
                int index = this->playerHand->findCard("blockade");
                // playing the card from hand
                if(index != -1)
                    // order is issued in play method of class card
                    playerHand->getHandCards()[index]->play(this, deck, this->toDefend()[indexToBlockade]);
                    //auto *blockade = new Blockade(this, this->toDefend()[indexToBlockade]);
                    //orderList->add(blockade);
                else
                    cout << "You do not have any Blockade cards!" << endl;
            } else {
                cout << "Invalid Blockade order" << endl;
            }
        }
        else if (orderString == "Negotiate") {
            cout << "Select the target Player number from the following Players" << endl;
            for (int i = 0; i < players_list.size(); i++) {
                if(this != players_list[i]) {
                    cout << i << ": " << players_list[i] << endl;
                }
            }
            int indexToPlayer;
            cin >> indexToPlayer;
            if (indexToPlayer < players_list.size() && indexToPlayer >= 0) {
                int index = this->playerHand->findCard("diplomacy");
                if(index != -1) {
                    // order issued in play method of class card
                    playerHand->getHandCards()[index]->play(this, deck, players_list[indexToPlayer]);
                }
                else
                    cout << "You do not have any diplomacy cards!" << endl;
            }
            else {
                cout << "Invalid diplomacy order" << endl;
            }
        }
        else{
            cout << "Invalid order." << endl;
        }
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
    Player::orderList = newOrderList;
}
void Player::setPlayerHand(Hand *newPlayerHand) {
    Player::playerHand = newPlayerHand;
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

bool Player::isNewTerritoryConquered() const {
    return newTerritoryConquered;
}

void Player::setNewTerritoryConquered(bool arg) {
    Player::newTerritoryConquered = arg;
}

void Player::addPlayerToNegotiatePlayersList(Player *player) {
    negotiatePlayersList.push_back(player);
}

void Player::resetNegotiatePlayersList() {
    negotiatePlayersList.clear();
}

void Player::removePlayerFromNegotiatePlayersList(Player *player) {
    std::remove(negotiatePlayersList.begin(), negotiatePlayersList.end(), player);

}

vector<Player *> Player::getNegotiatePlayersList() {
    return negotiatePlayersList;
}

void Player::setTerritoriesToAttack(vector<Territory *> &terrToAttack) {
    Player::territoriesToAttack = terrToAttack;

}

void Player::setTerritoriesToDefend(vector<Territory *> &terrToDefend) {
    territoriesToDefend = terrToDefend;

}

vector<Territory *> Player::getTerritoriesToAttack() {
    return territoriesToAttack;
}

vector<Territory *> Player::getTerritoriesToDefend() {
    return territoriesToDefend;
}

void Player::setTerritories(vector<Territory *> terr) {
    territories = std::move(terr);

}


Player::Player(string &name) {
    this->name = name;
}
bool Player::checkIfAlreadyExists(Territory* territory, vector<Territory *> territories) {
    for(auto t:territories){
        if(t->getTerritoryName()==territory->getTerritoryName()) {
            return true;
        }
    }
    return false;
}
