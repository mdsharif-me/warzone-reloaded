//
// Created by Created by deepp on 2022-02-10.
//

#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#include <iostream>
#include <vector>
#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
using namespace std;

class Order;
class OrdersList;
class Hand;
class Territory;

class Player {
private:
    string name;                                //Attribute to the player's name
    vector<Territory*> territoriesToAttack;
    vector<Territory*> territoriesToDefend;
    vector<Territory *> territories;
    OrdersList* orderList;
    Hand* playerHand;
    int reinforcementPool = 0;
    bool newTerritoryConquered;
public:
    Player() = default;                         //Default Constructor
    Player(string& name);
    Player(string& name, vector<Territory*> ta, vector<Territory*> td, Hand* c);
    Player(const Player&);                      //Copy Constructor
    ~Player();                                  //Destructor
    string getPlayerName();                     //Accessor
    vector<Territory *> toDefend();             //Accessor
    vector<Territory *> toAttack();             //Accessor
    vector<Territory *> getTerritories();       //Accessor
    void issueOrder(Deck* deck, vector<Player*> players_list);
    OrdersList* getOrderList();                 //Accessor
    Hand* getPlayerHand();                      //Accessor
    int getReinforcementPool();                 //Accessor
    const string& getName() const;              //Accessor
    void setOrderList(OrdersList *orderList);   //Mutator
    void setPlayerHand(Hand *playerHand);       //Mutator
    void setReinforcementPool(int nrArmies);    //Mutator
    void setName(const string& newName);        //Mutator
    Player& operator=(const Player& player);    //assignment operator
    friend ostream& operator << (ostream& os, const Player& player); //stream insertion operator for Player
    vector<Territory*> get_friendly_neighbour(Player* p);
    static vector<Territory*> get_neighbour_territories(Player* p);
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    bool checkIfAlreadyExists(Territory*, vector<Territory*>);
    bool isNewTerritoryConquered() const;
    void setNewTerritoryConquered(bool newTerritoryConquered);
};


#endif //COMP345_PLAYER_H
