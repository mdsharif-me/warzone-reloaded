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
    player->setName("Mike");
    enemyPlayer->setName("Enemy");

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


    auto * playerDeploy0 = new Deploy(player, playerTerritories[0], 1);
    auto * playerDeploy1 = new Deploy(player, playerTerritories[1], 1);
    auto * playerDeploy2 = new Deploy(player, playerTerritories[2], 1);
    auto * enemyDeploy0 = new Deploy(enemyPlayer, enemyTerritories[0], 1);
    auto * enemyDeploy1 = new Deploy(enemyPlayer, enemyTerritories[1], 1);
    auto * enemyDeploy2 = new Deploy(enemyPlayer, enemyTerritories[2], 1);

    playerOrdersList->add(playerDeploy0);
    playerOrdersList->add(playerDeploy1);
    playerOrdersList->add(playerDeploy2);
    player->setOrderList(playerOrdersList);

    enemyOrdersList->add(enemyDeploy0);
    enemyOrdersList->add(enemyDeploy1);
    enemyOrdersList->add(enemyDeploy2);
    enemyPlayer->setOrderList(enemyOrdersList);

    //auto* playerAdvance0 = new Advance(player, playerTerritories[0], enemyTerritories[0], 1);

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


    auto* playerAdvance1 = new Advance(player, playerTerritories[2], enemyTerritories[0], 1);

    //playerOrdersList->add(playerAdvance0);
    playerOrdersList->add(playerAdvance1);

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


    /*bool result = deploy->validate();
    cout << result;*/


    /*auto* playerTerritory = new Territory("playerTerritory", "Continent", 10);
    auto* targetTerritory = new Territory("targetTerritory", "Continent", 10);
    vector<Territory *> playerTerritories;
    vector<Territory *> targetTerritories;

    playerTerritories.push_back(playerTerritory);
    targetTerritories.push_back(targetTerritory);

    auto* player = new Player();
    player->setTerritories(playerTerritories);

    auto* targetPlayer = new Player();
    targetPlayer->setTerritories(targetTerritories);

    playerTerritory->addOwner(player);
    targetTerritory->addOwner(targetPlayer);


    //auto* deploy = new Deploy(player, playerTerritory, 5);
    player->issueOrder("Deploy", playerTerritory, 5);*/


    /*auto* advance = new Advance();
    auto * bomb = new Bomb();
    auto * blockade = new Blockade();
    auto* airlift = new Airlift();
    auto * negotiate = new Negotiate();

    cout << "adding orders to orderList...\n";
    auto* ordersList = new OrdersList();
    ordersList->add(deploy);
    ordersList->add(advance);
    ordersList->add(bomb);
    ordersList->add(blockade);
    ordersList->add(airlift);
    ordersList->add(negotiate);

    cout << "displaying orders...\n";
    cout << *ordersList;

    //move first order from index 0 to index 2
    cout << "moving order at index 0 to index 2\n";
    ordersList->move(0, 2);

    cout << "displaying changes\n";
    cout << *ordersList << endl;

    //move first order from index 1 to index 3
    cout << "moving order at index 1 to index 3\n";
    ordersList->move(1, 3);
    cout << "displaying changes\n";
    cout << *ordersList << endl;


    // remove the order at position 0
    cout << "removing order at index 0...\n";
    ordersList->remove(0);
    cout << "displaying changes\n";
    cout << *ordersList;

    // remove the order at position 3
    cout << "removing order at index 3...\n";
    ordersList->remove(3);
    cout << "displaying changes\n";
    cout << *ordersList;

    cout << "validating negotiate order...\n";
    if (negotiate->validate() == true) {}
    cout << "order Negotiate is validated\n\n";

    cout << "executing orders...\n";
    deploy->execute();
    advance->execute();
    bomb->execute();
    blockade->execute();
    airlift->execute();
    negotiate->execute();

    for (auto & someOrder : ordersList->getOrders()) {
        delete someOrder;
    }

    deploy = nullptr;
    advance = nullptr;
    bomb = nullptr;
    airlift = nullptr;
    negotiate = nullptr;
    ordersList = nullptr;*/


    return 0;
}

