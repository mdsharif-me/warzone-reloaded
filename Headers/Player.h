//
// Created by Created by deepp on 2022-02-10.
//

#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#include <iostream>
#include <vector>
#include <iostream>
#include "Orders.h"
using namespace std;

class Order;
class OrdersList;

class Player {
private:
    string name;
    vector<string*> territoriesToAttack;
    vector<string*> territoriesToDefend;
    vector<string*> cards;
    OrdersList* orderList;
public:
    Player() = default;
    Player(string name, vector<string*> ta, vector<string*> td, vector<string*> c);
    Player(const Player&);
    ~Player();
    vector<string *> toDefend();
    vector<string *> toAttack();
    void issueOrder(const std::string&);
    OrdersList* getOrderList();
    void printOrders();

    //assignment operator
    Player& operator=(const Player& player);

    //stream insertion operator for Player
    friend ostream& operator << (ostream& os, const Player& player);
};


#endif //COMP345_PLAYER_H
