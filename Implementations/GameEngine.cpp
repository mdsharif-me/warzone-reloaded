#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "../Headers/GameEngine.h"
using namespace std;

//class
GameEngine::GameEngine(){
    this->state=state[0];
}

vector<Player *> GameEngine::getPlayersList() {
    return player_list;
}

//commands
string states[]= {"start","maploaded","mapvalidated","playersadded","assignreinforcement",
                  "issueorders","executeorders","win"};
//functions
string GameEngine::loadMap(string currentPhase){
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
string GameEngine::validateMap(string currentPhase){
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
string GameEngine::addPlayer(string currentPhase){
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
string GameEngine::assignCountries(string currentPhase){
    if (currentPhase == states[3]||currentPhase == states[6]){
        cout<< "assign reinforcement";
        return states[4];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}
//functions
string GameEngine::issueOrder(string currentPhase){
    if (currentPhase == states[4]|| currentPhase == states[5]){
        cout<< "issue orders";
        return states[5];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}
//functions
string GameEngine::endIssueOrders(string currentPhase){
    if (currentPhase == states[5]||currentPhase == states[6]){
        cout<< "execute orders";
        return states[6];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::execOrder(string currentPhase){
    if (currentPhase == states[6] ){
        cout<< "execute orders";
        return states[6];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::endExecOrders(string currentPhase){
    if (currentPhase == states[6] ){
        cout<< "execute orders";
        return states[4];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::win(string currentPhase){
    if (currentPhase == states[6]){
        cout<< "win";
        return states[7];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::end(string currentPhase){
    if (currentPhase == states[7]){
        cout<< "The end";
        return "exit";
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::play(string currentPhase){
    if (currentPhase == states[7]){
        cout<< "Play again";
        return states[0];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

void GameEngine::createPlayers() {
    cout << "Enter number of Player:" << endl;
    int numOfPlayers; cin >> numOfPlayers;
    for(int i = 0; i < numOfPlayers; i++){
        cout << "Player " << i << "name: " << endl;
        string name; cin >> name;
        this->player_list.push_back(new Player(name));
        //TODO: Part2
    }
}


void GameEngine::mainGameLoop() {
// 1. Round robin fashiion in the order setup in startup phase
// 2. This loop shall continue until only one of the players owns all the terrotires in the map.
// 3. Also checks if any player does not control at least one territory
// 4. if so the player is removed from the game.
    int round = 0;
    while (player_list.size() != 1){
        this->reinforcementPhase();
        // To remove player with zero territories.
        for (int i = 0; i < player_list.size(); i++){
            if(player_list[i]->getTerritories().size() == 0){
                remove(player_list.begin(), player_list.end(), player_list[i]);
            }
        }
        this->issueOrdersPhase();
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
            if (typeid(order) == typeid(Deploy)) {
                order->execute();
            }
        }
        for(Order* order: orders) {
            if (typeid(order) != typeid(Deploy)) {
                order->execute();
            }
        }
        orders.clear();
    }
}

void GameEngine::startupPhase() {

}










