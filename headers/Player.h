//
// Created by tigerrrr on 1/24/2022.
//

#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H
#include <iostream>
#include <vector>
#include <iostream>
#include "OrderForPlayer.h"
using namespace std;

class Player {
private:
    string name;
    vector<string*> territoriesToAttack;
    vector<string*> territoriesToDefend;
    vector<string*> cards;
    vector<Order*> orderList;
public:
    Player();
    Player(string name, vector<string*> ta, vector<string*> td, vector<string*> c, vector<Order*>);
    Player(const Player&);
    ~Player();
    vector<string *> toDefend();
    vector<string *> toAttack();
    void issueOrder(string);
    vector<Order*> getOrderList();
    void printOrder();

    //assignment operator
    Player& operator=(const Player& player);

    //stream insertion operator for Player
    friend ostream& operator << (ostream& os, const Player& player);
};

#endif //COMP345_PLAYER_H
