#include <iostream>
#include <string>
#include "../Headers/GameEngine.h"
using namespace std;

int main(int argc, char* argv[]) {
    cout << "------------------\n";
    cout << "| WARZONE v1.0 |\n";
    cout << "------------------\n";
    cout << "\nYOU ARE AT THE START PHASE.\n" << endl;
    //../Maps/canada.map
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
            string fileName = argv[2];
            cout << "USER SELECTED -file " << fileName << endl;
            c = new FileCommandProcessorAdapter(fileName);
        }
    }
    GameEngine* g = new GameEngine();
    Deck* deck = new Deck();
    deck->addToDeck(new Card("Reinforcement"));
    deck->addToDeck(new Card("Bomb"));
    deck->addToDeck(new Card("Blockade"));
    deck->addToDeck(new Card("Airlift"));
    deck->addToDeck(new Card("Diplomacy"));
    deck->addToDeck(new Card("Reinforcement"));
    deck->addToDeck(new Card("Bomb"));
    deck->addToDeck(new Card("Blockade"));
    deck->addToDeck(new Card("Airlift"));
    deck->addToDeck(new Card("Diplomacy"));
    deck->addToDeck(new Card("Reinforcement"));
    deck->addToDeck(new Card("Bomb"));
    deck->addToDeck(new Card("Blockade"));
    deck->addToDeck(new Card("Airlift"));
    deck->addToDeck(new Card("Diplomacy"));
    g->setDeck(deck);
    g->startupPhase(c);


    //g->mainGameLoop();
    return 0;
}

