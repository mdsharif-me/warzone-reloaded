#include <iostream>
#include <string>
#include "../Headers/GameEngine.h"
using namespace std;

int main() {
    /*string currentState="start";
    string input;
    cout << "Game has started\n";
    GameEngine* g = new GameEngine();
    while (true){
        cout<<"\nCurrent state: "<< currentState << "\n";
        cout<<"Type a command: ";
        cin >> input;
        if (input=="loadmap"){
            currentState=g->loadMap(currentState);
        }else if(input=="validatemap"){
            currentState=g->validateMap(currentState);
        }else if(input=="addplayer"){
            currentState=g->addPlayer(currentState);
        }else if(input=="assigncountries"){
            currentState=g->assignCountries(currentState);
        }else if(input=="issueorder"){
            currentState=g->issueOrder(currentState);
        }else if(input=="endissueorders"){
            currentState=g->endIssueOrders(currentState);
        }else if(input=="execorder"){
            currentState=g->execOrder(currentState);
        }else if(input=="endexecorders"){
            currentState=g->endExecOrders(currentState);
        }else if(input=="win"){
            currentState=g->win(currentState);
        }else if(input=="end"){
            currentState=g->end(currentState);
            if (currentState=="exit"){
            return 0;
            }
        }else if(input=="play"){
            currentState =g->play(currentState);
        }else {
            cout<< "Invalid input\n";
        }
    }
    delete g;
     */
    int numberOfPlayers = 0;
    vector<Player*> tempPlayers;
    vector<string> mapFileList = { "../Maps/canada.map"};
    // Check the map files and build maps
    Map* m;
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
    GameEngine* g = new GameEngine();
    //g->createPlayers();
    //g->startupPhase();
    vector<Territory*> playerTerritories;
    vector<Territory*> enemyTerritories;
    int numberOfArmies;

    auto* player = new Player();
    auto* enemyPlayer = new Player();
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
    player->setReinforcementPool(50); // should be done in part 2
    enemyPlayer->setTerritories(enemyTerritories);
    enemyPlayer->setReinforcementPool(50); // part2
    Deck* deck = new Deck();
    deck->addToDeck(new Card("deploy"));
    deck->addToDeck(new Card("reinforcement"));
    deck->addToDeck(new Card("blockade"));
    deck->addToDeck(new Card("airlift"));
    deck->addToDeck(new Card("diplomacy"));
    deck->addToDeck(new Card("deploy"));
    deck->addToDeck(new Card("reinforcement"));
    deck->addToDeck(new Card("blockade"));
    deck->addToDeck(new Card("airlift"));
    deck->addToDeck(new Card("diplomacy"));
    deck->addToDeck(new Card("deploy"));
    deck->addToDeck(new Card("reinforcement"));
    deck->addToDeck(new Card("blockade"));
    deck->addToDeck(new Card("airlift"));
    deck->addToDeck(new Card("diplomacy"));

    vector<Player* > players;
    players.push_back(player);
    players.push_back(enemyPlayer);
    for(int i = 0; i < players.size();i++){
        players[i]->getPlayerHand()->addToHand(new Card("deploy"));
        players[i]->getPlayerHand()->addToHand(new Card("reinforcement"));
        players[i]->getPlayerHand()->addToHand(new Card("blockade"));
        players[i]->getPlayerHand()->addToHand(new Card("airlift"));
        players[i]->getPlayerHand()->addToHand(new Card("diplomacy"));
    }
    g->setPlayerList(players);
    g->setDeck(deck);
    g->setMap(m);
    cout << "Loading Main Game loop...." << endl;
    g->mainGameLoop();

    delete player;
    delete enemyPlayer;
    return 0;
}

