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

void GameEngine::reinforcementPhase() {
    int numOfArmies = 0;
    vector<Player*>::iterator i;
    for (i = this->player_list.begin(); i != this->player_list.end(); i++) {
        // (# of territories owned divided by 3, rounded down
        numOfArmies = (*i)->getTerritories().size();
        numOfArmies = floor(numOfArmies / 3);

        vector<Continent *> mapContinents = this->map->getContinents();  // get all continents for current map
        vector<Territory *> playerTerritories = (*i)->getTerritories(); // get the user's territories
        vector<string> playerTerritoriesName;                            // get the user's territories name

        // iterate through player's territories and add their name
        for (auto territory: playerTerritories) {
            playerTerritoriesName.push_back(territory->getTerritoryName());
        }

        // sort the vector for later processing
        sort(playerTerritoriesName.begin(), playerTerritoriesName.end());

        // check for each continent if user owns all territories
        for (auto continent: mapContinents) {
            vector<Territory *> mapTerritories = continent->getMembers();
            int n = mapTerritories.size();
            vector<string> continentTerritoriesName;

            // iterate through continent's territories and add their name
            for (auto territory: mapTerritories) {
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
void GameEngine::executeOrderPhase() {
    vector<Player *>::iterator it;
    vector<Order *>::iterator iter;
    OrdersList* playerOrders;
    for(Player* player: player_list) {
        for (Order *order: player->getOrderList()->getOrders()) {
            if (typeid(*order) != typeid(Deploy))
            {
                continue;
            }
            order->execute();
        }
    }
    for(Player* player: player_list) {
        for (Order *order: player->getOrderList()->getOrders()) {
            if (typeid(*order) == typeid(Deploy))
            {
                continue;
            }
            order->execute();
        }
    }
    reinforcementPhase(); //goes back to the reinforcement phase
}
void GameEngine::issueOrdersPhase()
{
    for(Player* p : player_list){
        cout << "Enter your order or type (end) to end your turn" << p->getName() << endl;
        cout << "Available orders: Deploy, Advance, Airlift, Bomb, Blockage, and Negotiate" << endl;
        while (true){
            string order;
            cin >> order;
            if(order == "end"){
                break;
            }
            issueOrder();
        }
    }
}
void GameEngine::startupPhase() {

}

void GameEngine::mainGameLoop() {

}









