//
// Created by tigerrrr on 2/11/2022.
//

#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Orders.h"
#include <vector>
#include <random>
#include <functional>

using namespace std;

class Territory;
class Player;

/**
 * Order class Implementation
 *
 */

// constructor implementation
Order::Order() = default;

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
bool Deploy::validate() {

    for (Territory* territory: player->getTerritories()) {
        if (territory->getOwner()->getPlayerName() == targetTerritory->getOwner()->getPlayerName()) {
            return true;
        }
    }
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
        cout << nrArmies << " troops have been deployed to " << targetTerritory->getTerritoryName() << endl;
    }
}


/**
 * Class to handle advance order
 */


// constructor implementation
Advance::Advance(Player *player, Territory *startTerritory, Territory *targetTerritory, int nrArmies) {
    this->player = player;
    this->startTerritory = startTerritory;
    this->targetTerritory = targetTerritory;
    this->nrArmies = nrArmies;
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
        return false;
    }

    // check if territory is adjacent
    for(Territory* territory: startTerritory->getAdjTerritories()) {
        if (territory->getTerritoryName() == targetTerritory->getTerritoryName()) {
            return true;
        }
    }

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


            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(1,100);
            auto dice = std::bind ( distribution, generator );

            int roll = dice();
            while (attackerArmies != 0 && defenderArmies != 0) {
                if (roll > 40) {
                    defenderArmies -= 1;
                }
                if (roll > 30) {
                    attackerArmies -= 1;
                }
                roll = dice();
            }
            targetTerritory->setArmyCount(defenderArmies);

            if (defenderArmies == 0) {
                targetTerritory->setArmyCount(attackerArmies);
                targetTerritory->getOwner()->setName(this->player->getPlayerName());
                player->addTerritory(targetTerritory);
            }


            /*for (int i = 0; i < this->nrArmies; i++) {
                int roll = dice();

                attackerKilledDefending = (roll < 60);
                defenderKilledAttacker = (roll  < 70);

                if (defenderKilledAttacker) {
                    if(startTerritory->getArmyCount() != 0) {
                        startTerritory->setArmyCount(startTerritory->getArmyCount() - 1);
                    }
                } else if (attackerKilledDefending) {
                    if(targetTerritory->getArmyCount() != 0) {
                        targetTerritory->setArmyCount(targetTerritory->getArmyCount() - 1);
                    }
                }
                if (targetTerritory->getArmyCount() == 0) {
                    targetTerritory->setPlayerName(startTerritory->getPlayerName());
                    targetTerritory->setArmyCount(startTerritory->getArmyCount());
                    startTerritory->setArmyCount(0);
                }
            }*/
        }

        cout << "Advance order executed" << endl;
        if (targetTerritory->getOwner()->getPlayerName() == this->player->getPlayerName()) {
            cout << "The territory" << targetTerritory->getTerritoryName() << " has been conquered" << endl;
        }
        //TO DO
        //receive a Card if at least one territory conquered.
    } else {
        cout << "Advance Order is invalid...ignoring...";
    }
}

/**
 * Method to print the results
 * @param os
 */
void Advance::print(ostream &os) const {
    cout << "Advance " << this->nrArmies << " to " << this->targetTerritory << endl;
}



/**
 * Class to implement Bomb
 */

// constructor implementation
Bomb::Bomb(Player* player, Territory* targetTerritory){
    this->player = player;
    this->targetTerritory=targetTerritory;
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
            return false;
        }

    }
    // check if territory is adjacent
    for(Territory* territory: startTerritory->getAdjTerritories()) {
        if (territory->getTerritoryName() == targetTerritory->getTerritoryName()) {
            return true;
        }
    }
}

// method to execute an order
void Bomb  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        targetTerritory->setArmyCount(targetTerritory->getArmyCount() / 2);
        cout << "Bomb order executed" << endl;
    }
}

/**
 * Method to print the results
 * @param os
 */
void Bomb::print(ostream &os) const {
    cout << "Bomb " << this->targetTerritory << endl;
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
            return true;
        }
    }
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
        cout << targetTerritory->getTerritoryName() << " has no owner now." << endl;
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
            return true;
        }
    }
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
    for(Territory* territory: player->getTerritories()) {
        if (territory->getOwner()->getPlayerName() == this->targetTerritory->getOwner()->getPlayerName()) {
            return false;
        }
    }
    return true;
}

// method to execute an order
void Negotiate  :: execute() {
    bool orderValid = this->validate();
    if (orderValid) {
        // invalidate attack orders
        cout << "Negotiate order executed" << endl;
    }
}

