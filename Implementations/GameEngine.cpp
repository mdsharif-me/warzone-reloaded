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
//commands
string states[]= {"start","maploaded","mapvalidated","playersadded","assignreinforcement",
                  "issueorders","executeorders","win"};
//functions
string GameEngine::loadMap(CommandProcessor* c,string currentPhase){
    if (currentPhase == states[0]|| currentPhase == states[1]){
        cout<< "Map loaded"; // success msg
        return states[1]; // new currentPhase return
    }
    else {
        cout<< "Error: This command is not available at this stage."; // error message
        return currentPhase;
    }
}
//functions
string GameEngine::validateMap(CommandProcessor* c, string currentPhase){
    if (currentPhase==states[1]){
        cout<< "map validated";
        return states[2];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}
//functions
string GameEngine::addPlayers(CommandProcessor* c, string currentPhase){
    if (currentPhase == states[2]||currentPhase == states[3]){
        cout<< "players added";
        return states[3];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}
//functions
string GameEngine::win(CommandProcessor* c, string currentPhase){
    if (currentPhase == states[6]){
        cout<< "win";
        return states[7];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

string GameEngine::quit(CommandProcessor* c, string currentPhase){
    if (currentPhase == states[7]){
        cout<< "The end";
        return "exit";
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

string GameEngine::startGame(CommandProcessor* c, string currentPhase){
    if (currentPhase == states[7]){
        cout<< "Play again";
        return states[0];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

string GameEngine::replay(CommandProcessor * c, string currentPhase) {
    return "";
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
        this->excuteOrderPhase();
        round++;
    }
    cout << player_list.front()->getPlayerName() << "wins!!" << endl;
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
void GameEngine::excuteOrderPhase() {
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
    // For loadmap <filename>
    state = "start";
    while (state != "end"){}
    while (state != "maploaded") {
        cout << "Available maps: canada.map, europass.map" << endl;
        cout << "Write the command to loadmap" << endl;
        Command *command = cp->getCommand();
        MapLoader mapLoader(command->getCommand());
        if (mapLoader.extract() && cp->validate(command->getCommand(), state)) {
            this->map = mapLoader.createMap();
            state = "maploaded";
        } else {
            cout << "COMMAND FAIL: LoadMap failed" << endl;
        }
    }
    // For validatemap
    cout << "Enter the next command to validate the map" << endl;
    Command* command = cp->getCommand();
    if (cp->validate(command->getCommand(), state)) {
        if (map->mapValidate()) {
            cout << "\nSuccess: Map \"" << command->getCommand() << "\" has been built.\n\n";
            state = "mapvalidated";
        } else {
            cout << "\nError: Map file \"" << command->getCommand() << "\" is invalid.\n\n";
            exit(0);
        }
    }
    // for addplayer command
    cout << "Add a new Player to the game (type end to continue with the current players" << endl;
    createPlayers();
    state = "playersadded";
    // For gamestart command
    cout << "startup" << endl;
    int number = map->getTerritories().size()/player_list.size();
    int counter = 0;
    int territoryIndex = 0;
    for(int i = 0; i < player_list.size(); i++){
        while(counter < number) {
            player_list[i]->addTerritory(map->getTerritories()[territoryIndex]);
            map->getTerritories()[territoryIndex]->addOwner(player_list[i]);
            territoryIndex++;
            counter++;
        }
        counter = 0;
    }
    while (map->getTerritories().size() % territoryIndex != 0){
        if(counter == player_list.size()){
            counter = 0;
        }
        else{
            player_list[counter]->addTerritory(map->getTerritories()[territoryIndex]);
            territoryIndex++;
            counter++;
        }
    }
    shuffle(player_list.begin(), player_list.end(), std::mt19937(std::random_device()()));

    for(auto player: player_list){
        player->setReinforcementPool(50);
        deck->draw(player);
        deck->draw(player);
    }
    mainGameLoop();
}

Map *GameEngine::getMap() const {
    return map;
}

void GameEngine::setMap(Map *map) {
    GameEngine::map = map;
}

const vector<Player *> &GameEngine::getPlayerList() const {
    return player_list;
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










