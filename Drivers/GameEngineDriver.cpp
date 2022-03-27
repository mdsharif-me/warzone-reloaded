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
        if(command == "-console") {
            cout << "USER SELECTED -console" << endl;
            c = new CommandProcessor();
        }
    }
    else if(argc == 3) {
        string command = argv[1];
        if (command == "-file") {
            cout << "USER SELECTED -file " << command << endl;
            string fileName = argv[2];
            c = new FileCommandProcessorAdapter(fileName);
        }
    }
    GameEngine* g = new GameEngine();
    g->startupPhase(c);
    //vector<Player*> tempPlayers;
    //vector<string> mapFileList = { "../Maps/canada.map"};
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


    //auto* player = new Player();
    //auto* enemyPlayer = new Player();
    //auto* enemyPlayer2 = new Player;
    //enemyPlayer2->setName("Deep");
    //player->setName("Mike");
    //enemyPlayer->setName("Enemy");
    //vector<Player* > players;
    //players.push_back(player);
    //players.push_back(enemyPlayer);
    //players.push_back(enemyPlayer2);

    for(int i = 0; i < g->getPlayersList().size();i++){
        g->getPlayersList()[i]->getPlayerHand()->addToHand(new Card("deploy"));
        g->getPlayersList()[i]->getPlayerHand()->addToHand(new Card("reinforcement"));
        g->getPlayersList()[i]->getPlayerHand()->addToHand(new Card("blockade"));
        g->getPlayersList()[i]->getPlayerHand()->addToHand(new Card("airlift"));
        g->getPlayersList()[i]->getPlayerHand()->addToHand(new Card("diplomacy"));
    }
    //delete player;
    //delete enemyPlayer;
    //delete enemyPlayer2;
    return 0;
}

