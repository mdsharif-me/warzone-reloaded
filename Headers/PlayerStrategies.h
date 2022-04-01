//
// Created by deepp on 2022-03-31.
//

#ifndef WARZONE_RELOADED_PLAYERSTRATEGIES_H
#define WARZONE_RELOADED_PLAYERSTRATEGIES_H
#include "Player.h"
using namespace std;

/**
 * Implementation of PlayerStrategy class
 */
class PlayerStrategy{
private:
    Player* player;
public:
    PlayerStrategy() = default;
    PlayerStrategy(Player* p);
    virtual void issueOrder() = 0;
    virtual void toAttack() = 0;
    virtual void toDefend() = 0;
};


/**
 * Implementation of Human class
 */
class Human: public PlayerStrategy{
public:
    void issueOrder();
    void toAttack();
    void toDefend();
};

/**
 * Implementation of Aggressive class
 */
class Aggressive: public PlayerStrategy{
public:
    void issueOrder();
    void toAttack();
    void toDefend();
};


/**
 * Implementation of Benevolent class
 */
class Benevolent: public PlayerStrategy{
public:
    void issueOrder();
    void toAttack();
    void toDefend();
};

/**
 * Implementation of Neutral class
 */
class Neutral: public PlayerStrategy {
public:
    void issueOrder();

    void toAttack();

    void toDefect();
};

/**
 * Implementation of Cheater class
 */
class Cheater: public PlayerStrategy {
public:
    void issueOrder();

    void toAttack();

    void toDefect();
};
#endif //WARZONE_RELOADED_PLAYERSTRATEGIES_H
