//
// Created by tigerrrr on 2/11/2022.
//

#ifndef COMP345_ORDERS_H
#define COMP345_ORDERS_H

#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
#include "Player.h"
#include "LogObserver.h"

using namespace std;

class Territory;
class Player;

/**
 * Class declaration Orders
 */
class Order: virtual public ILoggable, public Subject {
public:
    Order();                                                       // default constructor
    Order(const Order &order);                                     //copy constructor
    ~Order();                                                      //destructor
    Order& operator=(const Order &order);                          //assignment operator
    friend ostream& operator << (ostream &os, const Order &order); //stream insertion operator for Orders
    virtual bool validate();                                       //validate methods to be inherited by the Orders subclasses
    virtual void execute() = 0;                                    //execute methods to be inherited by the Orders subclasses
    virtual void print(std::ostream& os) const;                    // stream assignment operator
    void stringToLog();


protected:
    Player* player{};
    Territory* territory{};
    Territory* startTerritory{};
    Territory* targetTerritory{};
    Player* targetPlayer{};
    vector<Territory*> territories;
    int nrArmies{};
    int nrArmiesToAttack{};
    int nrArmiesToDefend{};

public:
    Territory *getTerritory() const;
    void setTerritory(Territory *territory);
    Territory *getStartTerritory() const;
    void setStartTerritory(Territory *startTerritory);
    Territory *getTargetTerritory() const;
    void setTargetTerritory(Territory *targetTerritory);
    Player *getPlayer() const;
    void setPlayer(Player *player);
    Player *getTargetPlayer() const;
    void setTargetPlayer(Player *targetPlayer);
    const vector<Territory *> &getTerritories() const;
    void setTerritories(const vector<Territory *> &territories);
    int getNrArmies() const;
    void setNrArmies(int nrArmies);
    int getNrArmiesToAttack() const;
    void setNrArmiesToAttack(int nrArmiesToAttack);
    int getNrArmiesToDefend() const;
    void setNrArmiesToDefend(int nrArmiesToDefend);
};

/**
 * Class declaration Orders List
 */

class OrdersList: virtual public ILoggable, public Subject {
private:
    vector<Order*> orders;
public:
    OrdersList() = default;                     //default constructor
    OrdersList(const vector<Order *> &orders);  //constructor
    OrdersList(const OrdersList &orderList);    //copy constructor
    ~OrdersList();                              //destructor
    OrdersList& operator = (OrdersList *orderList); // assignment operator
    friend ostream& operator << (ostream &ostream, const OrdersList &orderList); // stream insertion operator
    void add(Order* order);
    void remove(int index);
    void move(int from, int to);
    vector<Order*> getOrders();
    void removeOrder(Order* order);
    void stringToLog();
};

/**
 * Class declaration Deploy
 */
class Deploy : public Order {
public:
    Deploy() = default;  //default constructor
    Deploy(Player* player, Territory* targetTerritory, int nrArmies);     // constructor
    Deploy(const Deploy &deploy);   //copy constructor
    ~Deploy();   // destructor
    Deploy& operator = (const Deploy &deploy);    // assignment operator
    friend ostream& operator << (ostream &ostream, const Order &order);   //stream insertion operator
    bool validate();
    void execute() ;
    void print(std::ostream& os) const override;
};

/**
 * Class declaration Orders
 */
class Advance : public Order {
public:
    Advance() = default;  // default constructor
    Advance(Player* player, Territory* startTerritory, Territory* targetTerritory, int nrArmies); // constructor
    Advance(const Advance &advance); //copy constructor
    ~Advance() = default;  // destructor
    Advance& operator = (const Advance &advance);  // assignment operator
    //friend ostream& operator << (ostream &ostream, const Advance &advance);  //stream insertion operator
    bool validate();
    void execute();
    void print(std::ostream& os) const override;

};

/**
 * Class declaration  Bomb
 */
class Bomb : public Order {
public:
    Bomb() = default; // default constructor
    Bomb(Player* player, Territory* target);  // constructor
    Bomb(const Bomb &bomb); //copy constructor
    ~Bomb(); // destructor
    Bomb& operator = (const Bomb &bomb); // assignment operator
    //stream insertion operator
    //friend ostream& operator << (ostream &ostream, const Bomb &bomb);
    bool validate();
    void execute();
    void print(std::ostream& os) const override;
};

/**
 * C;ass declaration Blockade
 */
class Blockade : public Order {
public:
    Blockade() = default;  // default constructor
    Blockade(Player* player, Territory* target);    // constructor
    Blockade(const Blockade &blockade); //copy constructor
    ~Blockade();     // destructor
    Blockade& operator = (const Blockade &blockade);   // assignment operator
    //friend ostream& operator << (ostream &ostream, const Blockade &blockade); //stream insertion operator
    bool validate();
    void execute();
    void print(std::ostream& os) const override;
};

/**
 * Class declaration Airlift
 */
class Airlift : public Order {
public:
    Airlift() = default;
    Airlift(Player* player, Territory* startTerritory, Territory *targetTerritory, int nrArmies); // constructor
    Airlift(const Airlift &airlift);   //copy constructor
    ~Airlift();  // destructor
    Airlift& operator = (const Airlift &airlift);// assignment operator
    //friend ostream& operator << (ostream &ostream, const Airlift &airlift); //stream insertion operator
    bool validate();
    void execute();
    void print(std::ostream& os) const override;
};

/**
 * Class declatation Negotiate
 */
class Negotiate : public Order {
public:
    Negotiate() = default; //default constructor
    Negotiate(Player* player, Player* targetPlayer);   // constructor implementation
    Negotiate(const Negotiate &negotiate);    //copy constructor
    ~Negotiate();     // destructor
    Negotiate& operator = (const Negotiate &negotiate);     // assignment operator
    //friend ostream& operator << (ostream &ostream, const Negotiate &negotiate);     //stream insertion operator
    bool validate();
    void execute();
    void print(std::ostream& os) const override;
};

#endif //COMP345_ORDERS_H
