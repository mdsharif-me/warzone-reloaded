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
/*class Territory{
private:
    string TerritoryName;
public:
    Territory() = default;
    Territory(string name);
    string getTerritoryName();
};*/
class Player {
private:
    string name;                                //Attribute to the player's name
    vector<Territory*> territoriesToAttack;
    vector<Territory*> territoriesToDefend;
    vector<string*> cards;                      //player owns a hand of Cards
    OrdersList* orderList;
public:
    Player() = default;                         //Default Constructor
    Player(string& name, vector<Territory*> ta, vector<Territory*> td, vector<string*> c);
    Player(const Player&);                      //Copy Constructor
    ~Player();                                  //Destructor
    string getPlayerName();                     //Accessor
    vector<Territory *> toDefend();             //Accessor
    vector<Territory *> toAttack();             //Accessor
    void issueOrder(const string&);
    OrdersList* getOrderList();                 //Accessor
    Player& operator=(const Player& player);    //assignment operator
    friend ostream& operator << (ostream& os, const Player& player); //stream insertion operator for Player
};


#endif //COMP345_PLAYER_H
