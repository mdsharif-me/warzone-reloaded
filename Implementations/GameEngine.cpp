#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <algorithm>
#include "../Headers/GameEngine.h"
using namespace std;

//class
GameEngine::GameEngine(vector<Player*> players_list, Map* map, Deck* deck){
    this->player_list = players_list;
    this->map = map;
    this->deck = deck;
}
vector<Player *> GameEngine::getPlayersList() {
    return player_list;
}
void GameEngine::mainGameLoop() {
// 1. Round robin fashion in the order setup in startup phase
// 2. This loop shall continue until only one of the players owns all the terrotires in the map.
// 3. Also checks if any player does not control at least one territory
// 4. if so the player is removed from the game.
    int round = 1;
    while (player_list.size() != 1){
        cout << "----------------------------------------------------------------------------" << endl;
        cout << "Round " << round << " has Began" << endl;
        cout << "============================================================================" << endl;
        cout << "Reinforcement Phase beginning..." << endl;
        this->reinforcementPhase();
        cout << "End of Reinforcement Phase..." << endl;
        // To remove player with zero territories.
        for (int i = 0; i < player_list.size(); i++){
            if(player_list[i]->getTerritories().size() == 0){
                cout << "Removing " << player_list[i] << endl;
                remove(player_list.begin(), player_list.end(), player_list[i]);
            }
        }
        cout << "Issuing Order Phase begins...." << endl;
        this->issueOrdersPhase();
        cout << "Executing Order Phase begins...." << endl;
        this->executeOrderPhase();
        round++;
    }
    cout << player_list.front()->getPlayerName() << "wins!!" << endl;
    state = "win";
}
void GameEngine::reinforcementPhase() {
    // 1. Players are given armies that depends on the number of terrtories.
    // 2. Bonus Armies: Only if the player owns the whole continent.
    // 3. The minimal number of reinforcement armies per turn for any player is 3.
    // 4. The reinforcement armies should be placed in player's pool.
    int numOfArmies = 0;
    vector<Player*>::iterator i;
    for (i = this->player_list.begin(); i != this->player_list.end(); i++) {
        // # of territories owned divided by 3, rounded down
        numOfArmies = (*i)->getTerritories().size();
        numOfArmies = floor(numOfArmies / 3);

        vector<Continent *> mapContinents = this->map->getContinents(); // get all continents for current map
        vector<Territory *> playerTerritories = (*i)->getTerritories(); // get the user's territories
        vector<string> playerTerritoriesName;                           // get the user's territories name

        // iterate through player's territories and add their name
        for (auto territory: playerTerritories) {
            playerTerritoriesName.push_back(territory->getTerritoryName());
        }

        // sort the vector for later processing
        sort(playerTerritoriesName.begin(), playerTerritoriesName.end());

        // check for each continent if user owns all territories
        for (auto continent: mapContinents) {
            vector<Territory *> allTerritoriesInContinent = continent->getMembers();
            int n = allTerritoriesInContinent.size();
            vector<string> continentTerritoriesName;

            // iterate through continent's territories and add their name
            for (auto territory: allTerritoriesInContinent) {
                continentTerritoriesName.push_back(territory->getTerritoryName());
            }

            // temp vector for set_difference
            vector<string> v(n);
            vector<string>::iterator iter, st;

            // Sort vector to use set_difference
            sort(continentTerritoriesName.begin(), continentTerritoriesName.end());

            // compare both vector
            iter = set_difference(continentTerritoriesName.begin(),
                                  continentTerritoriesName.end(),
                                  playerTerritoriesName.begin(),
                                  playerTerritoriesName.end(), v.begin());

            for (st = v.begin(); st != iter; ++st) {
            } // add into st until it's not equal to iter

            // if the set difference has no element
            // means the player owns the continent
            if ((st - v.begin()) == 0) {
                numOfArmies += continent->getControlBonus();
            }
        }
        // minimal number of reinforcement armies per turn for any player is 3.
        if (numOfArmies < 3) {
            numOfArmies = 3;
        }
        // add new army number to the user's pool
        int totalArmySize = (*i)->getReinforcementPool() + numOfArmies;
        (*i)->setReinforcementPool(totalArmySize);
    }
}
void GameEngine::issueOrdersPhase() {
// 1. Player issue orders and place them in their order list through a call to issueOrder()
// 2. This method is called in round-robin fashion across all players by the game engine.
    for(auto player : player_list){
        cout << "----------------------------------------------------------------------------" << endl;
        cout << player->getPlayerName() << " TURN!!!!!" << endl;
        cout << "============================================================================" << endl;
        player->issueOrder(deck, player_list);
    }
}
void GameEngine::executeOrderPhase() {
    // 1. Once all the players have signified in the same turn that they are not issuing one more order, the game engine goes to executionPhase()
    // 2. How the orders executed:- New method called nextOrder() should be made.
    // 3. nextOrder() returns the next order in the OrderList.
    // 4. Once received, it calls the method execute() created in Part 4.
    // 5. Record the narrative of its effect stored in the order object.
    // 6. All deployment orders should be done first in round robin.
    // 6. This means you for loop all the deplot order from each player first.
    // 7. Once all the order for all player are executed return back to the reinforcementPhase.
    for(Player* player: this->getPlayersList()) {
        vector<Order* > orders = player->getOrderList()->getOrders();
        for(Order* order: orders) {
            if (dynamic_cast<const Deploy*>(order) != nullptr) {
                order->execute();
                player->getOrderList()->removeOrder(order);
            }
        }
    }

    for(Player* player: this->getPlayersList()) {
        vector<Order* > orders = player->getOrderList()->getOrders();
        for(Order* order: orders) {
                order->execute();
                player->getOrderList()->removeOrder(order);
        }
        if (player->isNewTerritoryConquered()) {
            deck->draw(player);
            player->setNewTerritoryConquered(false);
            cout << player->getPlayerName() << " got a new card" << endl;
        }
    }

    // resetting negotiating players
    for(Player* playerrr: this->getPlayersList()) {
        playerrr->getNegotiatePlayersList().clear();
    }
}
void GameEngine::startupPhase(CommandProcessor* cp) {
    state = "start";
    Command* command;
    do{
        command = cp->getCommand();
        if(command->getCommand() == "quit"){
            if(cp->validate(command->getCommand(),state)) {
                break;
            }
            else{
                cout << "COMMAND FAIL: quit failed" << endl;
            }
        }
        else if(command->getCommand().find("loadmap") != string::npos){
            string path = command->getCommand().substr(8);
            MapLoader mapLoader(path);
            if (mapLoader.extract() && cp->validate(command->getCommand(), state)) {
                this->map = mapLoader.createMap();
                cout << "CHANGE STATE TO: maploaded" << endl;
                state = "maploaded";
            } else {
                cout << "COMMAND FAIL: LoadMap failed" << endl;
            }
        }
        else if(command->getCommand() == "validatemap"){
            if (cp->validate(command->getCommand(), state)) {
                if (map->mapValidate()) {
                    cout << "\nSuccess: Map \"" << command->getCommand() << "\" has been built.\n\n";
                    cout << "CHANGE STATE TO: mapvalidated" << endl;
                    state = "mapvalidated";
                } else {
                    cout << "\nError: Map file \"" << command->getCommand() << "\" is invalid.\n\n";
                    exit(0);
                }
            }
            else{
                cout << "COMMAND FAIL: validatemap failed" << endl;
            }
        }
        else if(command->getCommand().find("addplayer") != string::npos){
            if (cp->validate(command->getCommand(), state)) {
                string playerName = command->getCommand().substr(10);
                player_list.push_back(new Player(playerName));
                cout << "PLAYER ADDED: " << playerName << endl;
                if(player_list.size() >= 2) {
                    cout << "CHANGE STATE TO: playersadded" << endl;
                    state = "playersadded";
                }
            }
            else{
                cout << "COMMAND FAIL: addplayer failed" << endl;
            }
        }
        else if(command->getCommand() == "replay"){
            if(cp->validate(command->getCommand(),state)) {
                //TODO: clear method
            }
            else{
                cout << "COMMAND FAIL: replay failed" << endl;
            }
        }
        else if(command->getCommand() == "gamestart") {
            if (cp->validate(command->getCommand(), state)) {
                cout << "GAME STARTING!!" << endl;
                for(int i = 0; i < player_list.size();i++){
                    player_list[i]->getPlayerHand()->addToHand(new Card("deploy"));
                    player_list[i]->getPlayerHand()->addToHand(new Card("reinforcement"));
                    player_list[i]->getPlayerHand()->addToHand(new Card("blockade"));
                    player_list[i]->getPlayerHand()->addToHand(new Card("airlift"));
                    player_list[i]->getPlayerHand()->addToHand(new Card("diplomacy"));
                }
                int number = map->getTerritories().size() / player_list.size();
                int counter = 0;
                int territoryIndex = 0;
                for (int i = 0; i < player_list.size(); i++) {
                    while (counter < number) {
                        player_list[i]->addTerritory(map->getTerritories()[territoryIndex]);
                        map->getTerritories()[territoryIndex]->addOwner(player_list[i]);
                        territoryIndex++;
                        counter++;
                    }
                    counter = 0;
                }
                while (map->getTerritories().size() % territoryIndex != 0) {
                    if (counter == player_list.size()) {
                        counter = 0;
                    } else {
                        player_list[counter]->addTerritory(map->getTerritories()[territoryIndex]);
                        territoryIndex++;
                        counter++;
                    }
                }
                shuffle(player_list.begin(), player_list.end(), std::mt19937(std::random_device()()));
                for (auto player: player_list) {
                    player->setReinforcementPool(50);
                    deck->draw(player);
                    deck->draw(player);
                }
                mainGameLoop();
            }
            else{
                cout << "COMMAND FAIL: gamestart failed" << endl;
            }
        }
        else{
            cout << "COMMAND FAIL: incorrect command" << endl;
        }
    }
    while(command->getCommand() != "quit");
}

Map *GameEngine::getMap() const {
    return map;
}

void GameEngine::setMap(Map *map) {
    GameEngine::map = map;
}
void GameEngine::setPlayerList(const vector<Player *> &playerList) {
    player_list = playerList;
}
Deck *GameEngine::getDeck() const {
    return deck;
}
void GameEngine::setDeck(Deck *deck) {
    GameEngine::deck = deck;
}
GameEngine::~GameEngine() {
    delete deck;
    delete map;
    for(auto player: player_list){
        delete player;
    }
    player_list.clear();
}










