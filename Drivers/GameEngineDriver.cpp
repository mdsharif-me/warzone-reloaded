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
            cout << "USER SELECTED -file " << command << endl;
            string fileName = argv[2];
            c = new FileCommandProcessorAdapter(fileName);
        }
    }
    GameEngine* g = new GameEngine();
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
    g->setDeck(deck);
    g->startupPhase(c);


    //g->mainGameLoop();
    return 0;
}

