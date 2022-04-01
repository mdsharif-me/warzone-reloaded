//
// Created by deepp on 2022-03-31.
//

#include "../Headers/PlayerStrategies.h"
#include <iostream>
using namespace std;


PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
}
PlayerStrategy::PlayerStrategy(const PlayerStrategy &copy){
    this->player = copy.player;
}
void PlayerStrategy::setPlayer(Player *p) {
    this->player = p;
}
Player *PlayerStrategy::getPlayer() {
    return this->player;
}
PlayerStrategy::~PlayerStrategy() {
    delete this->player;
}
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy &ps) {
    this->player = ps.player;
    return *this;
}

bool PlayerStrategy::isStartOfGame() {
    for(auto territory: this->player->getTerritories()){
        if(territory->getArmyCount() == 0){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

ostream &operator<<(ostream &os, PlayerStrategy &ps)
{
    os << "player strategy: " << ps.getPlayer()->getPlayerName() << endl;
    return os;
}

/**
 * Implementation of Human class
 */
Human::Human(Player *player) : PlayerStrategy(player) {}
Human::Human(const Human &h) : PlayerStrategy(h) {}
Human::~Human() {}
void Human::issueOrder() {

}
vector<Territory*> Human::toAttack() {

}
vector<Territory*> Human::toDefend() {

}

/**
 * Implementation of Human class
 */
void Aggressive::issueOrder() {

}

vector<Territory*> Aggressive::toAttack() {

}

vector<Territory*> Aggressive::toDefend() {

}

Aggressive::Aggressive(Player *player) : PlayerStrategy(player) {

}

void Benevolent::issueOrder() {
    toAttack();
    toDefend();
}

vector<Territory*> Benevolent::toAttack() {
    this->getPlayer()->getTerritoriesToAttack().clear();
}

vector<Territory*> Benevolent::toDefend() {
    // ToDefend has order  of territories from weakest to strongest
    if(isStartOfGame()){
        int number = this->getPlayer()->getReinforcementPool() / this->getPlayer()->getTerritories().size();
        int counter = 0;
        //int territoryIndex = 0;
        for (int i = 0; i < this->getPlayer()->getTerritories().size(); i++) {
            this->getPlayer()->getTerritories()[i]->setArmyCount(number);
            this->getPlayer()->setReinforcementPool(this->getPlayer()->getReinforcementPool() - number);
        }
        int remainder = this->getPlayer()->getReinforcementPool() % this->getPlayer()->getTerritories().size();
        if (remainder != 0) {
            int currentArmyCount = this->getPlayer()->getTerritories()[0]->getArmyCount();
            this->getPlayer()->getTerritories()[0]->setArmyCount(currentArmyCount + remainder);
        }
    }
    else{

    }

}

Benevolent::Benevolent(Player *player) : PlayerStrategy(player) {

}

void Neutral::issueOrder() {
    //
    toAttack();
    toDefend();
    cout << "PLAYER STRATEGY: Neutral -> Can not issue orders" << endl;
    if(this->getPlayer()->isPlayerWasAttacked()){
        this->getPlayer()->setPlayerStrategy(new Aggressive(this->getPlayer()));
    }
}

vector<Territory*> Neutral::toAttack() {
    this->getPlayer()->getTerritoriesToAttack().clear();
}

vector<Territory*> Neutral::toDefend() {
    this->getPlayer()->getTerritoriesToDefend().clear();
}

Neutral::Neutral(Player *player) : PlayerStrategy(player) {}

void Cheater::issueOrder() {

}

vector<Territory*> Cheater::toAttack() {

}

vector<Territory*> Cheater::toDefect() {

}

Cheater::Cheater(Player *player) : PlayerStrategy(player) {

}

