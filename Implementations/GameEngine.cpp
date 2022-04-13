#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <algorithm>
#include "../Headers/GameEngine.h"
using namespace std;

GameEngine::GameEngine(vector<Player*> players_list, Map* map, Deck* deck){
    this->player_list = players_list;
    this->map = map;
    this->deck = deck;
}
vector<Player *> GameEngine::getPlayersList() {
    return player_list;
}
void GameEngine::mainGameLoop(int maxNumOfTurns, bool tournamentMode) {
// 1. Round robin fashion in the order setup in startup phase
// 2. This loop shall continue until only one of the players owns all the terrotires in the map.
// 3. Also checks if any player does not control at least one territory
// 4. if so the player is removed from the game.
    int round = 1;
    while (player_list.size() != 1 && maxNumOfTurns != round){
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
    if(tournamentMode) {
        vector<int> numbers;
        for (auto player: player_list) {
            int counter = player->getTerritories().size();
            cout << player->getPlayerName() << " has " << counter << " territories in round " << maxNumOfTurns << endl;
            numbers.push_back(counter);
        }
        int greatest = 0;
        int greatestIndex = 0;
        for(int i = 0; i < numbers.size(); i++){
            if(greatest < numbers[i]){
                greatest = numbers[i];
                greatestIndex = i;
            }
        }
        cout << player_list[greatestIndex]->getPlayerName() << "wins!!" << endl;
        winnerIndex = greatestIndex;
    }
    else{
        cout << player_list.front()->getPlayerName() << "wins!!" << endl;
        winnerIndex = 0;
        transition("win");
    }
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
        cout << (*i)->getPlayerName() << " given " << numOfArmies << " for the territory they own." << endl;
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
                cout << "BONUS ARMY for :" << continent->getName() << " = " << continent->getControlBonus() << endl;
                numOfArmies += continent->getControlBonus();
            }
        }
        // minimal number of reinforcement armies per turn for any player is 3.
        if (numOfArmies < 3) {
            numOfArmies = 3;
        }
        // add new army number to the user's pool
        int totalArmySize = (*i)->getReinforcementPool() + numOfArmies;
        cout << "TOTAL BONUS ARMY OF: " << totalArmySize << " [TO: " << (*i)->getPlayerName() << "]"<< endl;
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
        cout << "----------------------------------------------------------------------------" << endl;
        cout << player->getPlayerName() << " ORDER EXECUTION taking place!!" << endl;
        cout << "============================================================================" << endl;
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
    for(Player* player: this->getPlayersList()) {
        player->getNegotiatePlayersList().clear();
    }
}
void GameEngine::addPlayer(string command, string strategy){
    if(strategy.empty()) {
        string playerName = command.substr(10);
        string human = "Human";
        player_list.push_back(new Player(playerName, human));
        cout << "PLAYER ADDED: " << playerName << endl;
    }
    else{
        string playerName = command.substr(10);
        player_list.push_back(new Player(playerName, strategy));
        cout << "PLAYER ADDED: " << playerName << endl;
    }
    if (player_list.size() >= 2 && player_list.size() <= 6) {
        cout << "CHANGE STATE TO: playersadded" << endl;
        transition("playersadded");
    }
    if (player_list.size() == 6) {
        cout << "MAX PLAYER LIST REACHED : Cannot add more players";
    }
}
void GameEngine:: loadAndValidateMap(string& path){
    MapLoader mapLoader(path);
    if (mapLoader.extract()) {
        this->map = mapLoader.createMap();
        transition("maploaded");
        if (map->mapValidate()) {
            cout << "\nSuccess: Map \"" << path << "\" has been built.\n\n";
            transition("mapvalidated");
        } else {
            cout << "\nError: Map file \"" << path << "\" is invalid.\n\n";
            exit(0);
        }
    } else {
        cout << "COMMAND FAIL: Tournament LoadMap failed" << endl;
    }
}
void GameEngine::gameStart(int maxNumOfTurns, bool tournamentMode) {
    this->deck->fillDeck();
    for(int i = 0; i < player_list.size();i++){
        //player_list[i]->getPlayerHand()->addToHand(new Card("Reinforcement"));
        player_list[i]->getPlayerHand()->addToHand(new Card("Blockade"));
        player_list[i]->getPlayerHand()->addToHand(new Card("Airlift"));
        player_list[i]->getPlayerHand()->addToHand(new Card("Diplomacy"));
        player_list[i]->getPlayerHand()->addToHand(new Card("Bomb"));
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
    mainGameLoop(maxNumOfTurns, tournamentMode);
}
void GameEngine::startupPhase(CommandProcessor* cp) {
    transition("start");
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
                transition("maploaded");
            } else {
                cout << "COMMAND FAIL: LoadMap failed" << endl;
            }
        }
        else if(command->getCommand() == "validatemap"){
            if (cp->validate(command->getCommand(), state)) {
                if (map->mapValidate()) {
                    cout << "\nSuccess: Map \"" << command->getCommand() << "\" has been built.\n\n";
                    cout << "CHANGE STATE TO: mapvalidated" << endl;
                    transition("mapvalidated");
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
                addPlayer(command->getCommand(), "");
            }
            else{
                cout << "COMMAND FAIL: addplayer failed" << endl;
            }
        }
        else if(command->getCommand() == "replay"){
            if(cp->validate(command->getCommand(),state)) {
                clear();
            }
            else{
                cout << "COMMAND FAIL: replay failed" << endl;
            }
        }
        else if(command->getCommand() == "gamestart") {
            if (cp->validate(command->getCommand(), state)) {
                cout << "GAME STARTING!!" << endl;
                gameStart(-1, false);
            }
            else{
                cout << "COMMAND FAIL: gamestart failed" << endl;
            }
        }
        else if(command->getCommand().find("tournament") != string::npos){
            try {
                vector<string> listOfMaps;
                vector<string> listOfPlayers;
                int listOfMapsFilesStartIndex = command->getCommand().find("-M ");
                int listOfMapFilesEndIndex = command->getCommand().find(" -P");
                string listOfMapFiles = command->getCommand().substr(listOfMapsFilesStartIndex + 2,listOfMapFilesEndIndex - listOfMapsFilesStartIndex - 2);
                cout << "List of Map Files: " << listOfMapFiles << endl;
                string maps = listOfMapFiles;
                int listOfPlayersStratStartIndex = command->getCommand().find("-P ");
                int listOfPlayersStratEndIndex = command->getCommand().find(" -G");
                string listOfPlayersStrat = command->getCommand().substr(listOfPlayersStratStartIndex + 2,listOfPlayersStratEndIndex - listOfPlayersStratStartIndex - 2);
                cout << "List of Player Strategies: " << listOfPlayersStrat << endl;
                string players = listOfPlayersStrat;
                int numberOfGamesStartIndex = command->getCommand().find("-G ");
                int numberOfGamesEndIndex = command->getCommand().find(" -D");
                int numberOfGames = stoi(command->getCommand().substr(numberOfGamesStartIndex + 3,numberOfGamesEndIndex - numberOfGamesStartIndex - 3));
                cout <<"Tournament >> Number of Games: " << numberOfGames << endl;

                int maxNoOfTurnsStartIndex = command->getCommand().find("-D ");
                int maxNoOfTurns = stoi(command->getCommand().substr(maxNoOfTurnsStartIndex + 3));
                cout << "Tournament >> Maximum number of Turns per player: " << maxNoOfTurns << endl;

                //Splitting listOfMapsFiles
                int pos = 0;
                std::string token;
                while ((pos = listOfMapFiles.find(", ")) != std::string::npos) {
                    token = listOfMapFiles.substr(1, pos-1);
                    listOfMaps.push_back(token);
                    listOfMapFiles.erase(0, pos + 1);
                }
                if ((pos = listOfMapFiles.find(",")) == std::string::npos){
                    listOfMaps.push_back(listOfMapFiles.substr(pos+2));
                }
                if(listOfMaps.size() > 5 || listOfMaps.size() <= 0){
                    throw "Number of Maps: greater than 5 or less than 1";
                }
                //Splitting players
                pos = 0;
                while ((pos = listOfPlayersStrat.find(", ")) != std::string::npos) {
                    token = listOfPlayersStrat.substr(1, pos-1);
                    listOfPlayers.push_back(token);
                    listOfPlayersStrat.erase(0, pos + 1);
                }
                if ((pos = listOfPlayersStrat.find(", ")) == std::string::npos){
                    listOfPlayers.push_back(listOfPlayersStrat.substr(pos+2));
                }
                if(listOfPlayers.size() < 2 || listOfPlayers.size() > 4){
                    throw "Number of Players less than 2 or greater than 4";
                }
                if(numberOfGames < 1 || numberOfGames > 5){
                    throw "Number of games less than 1 or greater than 5";
                }
                if(maxNoOfTurns < 10 || maxNoOfTurns > 50){
                    throw "Maximum number of turns is less than 10 or greater than 50";
                }
                vector<vector<string>> result_;


                for(int i = 0; i < listOfMaps.size(); i++) {
                    loadAndValidateMap(listOfMaps[i]);
                    vector<string> empty_vector;
                    result_.push_back(empty_vector);
                    for (int j = 0; j < numberOfGames; j++) {
                        cout << "__________________________________________________________________________" << endl;
                        cout << "GAME " << j+1 << endl;
                        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

                        for(int i = 0; i < listOfPlayers.size(); i++){
                            string playerName = "addplayer player" + to_string(i);
                            addPlayer(playerName, listOfPlayers[i]);
                        }
                        gameStart(maxNoOfTurns, true);

                        //typeid(player_list.front()->getPlayerStrategy()).name();
                        //result_[i].push_back(player_list[winnerIndex]->getPlayerName());
                        string type;
                        if (dynamic_cast<Human*>(player_list[winnerIndex]->getPlayerStrategy()) != nullptr){
                            type = "Human";
                        }
                        else if (dynamic_cast<Aggressive*>(player_list[winnerIndex]->getPlayerStrategy()) != nullptr){
                            type = "Aggressive";
                        }
                        else if (dynamic_cast<Benevolent*>(player_list[winnerIndex]->getPlayerStrategy()) != nullptr){
                            type = "Benevolent";
                        }
                        else if (dynamic_cast<Cheater*>(player_list[winnerIndex]->getPlayerStrategy()) != nullptr){
                            type = "Cheater";
                        }
                        else if (dynamic_cast<Neutral*>(player_list[winnerIndex]->getPlayerStrategy()) != nullptr){
                            type = "Neutral";
                        }
                        result_[i].push_back(type);
                        player_list.clear();
                    }
                }
                tournamentSettings(maps, players, numberOfGames, maxNoOfTurns);
                results(result_);
            }
            catch (const out_of_range& oor){
                cout << "COMMAND FAIL: Tournament failed " << oor.what() << endl;
            }
            catch (const char* msg){
                cout << "ERROR: " << msg << endl;
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
void GameEngine::clear() {
    delete deck;
    delete map;
    for(auto player: player_list){
        delete player;
    }
    player_list.clear();
    transition("start");
}
GameEngine &GameEngine::operator=(const GameEngine &gameEngine) {
    this->player_list = gameEngine.player_list;
    this->map = gameEngine.map;
    this->state = gameEngine.state;
    this->deck = gameEngine.deck;
    return *this;
}
ostream &operator<<(ostream &os, const GameEngine &gameEngine) {
    os << "The player list: " << endl;
    for (auto* player: gameEngine.player_list) {
        os << player->getName() << endl;
    }
    if(gameEngine.map != nullptr) {
        os << "Map: True" << endl;
    } else {
        os << "Map: False" << endl;
    }
    os << "Current state: " << gameEngine.state << endl;
    if(gameEngine.deck != nullptr) {
        os << "Deck : True"<< endl;
    } else {
        os << "Deck: False" << endl;
    }
    return os;
}
GameEngine::GameEngine(const GameEngine & gameEngine) {
    this->player_list = gameEngine.player_list;
    this->map = gameEngine.map;
    this->state = gameEngine.state;
    this->deck = gameEngine.deck;
}

void GameEngine::setState(const string& state_) {
    this->state = state_;
}

string GameEngine::getState() {
    return this->state;
}
void GameEngine::stringToLog(const string &message) {
    ofstream myFile;
    myFile.open("../gamelog.txt", ios::app);
    if (myFile.is_open()) {
        myFile << message;
        myFile << "\n";
        myFile.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
}
void GameEngine::transition(const string& state_) {
    this->setState(state_);
    Subject* subject = new Subject();
    subject->setMessage("Game Engine new state: " + this->getState());
    LogObserver* logObserver = new LogObserver(subject);
    subject->Notify(this);
}
void GameEngine::results(vector<vector<string>> result_) {
    string result;
    for(int i = 0; i < result_.size(); i++){
        result += "Map " + to_string(i) + "  |  ";
        for( int j = 0; j < result_[i].size(); j++){
            result += result_[i][j] + "  |  ";
        }
        result += "\n";
    }
    cout << result << endl;
    Subject* subject = new Subject();
    subject->setMessage("Results: \n" + result);
    LogObserver* logObserver = new LogObserver(subject);
    subject->Notify(this);
}
void GameEngine::tournamentSettings(string& mapList, string& playerList, int numberOfGames, int maxNum) {
    string result = "Tournament mode: \n" ;
    result += "M: "+ mapList + "\nP: " + playerList + "\nG: " + to_string(numberOfGames) + "\nD: " + to_string(maxNum);
    cout << result << endl;
    Subject* subject = new Subject();
    subject->setMessage("Results: \n" + result);
    LogObserver* logObserver = new LogObserver(subject);
    subject->Notify(this);
}











