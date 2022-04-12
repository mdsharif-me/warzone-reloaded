//
// Created by deepp on 2022-03-31.
//

#ifndef WARZONE_RELOADED_PLAYERSTRATEGIES_H
#define WARZONE_RELOADED_PLAYERSTRATEGIES_H
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <vector>
#include <iostream>
using namespace std;

class Player;
class Territory;
class Deck;
/**
 * Implementation of PlayerStrategy class
 */
class PlayerStrategy{
private:
    Player* player;
public:
    PlayerStrategy() = default;
    PlayerStrategy(Player* p);
    PlayerStrategy(const PlayerStrategy& ps);
    PlayerStrategy& operator=(const PlayerStrategy &ps);
    ~PlayerStrategy();
    void setPlayer(Player* p);
    Player * getPlayer() const;
    virtual void issueOrder(Deck* deck, vector<Player*> players_list) = 0;
    virtual void toAttack() = 0;
    virtual void toDefend() = 0;
    bool isStartOfGame();
    vector<Territory*> getTerritoriesToDefend();
    vector<Territory*> getTerritoriesToAttack();

};


/**
 * Implementation of Human class
 */
class Human: public PlayerStrategy{
public:
    Human(Player *player);
    Human(const Human& h);
    ~Human();
    Human& operator=(const Human& h); // assignment operator
    friend ostream& operator<<(ostream& os, const Human& h); // output stream
    void issueOrder(Deck* deck, vector<Player*> players_list);
    void toAttack();
    void toDefend();
};

/**
 * Implementation of Aggressive class
 */
class Aggressive: public PlayerStrategy{
public:
    Aggressive(Player* player);
    Aggressive(const Aggressive& aggressive);
    ~Aggressive();
    Aggressive& operator=(const Aggressive& aggressive);
    friend ostream& operator<< (ostream os, const Aggressive& aggressive);
    void issueOrder(Deck* deck, vector<Player*> players_list) override;
    void toAttack();
    void toDefend();
};


/**
 * Implementation of Benevolent class
 */
class Benevolent: public PlayerStrategy{
public:
    Benevolent(Player* player);
    Benevolent(const Benevolent& benevolent);
    ~Benevolent();
    Benevolent& operator=(const Benevolent& benevolent);
    friend ostream& operator<< (ostream& os, const Benevolent& benevolent);
    void issueOrder(Deck* deck, vector<Player*> players_list) override;
    void toAttack();
    void toDefend();
};

/**
 * Implementation of Neutral class
 */
class Neutral: public PlayerStrategy {
public:
    Neutral(Player* player);
    Neutral(const Neutral& neutral);
    ~Neutral();
    Neutral& operator=(const Neutral& neutral);
    friend ostream& operator<< (ostream& os, const Neutral& neutral);
    void issueOrder(Deck* deck, vector<Player*> players_list) override;
    void toAttack();
    void toDefend();
};

/**
 * Implementation of Cheater class
 */
class Cheater: public PlayerStrategy {
public:
    Cheater(Player* player);
    Cheater(const Cheater& cheater);
    ~Cheater();
    Cheater& operator=(const Cheater& cheater);
    friend ostream& operator<< (ostream& os, const Cheater& cheater);
    void issueOrder(Deck* deck, vector<Player*> players_list) override;
    void toAttack();
    void toDefend();
};
#endif //WARZONE_RELOADED_PLAYERSTRATEGIES_H
