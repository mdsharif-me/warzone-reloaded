
#include <iostream>
#include "../Headers/Orders.h"
#include "../Headers/PlayerStrategies.h"
#include <vector>

class Player;
class Card;
class LogObserver;
class Map;
class Territory;
class Order;

using namespace std;

int main() {

    cout << "------------------\n";
    cout << "| MapLoader v1.0 |\n";
    cout << "------------------\n";
    cout << "\nThe map loader has started.\n" << endl;

    vector<string> mapFileList = {"../Maps/canada.map"};
    // Check the map files and build maps
    Map *m;
    for (int i = 0; i < mapFileList.size(); i++) {
        MapLoader map(mapFileList[i]);
        if (map.extract()) {
            m = map.createMap();
            if (m->mapValidate()) {
                cout << "\nSuccess: Map \"" << mapFileList[i] << "\" has been built.\n\n";
            }
        } else {
            cout << "\nError: Map file \"" << mapFileList[i] << "\" is invalid.\n\n";
        }
    }

    cout << "\n\n" << endl;

    //new Player
    //target terrritory
    //nraarmies
    vector<Territory *> playerTerritories;
    vector<Territory *> playertoDefend;
    vector<Territory *> playertoAttack;
    vector<Territory *> enemyTerritories;
    vector<Territory *> enemytoDefend;
    vector<Territory *> enemytoAttack;
    int numberOfArmies;


    //set up human player
    auto *player = new Player();
    player->setName("player");
    player->setPlayerStrategy(new Human(player));


    // set up aggressive enemy player
    auto *aggressiveEnemyPlayer = new Player();
    aggressiveEnemyPlayer->setName("aggressive enemy");
    aggressiveEnemyPlayer->setPlayerStrategy(new Aggressive(aggressiveEnemyPlayer));

    // set up benevolent enemy player
    auto *benevolentEnemyPlayer = new Player();
    benevolentEnemyPlayer->setName("benevolent enemy");
    benevolentEnemyPlayer->setPlayerStrategy(new Benevolent(benevolentEnemyPlayer));

    // set up cheater enemy player
    auto *cheaterEnemyPlayer = new Player();
    cheaterEnemyPlayer->setName("cheater enemy");
    cheaterEnemyPlayer->setPlayerStrategy(new Cheater(cheaterEnemyPlayer));

    // set up neutral enemy player
    auto *neutralEnemyPlayer = new Player();
    neutralEnemyPlayer->setName("neutral enemy");
    neutralEnemyPlayer->setPlayerStrategy(new Neutral(neutralEnemyPlayer));


    vector<Player*> playerslist;
    playerslist.push_back(neutralEnemyPlayer);
    playerslist.push_back(aggressiveEnemyPlayer);

    //*********************************************************************
    vector<Territory *> allTerritories = m->getTerritories();
    playerTerritories.reserve(6);
    for (int i = 0; i < 6; i++) {
        playerTerritories.push_back(allTerritories[i]);
    }

    for (int i = 0; i < 6; i++) {
        playerTerritories[i]->addOwner(playerslist[0]);
    }

    //**************************************************************


    enemyTerritories.reserve(6);
    for (int i = 6; i < 12; i++) {
        enemyTerritories.push_back(allTerritories[i]);
    }

    for (int i = 0; i < 6; i++) {
        enemyTerritories[i]->addOwner(playerslist[1]);
    }
    //********************************************************


    Deck* deck = new Deck();
    Card* bomb = new Card("Bomb");
    Card* reinforcement = new Card("Reinforcement");
    Card* blockade = new Card("Blockade");
    Card* airlift = new Card("Airlift");
    Card* diplomacy = new Card("Diplomacy");

    deck->addToDeck(bomb);
    deck->addToDeck(reinforcement);
    deck->addToDeck(blockade);
    deck->addToDeck(airlift);
    deck->addToDeck(diplomacy);


    playerslist[0]->setTerritories(playerTerritories);
    playerslist[0]->setReinforcementPool(10);
    playerslist[0]->getPlayerHand()->addToHand(bomb);


    playerslist[1]->setTerritories(enemyTerritories);
    playerslist[1]->setReinforcementPool(10);
    playerslist[1]->getPlayerHand()->addToHand(airlift);

    int turn = 0;
    for (int i = 0; i < 3; i++) {
        playerslist[0]->issueOrder(deck, playerslist);
        vector <Order* > aggressive_player_orders = playerslist[0]->getOrderList()->getOrders();
        for(Order* order: aggressive_player_orders) { order->execute();}

        playerslist[1]->issueOrder(deck, playerslist);
        vector <Order* > benevolent_player_orders = playerslist[1]->getOrderList()->getOrders();
        for(Order* order: benevolent_player_orders) { order->execute();}
        ++turn;
        cout << endl;
        cout << "end of turn: " << turn << endl;
        cout << endl;


    }




} // end of main