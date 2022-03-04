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

void GameEngine::reinforcementPhase(vector<Player *>) {
    int numOfArmies = 0;
    vector<Player *>::iterator it;
    for (it = this->player_list.begin(); it != this->player_list.end(); it++) {
        //iterating through list of players
        // (# of territories owned divided by 3, rounded down
        numOfArmies = (*it)->getTerritories().size();
        numOfArmies = floor(numOfArmies / 3);

        vector<Continent *> mapContinents = this->map->getContinents();  // get all continents for current map
        vector<Territory *> playerTerritories = (*it)->getTerritories(); // get the user's territories
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
        int totalArmySize = (*it)->getReinforcementPool() + numOfArmies;
        (*it)->setReinforcementPool(totalArmySize);
    }
}

void GameEngine::issueOrdersPhase(vector<Player*> players, vector<Territory *>) {
    std::string availableOrders[5] = {"Advance", "Bomb", "Airlift", "Blockade", "Negotiate"};
    string choice;
    string startTerritory;
    string targetTerritory;
    string targetPlayer;
    int numberOfArmies;
    bool orderIsDeploy;
    bool orderIsAdvance;
    bool orderIsBomb;
    bool orderIsAirlift;
    bool orderIsBlockade;
    bool orderIsNegotiate;

    Territory* start = nullptr;
    Territory* target = nullptr;
    Player* targetPlayerObj = nullptr;

    for(Player* player: this->getPlayersList()) {

        // DEPLOY armies until the reinforcement pool is empty
        int availableArmies = player->getReinforcementPool();
        int armiesToDeploy = 0;
        do {
            if (availableArmies < 1) {
                break;
            }
            if (availableArmies > 0) {
                for (Territory* territory: player->getTerritories()) {
                    cout << "# armies to deploy to " << territory->getTerritoryName() << " (max " << player->getReinforcementPool() << ")" << ": ";
                    cin >> armiesToDeploy;
                    while (armiesToDeploy > availableArmies || armiesToDeploy < 0) {
                        cout << "# armies to deploy to " << territory->getTerritoryName() << " (max " << player->getReinforcementPool() << ")" << ": ";
                        cin >> armiesToDeploy;
                    }
                    availableArmies -= armiesToDeploy;
                    cout << "Deploying " << to_string(armiesToDeploy) << " armies to " << territory->getTerritoryName() << endl;
                    player->issueOrder(availableOrders[0], territory, numberOfArmies);
                }
            }
        } while (availableArmies > 0);

        if (availableArmies < 1) {
            cout << "No more armies to deploy.";
        }


        // Let the player choose an order
        bool validChoice = false;
        while (!validChoice) {
            cout << "Please enter the desired order from the list bellow:" << endl;
            for(std::string order: availableOrders) {
                cout << order << endl;
            }
            cout << "Order: ";

            cin >> choice;
            for(std::string order: availableOrders) {
                if (choice == order) {
                    validChoice = true;
                    break;
                }
            }
        }


        // FOR ADVANCE ORDER
        orderIsAdvance = availableOrders[0] == choice;
        if (orderIsAdvance) {
            cout << player->getPlayerName() << "choose to ADVANCE " << endl;
            cout << "Please SELECT a start territory by name from the list:" << endl;

            if (player->getTerritories().size() < 1) {
                cout << player->getPlayerName() << " has no controlled territories. Nothing to advance" << endl;
                continue;

            } else {
                // display the list of territories controlled by player.
                for(Territory* territory: player->getTerritories()) {
                    cout << "PLAYER TERRITORY: " << territory->getTerritoryName() << " " << territory->getArmyCount() << " armies." << endl;
                    for(Territory* neighbour: territory->getAdjTerritories()) {
                        cout << "     NEIGHBOUR: ";
                        if(neighbour->isAllied(player)) {
                            cout << "FRIENDLY ";
                        } else if(neighbour->isEnemy(player)) {
                            cout << "ENEMY ";
                        }
                        cout << neighbour->getTerritoryName() << " " << neighbour->getArmyCount() << " armies" << endl;
                    }

                }

                // get user input for START TERRITORY.
                bool validChoice = false;
                while (!validChoice) {
                    cout << "Start territory: ";
                    cin >> startTerritory;
                    for(Territory* territory: player->getTerritories()) {
                        if(territory->getTerritoryName() == startTerritory) {
                            validChoice = true;
                            start = territory;
                        }
                    }
                    cout << "Invalid choice." << endl;
                }

                cout << player->getPlayerName() << " will start ADVANCE from " << start->getTerritoryName() << endl;

                // get input for target territory
                validChoice = false;
                do {
                    cout << "Target territory (by name): " << endl;
                    cin >> targetTerritory;
                    for(Territory* territory: start->getAdjTerritories()) {
                        if (territory->getTerritoryName() == targetTerritory) {
                            target = territory;
                            validChoice = true;
                        }
                    }
                } while (!validChoice);

                do {
                    cout << "Number of Armies to Advance (max " << start->getArmyCount()  << "): " << endl;
                    cin >> numberOfArmies;
                    if (numberOfArmies < start->getArmyCount()) {
                        player->issueOrder(availableOrders[0], target, numberOfArmies);
                    }
                } while (numberOfArmies > start->getArmyCount() );

                player->issueOrder(availableOrders[0], start, target, numberOfArmies);

            }
        }

        //FOR AIRLIFT ORDER
        if (orderIsAirlift) {
            cout << player->getPlayerName() << "choose to AIRLIFT " << endl;
            cout << "Please SELECT a start territory by name from the list:" << endl;

            if (player->getTerritories().size() < 1) {
                cout << player->getPlayerName() << " has no controlled territories. Nothing to airlift." << endl;
                continue;

            } else {
                // display the list of territories controlled by player.
                for(Territory* territory: player->getTerritories()) {
                    cout << "PLAYER TERRITORY: " << territory->getTerritoryName() << " " << territory->getArmyCount() << " armies." << endl;
                    for(Territory* neighbour: territory->getAdjTerritories()) {
                        if (neighbour->isAllied(player)) {
                            cout << "     NEIGHBOUR: ";
                            cout << "FRIENDLY ";
                            cout << neighbour->getTerritoryName() << " " << neighbour->getArmyCount() << " armies" << endl;
                        }
                    }
                }

                // get user input for START TERRITORY.
                bool validChoice = false;
                while (!validChoice) {
                    cout << "Start territory: ";
                    cin >> startTerritory;
                    for(Territory* territory: player->getTerritories()) {
                        if(territory->getTerritoryName() == startTerritory) {
                            validChoice = true;
                            start = territory;
                        }
                    }
                    cout << "Invalid choice." << endl;
                }

                cout << player->getPlayerName() << " will start AIRLIFT from " << start->getTerritoryName() << endl;

                // get input for target territory
                validChoice = false;
                do {
                    cout << "Target territory (by name): " << endl;
                    cin >> targetTerritory;
                    for(Territory* territory: start->getAdjTerritories()) {
                        if (territory->isAllied(player)) {
                            if (territory->getTerritoryName() == targetTerritory) {
                                target = territory;
                                validChoice = true;
                            }
                        }
                    }
                } while (!validChoice);

                do {
                    cout << "Number of Armies to AIRLIFT (max " << start->getArmyCount()  << "): " << endl;
                    cin >> numberOfArmies;
                    if (numberOfArmies < start->getArmyCount()) {
                        player->issueOrder(availableOrders[2], target, numberOfArmies);
                    }
                } while (numberOfArmies > start->getArmyCount() );
            }
        }


        // FOR BOMB ORDER
        orderIsBomb = choice == availableOrders[1];
        if (orderIsBomb) {
            cout << player->getPlayerName() << "choose to BOMB " << endl;
            bool validChoice = false;
            do {
                cout << "Target territory: " << endl;
                cin >> targetTerritory;
                for(Territory* territory: start->getAdjTerritories()) {
                    if (territory->isEnemy(player)) {
                        if (territory->getTerritoryName() == targetTerritory) {
                            target = territory;
                            validChoice = true;
                        }
                    }
                }
            } while (!validChoice);

            player->issueOrder(availableOrders[1], target);
        }


        // FOR BLOCKADE ORDER
        orderIsBlockade = choice == availableOrders[3];
        if (orderIsBlockade) {
            cout << player->getPlayerName() << "choose to BLOCKADE " << endl;
            bool validChoice = false;
            do {
                cout << "Target territory: " << endl;
                cin >> targetTerritory;
                for(Territory* territory: start->getAdjTerritories()) {
                    if (territory->isEnemy(player)) {
                        if (territory->getTerritoryName() == targetTerritory) {
                            target = territory;
                            validChoice = true;
                        }
                    }
                }
            } while (!validChoice);

            player->issueOrder(availableOrders[3], target);
        }



        // FOR NEGOTIATE ORDER
        orderIsNegotiate = choice == availableOrders[4];
        if(orderIsNegotiate) {
            cout << player->getPlayerName() << "choose to NEGOTIATE " << endl;
            do {
                cout << "Please choose a target player by name from the list:" << endl;
                for(Player* player1: this->getPlayersList()) {
                    cout << player1->getPlayerName() << ", ";
                }
                cout << endl;
                cout << "Target Player: " << endl;
                cin >> targetPlayer;

                if (targetPlayer == player->getPlayerName()) {
                    cout << "Cannot negotiate with yourself. Please choose a competing player.";
                    continue;
                }

                for(Player* player2: this->getPlayersList()) {
                    if(player2->getPlayerName() == targetPlayer) {
                        targetPlayerObj = player;
                        break;
                    }
                }
            } while (targetPlayerObj == nullptr);

            player->issueOrder(availableOrders[4], targetPlayerObj);
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


}
void GameEngine::startupPhase() {

}

void GameEngine::mainGameLoop() {

}









