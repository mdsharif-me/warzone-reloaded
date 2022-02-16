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
class Hand;

class Player {
private:
    string name;                                //Attribute to the player's name
    vector<Territory*> territoriesToAttack;
    vector<Territory*> territoriesToDefend;
    OrdersList* orderList;
    Hand* playerHand;
public:
    Player() = default;                         //Default Constructor
    Player(string& name, vector<Territory*> ta, vector<Territory*> td, Hand* c);
    Player(const Player&);                      //Copy Constructor
    ~Player();                                  //Destructor
    string getPlayerName();                     //Accessor
    vector<Territory *> toDefend();             //Accessor
    vector<Territory *> toAttack();             //Accessor
    void issueOrder(const string&);
    OrdersList* getOrderList();                 //Accessor
    Hand* getPlayerHand();

    void setOrderList(OrdersList *orderList);   //Mutator
    void setPlayerHand(Hand *playerHand);       //Mutator

    Player& operator=(const Player& player);    //assignment operator
    friend ostream& operator << (ostream& os, const Player& player); //stream insertion operator for Player
};


#endif //COMP345_PLAYER_H
