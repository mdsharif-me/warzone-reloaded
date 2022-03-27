#include <iostream>
#include <string>
#include "../Headers/GameEngine.h"
using namespace std;

int main(int argc, char* argv[]) {
    cout << "------------------\n";
    cout << "| WARZONE v1.0 |\n";
    cout << "------------------\n";
    cout << "\nYOU ARE AT THE START PHASE.\n" << endl;
    CommandProcessor* c;
    if(argc == 1) {
        cout << "Enter your command in the command line argument" << endl;
    }
    else if(argc == 2){
        string command = argv[1];
        if(command == "-console")
            c = new CommandProcessor();
    }
    else if(argc == 3) {
        string command = argv[1];
        if (command == "-file") {
            string fileName = argv[2];
            c = new FileCommandProcessorAdapter(fileName);
        }
    }
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
    GameEngine* g = new GameEngine();
    g->startupPhase(c);

    vector<Player*> tempPlayers;
    vector<string> mapFileList = { "../Maps/canada.map"};
    // Check the map files and build maps

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


    auto* player = new Player();
    auto* enemyPlayer = new Player();
    auto* enemyPlayer2 = new Player;
    enemyPlayer2->setName("Deep");
    player->setName("Mike");
    enemyPlayer->setName("Enemy");
    vector<Player* > players;
    players.push_back(player);
    players.push_back(enemyPlayer);
    players.push_back(enemyPlayer2);

    for(int i = 0; i < players.size();i++){
        players[i]->getPlayerHand()->addToHand(new Card("deploy"));
        players[i]->getPlayerHand()->addToHand(new Card("reinforcement"));
        players[i]->getPlayerHand()->addToHand(new Card("blockade"));
        players[i]->getPlayerHand()->addToHand(new Card("airlift"));
        players[i]->getPlayerHand()->addToHand(new Card("diplomacy"));
    }

    cout << "Loading Main Game loop...." << endl;
    g->mainGameLoop();
    delete player;
    delete enemyPlayer;
    delete enemyPlayer2;
    return 0;
}

