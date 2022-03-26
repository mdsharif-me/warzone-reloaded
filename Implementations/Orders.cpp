

#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Orders.h"
#include <random>

using namespace std;

class Territory;
class Player;

/**
 * Order class Implementation
 *
 */

// constructor implementation
  

// copy constructor implementation
Order::Order(const Order &order) {
    this->territory = order.territory;
    this->startTerritory = order.startTerritory;
    this->targetTerritory = order.targetTerritory;
    this->player = order.player;
    this->targetPlayer = order.targetPlayer;
    this->nrArmies = order.nrArmies;
    this->nrArmiesToAttack = order.nrArmiesToAttack;
    this->nrArmiesToDefend = order.nrArmiesToDefend;
}

//destructor implementation
Order::~Order() = default;

// assignment operator
Order &Order::operator=(const Order &order) {
    if (this != &order) {
        return *this;
    }
    return *this;
}

//stream insertion operator implementation
ostream &operator<<(ostream &os, const Order &order) {
    order.print(os);
    return os;
}

bool Order::validate() {
    return true;

}

void::Order::execute() {
}

void Order::print(ostream &os) const {
    cout << "Order" << endl;
}

Territory *Order::getTerritory() const {
    return territory;
}

void Order::setTerritory(Territory *territory) {
    Order::territory = territory;
}

Territory *Order::getStartTerritory() const {
    return startTerritory;
}

void Order::setStartTerritory(Territory *startTerritory) {
    Order::startTerritory = startTerritory;
}

Territory *Order::getTargetTerritory() const {
    return targetTerritory;
}

void Order::setTargetTerritory(Territory *targetTerritory) {
    Order::targetTerritory = targetTerritory;
}

Player *Order::getPlayer() const {
    return player;
}

void Order::setPlayer(Player *player) {
    Order::player = player;
}

Player *Order::getTargetPlayer() const {
    return targetPlayer;
}

void Order::setTargetPlayer(Player *targetPlayer) {
    Order::targetPlayer = targetPlayer;
}

const vector<Territory *> &Order::getTerritories() const {
    return territories;
}

void Order::setTerritories(const vector<Territory *> &territories) {
    Order::territories = territories;
}

int Order::getNrArmies() const {
    return nrArmies;
}

void Order::setNrArmies(int nrArmies) {
    Order::nrArmies = nrArmies;
}

int Order::getNrArmiesToAttack() const {
    return nrArmiesToAttack;
}

void Order::setNrArmiesToAttack(int nrArmiesToAttack) {
    Order::nrArmiesToAttack = nrArmiesToAttack;
}

int Order::getNrArmiesToDefend() const {
    return nrArmiesToDefend;
}

void Order::setNrArmiesToDefend(int nrArmiesToDefend) {
    Order::nrArmiesToDefend = nrArmiesToDefend;
}

void Order::stringToLog() {
    cout << "inside string to log of order class" << endl;

}

/*void Order::stringToLog() {

}*/

Order::Order() = default;



/**
 * Orders List Class Implementation
 *
 */

// constructor implementation
OrdersList::OrdersList(const vector<Order *> &ordersList) : orders(ordersList) {
    this -> orders = ordersList;
}

// copy constructor implementation
OrdersList::OrdersList(const OrdersList &orderList) {
    this ->orders = orderList.orders;
}

//destructor implementation
OrdersList::~OrdersList() {
    this ->orders.clear();
}

// assignment operator
OrdersList& OrdersList::operator=(OrdersList *otherList) {

    this -> orders = otherList->orders;
    return *this;
}


/**
 * stream insertion operator implementation
 * @param ostream
 * @param ordersList
 * @return
 */
ostream &operator<<(ostream &ostream, const OrdersList &ordersList) {
    ostream << "[\n";
    for (int i = 0; i < ordersList.orders.size(); ++i) {
        cout << *(ordersList.orders[i]);
    }
    ostream <<"]\n";
    return ostream;
}


/**
 * adds an order to the list
 * @param order
 */
void OrdersList::add(Order* order) {
    orders.push_back(order);
    std::string message = "";
    if (dynamic_cast<const Deploy*>(order) != nullptr) {
        message = "Order issued: Deploy";
    } else if (dynamic_cast<const Advance*>(order) != nullptr) {
        message = "Order issued: Advance";

    } else if (dynamic_cast<const Bomb*>(order) != nullptr) {
        message = "Order issued: Bomb";

    } else if (dynamic_cast<const Airlift*>(order) != nullptr) {
        message = "Order issued: Airlift";

    } else if (dynamic_cast<const Blockade*>(order) != nullptr) {
        message = "Order issued: Blockade";

    } else if (dynamic_cast<const Negotiate*>(order) != nullptr) {
        message = "Order issued: Negotiate";

    }
    Subject subject;
    LogObserver* logObserver = new LogObserver(subject);
    subject.setMessage(message);
    subject.Notify(this);
    delete logObserver;
    logObserver = nullptr;
    
    //super.update(order);
}

/**
 * removes an order from the list
 * @param index
 */
void OrdersList::remove(int index) {
    orders.erase(orders.begin() + index);
}

/**
 * Method to move an order inside the list.
 * @param from
 * @param to
 */
void OrdersList::move(int from, int to) {
    if (from < 0 || from > orders.size() || to < 0 || to > orders.size()) {
        throw std::invalid_argument("Provided indexes are out of vector range.");
    }
    iter_swap(orders.begin() + from, orders.begin() + to);
}

vector<Order *> OrdersList::getOrders() {
    return this->orders;
}

void OrdersList::removeOrder(Order* order) {
    for (int i = 0; i < this->getOrders().size(); ++i) {
        if (this->getOrders()[i] == order) {
            this->remove(i);
        }
    }

}

void OrdersList::stringToLog() {}




/**
* Deploy class implementation
*/

// constructor implementation
Deploy::Deploy(Player *player, Territory *targetTerritory, int nrArmies) {
    this -> player = player;
    this -> targetTerritory = targetTerritory;
    this -> nrArmies = nrArmies;
}

// copy constructor implementation
Deploy::Deploy(const Deploy& deploy)  : Order(deploy) {
    this -> player = deploy.player;
    this -> targetTerritory = deploy.targetTerritory;
    this -> nrArmies = deploy.nrArmies;
}

// destructor implementation
Deploy::~Deploy() = default;

// assignment operator implementation
Deploy& Deploy::operator=(const Deploy &deploy) {
    this -> player = deploy.player;
    this -> targetTerritory = deploy.targetTerritory;
    this -> nrArmies = deploy.nrArmies;

    return *this;
}


void Deploy::print(std::ostream &os) const {
    cout << "Deploy " << this->nrArmies << " to " << this->targetTerritory << endl;
}

/**
 * Method to validate a deploy order
 * @return
 */
bool Deploy::validate(){

    for (Territory* territory: player->getTerritories()) {
        if (territory->getOwner()->getPlayerName() == targetTerritory->getOwner()->getPlayerName()) {
            cout << "Deploy order is valid." << endl;
            return true;
        }
    }
    cout << "Deploy order is invalid." << endl;
    return false;
}

/**
/**
 * Method to execute a deploy operation
 */
void Deploy::execute() {
    bool validOrder = this->validate();
    if(validOrder) {
        player->setReinforcementPool(player->getReinforcementPool() - nrArmies);
        targetTerritory->setArmyCount(targetTerritory->getArmyCount() + this->nrArmies);
        cout << player->getPlayerName() << " has executed Deploy order." << endl;
        cout << nrArmies << " troops have been deployed to " << targetTerritory->getTerritoryName() << endl;
        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Deploy");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;
    } else {
        cout << "Cannot execute invalid Deploy order." << endl;
    }
}

void stringToLog() {}




/**
 * Class to handle
 * order
 */


// constructor implementation
Advance::Advance(Player *player, Territory *startTerritory, Territory *targetTerritory, int nrArmies) {
    this->player = player;
    this->startTerritory = startTerritory;
    this->targetTerritory = targetTerritory;
    this->nrArmies = nrArmies;
    this->targetPlayer = targetTerritory->getOwner();
}

// copy constructor implementation
Advance::Advance(const Advance &advance) : Order(advance){
    this->player = advance.player;
    this->startTerritory = advance.startTerritory;
    this->targetTerritory = advance.targetTerritory;
    this->nrArmies = advance.nrArmies;

}

// assignment operator implementation
Advance& Advance::operator=(const Advance &advance){
    this->player = advance.player;
    this->startTerritory = advance.startTerritory;
    this->targetTerritory = advance.targetTerritory;
    this->nrArmies = advance.nrArmies;

    return *this;
}


// method to validate an order
bool Advance::validate() {
    if (startTerritory->getOwner()->getPlayerName() != player->getPlayerName()) {
        cout << "Advance order is invalid." << endl;
        return false;
    }

    if (!player->getNegotiatePlayersList().empty()) {
        for(Player* searchedPlayer: player->getNegotiatePlayersList()) {
            if (searchedPlayer->getPlayerName() == this->targetPlayer->getPlayerName()) {
                cout << searchedPlayer->getPlayerName() << " is currently negotiating with " << player->getPlayerName() << endl;
                return false;
            }
        }
    }


    // check if territory is adjacent
    for(Territory* territory: startTerritory->getAdjTerritories()) {
        if (territory->getTerritoryName() == targetTerritory->getTerritoryName()) {
            cout << "Advance order is valid." << endl;
            return true;
        }
    }

    cout << "Advance order is invalid." << endl;
    return false;
}

// method to execute an order
void Advance  :: execute() {
    int attackerArmies = this->nrArmies;
    int defenderArmies = targetTerritory->getArmyCount();

    bool orderIsValid = this->validate();
    if (orderIsValid) {
        if (startTerritory->getOwner()->getPlayerName() == player->getPlayerName() &&
            targetTerritory->getOwner()->getPlayerName() == player->getPlayerName()) {
            // decrease #armies in the source territory
            startTerritory->setArmyCount(startTerritory->getArmyCount() - this->nrArmies);
            // increase #armies in the target territories
            targetTerritory->setArmyCount(targetTerritory->getArmyCount() + this->nrArmies);

        } else if (targetTerritory->getOwner()->getPlayerName() != player->getPlayerName()) {
            bool attackerKilledDefending = false;
            bool defenderKilledAttacker = false;

            startTerritory->setArmyCount(startTerritory->getArmyCount() - attackerArmies);

            random_device rd;
            mt19937 gen(rd());
            uniform_real_distribution<> dis(0, 1);
            float randomNumberAttack = dis(gen);
            while (attackerArmies != 0 && defenderArmies != 0) {
                // 60% killing 1 defending army
                if (randomNumberAttack > 0.4){
                    defenderArmies -= 1;
                }
                // 70% killing 1 attacking army
                if (randomNumberAttack > 0.3){
                    attackerArmies -= 1;
                }
                randomNumberAttack = dis(gen);
            }
            targetTerritory->setArmyCount(defenderArmies);

            if (defenderArmies == 0) {
                player->addTerritory(targetTerritory);
                targetTerritory->setArmyCount(attackerArmies);
                // set the flag that a new territory is conquered
                player->setNewTerritoryConquered(true);
            }


        }

        cout << "Advance order executed" << endl;
        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Advance");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;
        if (targetTerritory->getOwner()->getPlayerName() == this->player->getPlayerName()) {
            cout << "The territory" << targetTerritory->getTerritoryName() << " has been conquered" << endl;
        }
    } else {
        cout << "Cannot execute invalid Advance order." << endl;

    }
}


/**
 * Method to print the results
 * @param os
 */
void Advance::print(ostream &os) const {
    cout << "Advance " << this->nrArmies << " to " << this->targetTerritory->getTerritoryName() << endl;
}



/**
 * Class to implement Bomb
 */

// constructor implementation
Bomb::Bomb(Player* player, Territory* targetTerritory){
    this->player = player;
    this->targetTerritory=targetTerritory;
    this->targetPlayer = targetTerritory->getOwner();
}

//copy constructor implementation
Bomb::Bomb(const Bomb &bomb) : Order(bomb){
    this->player=bomb.player;
    this->targetTerritory=bomb.targetTerritory;
}

//assignment operator implementation
Bomb& Bomb::operator=(const Bomb &bomb){
    this->player=bomb.player;
    this->targetTerritory = bomb.targetTerritory;

    return *this;
}

// method to validate an order
bool Bomb  :: validate() {
    for(Territory* territory: player->getTerritories()) {
        if(targetTerritory->getOwner()->getPlayerName() == territory->getOwner()->getPlayerName()) {
            cout << "Bomb order is invalid." << endl;
            return false;
        }

        if (!player->getNegotiatePlayersList().empty()) {
            for(Player* searchedPlayer: player->getNegotiatePlayersList()) {
                if (searchedPlayer->getPlayerName() == this->targetPlayer->getPlayerName()) {
                    cout << searchedPlayer->getPlayerName() << " is currently negotiating with " << player->getPlayerName() << endl;
                    return false;
                }
            }
        }


    }
    // check if territory is adjacent
    for(Territory* territory: startTerritory->getAdjTerritories()) {
        if (territory->getTerritoryName() == targetTerritory->getTerritoryName()) {
            cout << "Bomb order is valid." << endl;
            return true;
        }
    }

    cout << "Bomb order is invalid" << endl;
    return false;
}

// method to execute an order
void Bomb  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        targetTerritory->setArmyCount(targetTerritory->getArmyCount() / 2);
        cout << "Bomb order executed" << endl;
        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Bomb");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;
    } else {
        cout << "Cannot execute invalid Bomb order." << endl;
    }
}

/**
 * Method to print the results
 * @param os
 */
void Bomb::print(ostream &os) const {
    cout << "Bomb " << this->targetTerritory->getTerritoryName() << endl;
}


/**
 * Class to hande Blockade
 */

//constructor implementation
Blockade::Blockade(Player* player, Territory* targetTerritory){
    this->player = player;
    this->targetTerritory = targetTerritory;
}

//copy constructor implementation
Blockade::Blockade(const Blockade &blockade) : Order(blockade){
    this->player = blockade.player;
    this->targetTerritory = blockade.targetTerritory;
}

//assignment operator implementation
Blockade& Blockade::operator=(const Blockade &blockade){
    this->player = blockade.player;
    this->targetTerritory=blockade.targetTerritory;

    return *this;
}

//stream insertion operator for Blockade implementation
void Blockade::print(ostream &os) const {
    cout << "Blockade " << this->targetTerritory << endl;
}

// method to valida an order
bool Blockade  :: validate() {
    for(Territory* territory: player->getTerritories()) {
        if (targetTerritory->getOwner()->getPlayerName() == territory->getOwner()->getPlayerName()) {
            cout << "Blockade order is valid." << endl;
            return true;
        }
    }
    cout << "Blockade order is invalid. The target territory does not belong to the player that issued the order" << endl;
    return false;
}

// method to execute an order
void Blockade  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        //double the number of armies
        targetTerritory->setArmyCount(targetTerritory->getArmyCount() * 2);
        targetTerritory->getOwner()->removeTerritory(targetTerritory);
        targetTerritory->removeOwner();

        cout << "Blockade order executed" << endl;
        cout << targetTerritory->getTerritoryName() << " has no owner now and has " << targetTerritory->getArmyCount() << " armies." << endl;
        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Blockade");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;
    } else {
        cout << "Cannot execute invalid Blockade  order." << endl;
    }
}



/**
 * Class to handle Airlift
 */

// constructor implementation
Airlift::Airlift(Player *player, Territory *startTerritory, Territory *targetTerritory, int nrArmies) {
    this->player = player;
    this->startTerritory = startTerritory;
    this->targetTerritory = targetTerritory;
    this->nrArmies = nrArmies;

}

// copy constructor implementation
Airlift::Airlift(const Airlift &airlift) : Order(airlift){
    this->player= airlift.player;
    this->startTerritory = airlift.startTerritory;
    this->targetTerritory = airlift.targetTerritory;
    this->nrArmies = airlift.nrArmies;
}

// assignment operator implementation
Airlift& Airlift::operator=(const Airlift &airlift){
    this->player = airlift.player;
    this->startTerritory = airlift.startTerritory;
    this->targetTerritory = airlift.targetTerritory;
    this->nrArmies = airlift.nrArmies;

    return *this;
}

void Airlift::print(ostream &os) const {
    cout << "Airlift " << this->nrArmies <<" armies" << " from " << this->startTerritory << " to " << this->targetTerritory << endl;
}


// method to valida an order
bool Airlift  :: validate() {
    for(Territory* territory: player->getTerritories()) {
        if (territory->getOwner()->getPlayerName() == startTerritory->getOwner()->getPlayerName() &&
            territory->getOwner()->getPlayerName() == targetTerritory->getOwner()->getPlayerName()) {
            cout << "Airlift order is valid." << endl;
            return true;
        }
    }
    cout << "Airlift order is invalid. Either the start or the target territory does not belong to the player that issued the order." << endl;
    return false;
}

// method to execute an order
void Airlift  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        //increase number of armies in the target territories
        targetTerritory->setArmyCount(targetTerritory->getArmyCount() + this->nrArmies);
        //decrease number of armies in the source territory
        startTerritory->setArmyCount(startTerritory->getArmyCount() - this->nrArmies);
        cout << "Airlift order executed" << endl;
        cout << "Airlifted " << this->nrArmies <<" armies" << " from " << this->startTerritory->getTerritoryName() << " to " << this->targetTerritory->getTerritoryName() << endl;
        cout << "The target territory has now: " << targetTerritory->getArmyCount() << " armies and start territory has now " << startTerritory->getArmyCount() << " armies."  << endl;

        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Airlift");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;
    } else {
        cout << "Cannot execute invalid Airlift order." << endl;
    }
}



/**
 * Class to handle Negotiate
 */

// constructor implementation
Negotiate::Negotiate(Player* player, Player* targetPlayer){
    this->player = player;
    this->targetPlayer = targetPlayer;
}

// copy constructor implementation
Negotiate::Negotiate(const Negotiate &negotiate) : Order(negotiate){
    this->player = negotiate.player;
    this->targetPlayer = negotiate.targetPlayer;
}

// assignment operator implementation
Negotiate& Negotiate::operator=(const Negotiate &negotiate){
    this->player = negotiate.player;
    this->targetPlayer = negotiate.targetPlayer;
    return *this;
}

// stream assignment operator implementation
void Negotiate::print(ostream &os) const {
    cout << "Negotiate with " << this->targetPlayer << endl;
}

// method to validate an order
bool Negotiate  :: validate() {
    if (this->player->getPlayerName() == this->targetPlayer->getPlayerName()) {
        cout << "Order is invalid. Attempting to negotiate with itself.";
        return false;
    }
    cout << "Negotiate order is valid." << endl;
    return true;
}

// method to execute an order
void Negotiate  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        player->addPlayerToNegotiatePlayersList(targetPlayer);
        targetPlayer->addPlayerToNegotiatePlayersList(player);
        cout << "Negotiate order executed." << endl;
        cout << targetPlayer->getPlayerName() << " will not attack " << player->getPlayerName() << " territories during this turn." << endl;
        cout << player->getPlayerName() << " will not attack " << targetPlayer->getPlayerName() << " territories this turn" << endl;

        Subject subject;
        LogObserver* logObserver = new LogObserver(subject);
        subject.setMessage("Order Executed: Negotiate");
        subject.Notify(this);
        delete logObserver;
        logObserver = nullptr;

    } else {
        cout << "Cannot execute invalid Negotiate order." << endl;
    }
}
