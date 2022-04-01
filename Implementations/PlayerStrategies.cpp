//
// Created by deepp on 2022-03-31.
//

#include "../Headers/PlayerStrategies.h"
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


void Aggressive::issueOrder() {

}

vector<Territory*> Aggressive::toAttack() {

}

vector<Territory*> Aggressive::toDefend() {

}

void Benevolent::issueOrder() {

}

vector<Territory*> Benevolent::toAttack() {

}

vector<Territory*> Benevolent::toDefend() {

}

void Neutral::issueOrder() {

}

vector<Territory*> Neutral::toAttack() {

}

vector<Territory*> Neutral::toDefect() {

}

void Cheater::issueOrder() {

}

vector<Territory*> Cheater::toAttack() {

}

vector<Territory*> Cheater::toDefect() {

}

