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

void GameEngine::issueOrdersPhase(vector<Player*> players, vector<Territory *>) {
    std::string availableOrders[6] = {"Deploy", "Advance", "Bomb", "Airlift", "Blockade", "Negotiate"};
    string choice;
    string startTerritory;
    string targetTerritory;
    string targetPlayer;
    int numberOfArmies;
    bool isDeploy;
    bool isAdvance;
    bool isBomb;
    bool isAirlift;
    bool isBlockade;
    bool isNegotiate;

    Territory* start = nullptr;
    Territory* target = nullptr;
    Player* targetPlayerObj = nullptr;

    for(Player* player: this->getPlayersList()) {
        cout << player->getPlayerName() << endl;
        cout << "Please choose a start territory from the list:" << endl;
        for(Territory* territory: player->getTerritories()) {
            cout << territory->getTerritoryName() << " , ";
        }

        while (start == nullptr) {
            cout << "Start territory: ";
            cin >> startTerritory;
            for(Territory* territory: player->getTerritories()) {
                if(territory->getTerritoryName() == startTerritory) {
                    start = territory;
                    break;
                }
            }
        }


        while (true) {
            cout << "Please enter the desired order from the list bellow:" << endl;
            for(std::string order: availableOrders) {
                cout << order << ", ";
            }
            cout << endl;
            cout << "Order: ";

            cin >> choice;
            for(std::string order: availableOrders) {
                if (choice == order) {
                    break;
                }
            }
            break;
        }

        isDeploy = choice == availableOrders[0];
        if (isDeploy) {

            while (target == nullptr) {
                cout << "Target territory: " << endl;
                cin >> targetTerritory;
                for(Territory* territory: start->getAdjTerritories()) {
                    if(territory->getTerritoryName() == targetTerritory) {
                        target = territory;
                        break;
                    }
                }
            }

            do {
                cout << "Number of Armies (max " << player->getReinforcementPool() << "): " << endl;
                cin >> numberOfArmies;
                if (numberOfArmies < player->getReinforcementPool()) {
                    player->issueOrder(availableOrders[0], target, numberOfArmies);
                }
            } while (numberOfArmies > player->getReinforcementPool());
        }

        isBomb = choice == availableOrders[2];
        isBlockade = choice == availableOrders[4];
        if (isBomb || isBlockade) {
            do {
                cout << "Target territory: " << endl;
                cin >> targetTerritory;
                for(Territory* territory: start->getAdjTerritories()) {
                    if (territory->getTerritoryName() == targetTerritory) {
                        target = territory;
                        break;
                    }
                }
            } while (target == nullptr);

            if (isBomb) {
                player->issueOrder(availableOrders[2], target);
            } else if (isBlockade) {
                player->issueOrder(availableOrders[4], target);
            }

        }

        isAdvance = choice == availableOrders[1];
        isAirlift = choice == availableOrders[3];
        if (isAdvance || isAirlift) {
            do {
                cout << "Target territory: " << endl;
                cin >> targetTerritory;
                for(Territory* territory: start->getAdjTerritories()) {
                    if (territory->getTerritoryName() == targetTerritory) {
                        target = territory;
                        break;
                    }
                }
            } while (target == nullptr);

            do {
                cout << "Number of Armies (max " << start->getArmyCount()  << "): " << endl;
                cin >> numberOfArmies;
                if (numberOfArmies < player->getReinforcementPool()) {
                    player->issueOrder(availableOrders[0], target, numberOfArmies);
                }
            } while (numberOfArmies > start->getArmyCount() );

            if (isAdvance ) {
                player->issueOrder(availableOrders[1], start, target, numberOfArmies);
            }
            if (isAirlift) {
                player->issueOrder(availableOrders[3], start, target, numberOfArmies);
            }

        }


        isNegotiate = choice == availableOrders[5];
        if(isNegotiate) {
            do {
                cout << "Please choose a target player from the list:" << endl;
                for(Player* player1: this->getPlayersList()) {
                    cout << player1->getPlayerName() << ", ";
                }
                cout << endl;
                cout << "Target Player: " << endl;
                cin >> targetPlayer;

                for(Player* player2: this->getPlayersList()) {
                    if(player2->getPlayerName() == targetPlayer) {
                        targetPlayerObj = player;
                        break;
                    }
                }
            } while (targetPlayerObj == nullptr);

            player->issueOrder(availableOrders[5], targetPlayerObj);
        }
    }
}

void GameEngine::excuteOrderPhase() {
    for(Player* player: this->getPlayersList()) {
        OrdersList* ordersList = player->getOrderList();
        vector<Order* > orders = ordersList->getOrders();
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
    }
    reinforcementPhase()


}
void GameEngine::startupPhase() {

}

void GameEngine::mainGameLoop() {

}









