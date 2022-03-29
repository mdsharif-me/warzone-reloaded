//
// Created by tigerrrr on 2/11/2022.
//

#include <iostream>
#include "../Headers/Orders.h"
#include <vector>

using namespace std;

int main() {

    cout << "------------------\n";
    cout << "| MapLoader v1.0 |\n";
    cout << "------------------\n";
    cout << "\nThe map loader has started.\n" << endl;

    vector<string> mapFileList = { "../Maps/canada.map"};
    // Check the map files and build maps
    Map *m;
    for (int i = 0; i < mapFileList.size(); i++) {
        MapLoader map(mapFileList[i]);
        if(map.extract()) {
            m = map.createMap();
            if (m->mapValidate()) {
                cout << "\nSuccess: Map \"" << mapFileList[i] << "\" has been built.\n\n";
            }
        }
        else {
            cout << "\nError: Map file \"" << mapFileList[i] << "\" is invalid.\n\n";
        }
    }

    cout << "\n\n" << endl;

    //new Player
    //target terrritory
    //nraarmies
    vector<Territory*> playerTerritories;
    vector<Territory*> playertoDefend;
    vector<Territory*> playertoAttack;
    vector<Territory*> enemyTerritories;
    vector<Territory*> enemytoDefend;
    vector<Territory*> enemytoAttack;
    int numberOfArmies;


    auto* player = new Player();
    auto * enemyPlayer = new Player();
    player->setName("player");
    enemyPlayer->setName("enemy");

    vector<Territory *> allTerritories = m->getTerritories();
    playerTerritories.reserve(3);
    for(int i = 0; i < 3; i++) {
        playerTerritories.push_back(allTerritories[i]);
    }

    enemyTerritories.reserve(3);
    for(int i = 3; i < 6; i++) {
        enemyTerritories.push_back(allTerritories[i]);
    }

    for(int i = 0; i < 3; i++) {
        playerTerritories[i]->addOwner(player);
        enemyTerritories[i]->addOwner(enemyPlayer);
    }

    player->setTerritories(playerTerritories);
    player->setTerritoriesToDefend(playerTerritories);
    enemyPlayer->setTerritories(enemyTerritories);
    enemyPlayer->setTerritoriesToDefend(enemyTerritories);

    vector<Player* > players;
    players.push_back(player);
    players.push_back(enemyPlayer);

    auto* playerOrdersList = new OrdersList();
    auto* enemyOrdersList = new OrdersList();

    auto * playerDeploy0 = new Deploy(player, playerTerritories[0], 2);
    auto * playerDeploy1 = new Deploy(player, playerTerritories[1], 2);
    auto * playerDeploy2 = new Deploy(player, playerTerritories[2], 2);
    auto * enemyDeploy0 = new Deploy(enemyPlayer, enemyTerritories[0], 1);
    auto * enemyDeploy1 = new Deploy(enemyPlayer, enemyTerritories[1], 1);
    auto * enemyDeploy2 = new Deploy(enemyPlayer, enemyTerritories[2], 1);

    playerOrdersList->add(playerDeploy0);
    playerOrdersList->add(playerDeploy1);
    playerOrdersList->add(playerDeploy2);

    enemyOrdersList->add(enemyDeploy0);
    enemyOrdersList->add(enemyDeploy1);
    enemyOrdersList->add(enemyDeploy2);

    player->setOrderList(playerOrdersList);
    enemyPlayer->setOrderList(enemyOrdersList);

    vector<Territory *> adjacentTerritory = playerTerritories[2]->getAdjTerritories();

    cout << "Start Territory " << playerTerritories[2]->getTerritoryName() << endl;
    //cout << "Territory to attack " << enemyTerritories[2]->getTerritoryName() << endl;
    cout << "adjacent territories of " << playerTerritories[2]->getTerritoryName() << " :" << endl;
    for(Territory* territory: adjacentTerritory) {
        cout << territory->getTerritoryName() << endl;
    }
    cout << "---------------------end adjacent " << endl;
    cout << "player territories: " << endl;
    for(Territory* terr: playerTerritories) {
        cout << terr->getTerritoryName() << endl;
    }
    cout << "--------------------------end." << endl;
    cout << "enemy territories: " << endl;
    for(Territory* terr: enemyTerritories) {
        cout << terr->getTerritoryName() << endl;
    }
    cout << "--------------------------end." << endl;


    auto* playerNegotiate = new Negotiate(player, enemyPlayer);
    auto* playerAdvance1 = new Advance(player, playerTerritories[2], enemyTerritories[0], 1);
    auto* playerBomb = new Bomb(player, enemyTerritories[0]);
    auto* playerAirlift = new Airlift(player, playerTerritories[0], playerTerritories[1], 1);
    auto* playerBlockade = new Blockade(player, playerTerritories[1]);

    //playerOrdersList->add(playerNegotiate);
    playerOrdersList->add(playerAdvance1);
    playerOrdersList->add(playerBomb);
    playerOrdersList->add(playerAirlift);
    playerOrdersList->add(playerBlockade);

    for(Player* gamePlayer: players) {
        for (auto order: gamePlayer->getOrderList()->getOrders()) {
            if (dynamic_cast<const Deploy*>(order) != nullptr) {
                order->execute();
                gamePlayer->getOrderList()->removeOrder(order);
            }
        }
    }
    for(Player* gamePlayer: players) {
        for (auto order: gamePlayer->getOrderList()->getOrders()) {
            order->execute();
            gamePlayer->getOrderList()->removeOrder(order);
        }
    }




    return 0;
}

