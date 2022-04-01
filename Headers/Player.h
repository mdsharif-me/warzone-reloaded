//
// Created by Created by deepp on 2022-02-10.
//

#ifndef COMP345_PLAYER_H
#define COMP345_PLAYER_H

#include <vector>
#include <iostream>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "PlayerStrategies.h"
using namespace std;

class Order;
class OrdersList;
class Hand;
class Territory;
class Deck;
class PlayerStrategy;

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
    bool playerWasAttacked;
    vector<Player* > negotiatePlayersList;
    PlayerStrategy* playerStrategy;

public:
    Player();                                    //Default Constructor
    Player(string& name);
    Player(string& name, vector<Territory*> ta, vector<Territory*> td, Hand* c);
    Player(const Player&);                      //Copy Constructor
    ~Player();                                  //Destructor
    string getPlayerName();                     //Accessor
    void setPlayerWasAttacked(bool wasAttacked);
    bool isPlayerWasAttacked();
    PlayerStrategy *getPlayerStrategy() const;
    void setPlayerStrategy(PlayerStrategy *playerStrategy);
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
    void addPlayerToNegotiatePlayersList(Player* player);
    void resetNegotiatePlayersList();
    void removePlayerFromNegotiatePlayersList(Player* player);
    vector<Player *> getNegotiatePlayersList();
    vector<Territory *> getTerritoriesToAttack();
    void setTerritoriesToAttack(vector<Territory *> &territoriesToAttack);
    vector<Territory *> getTerritoriesToDefend();
    void setTerritoriesToDefend(vector<Territory *> &territoriesToDefend);
    void setTerritories(vector<Territory *> territories);
};


#endif //COMP345_PLAYER_H
