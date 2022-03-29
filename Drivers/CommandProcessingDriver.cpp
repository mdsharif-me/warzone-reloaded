//
// Created by deepp on 2022-03-26.
//

#include "../Headers/CommandProcessing.h"
#include "../Headers/Orders.h"
#include "../Headers/GameEngine.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
   CommandProcessor* c;
    if(argc == 1) {
        cout << "Enter your command in the command line arguement" << endl;
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
    for(int i = 0; i < 3;i++) {
        c->getCommand();
    }
    cout << "The list of commands in the command processor:" << endl;
    for(auto command: c->getCommandList()){
        cout << command->getCommand() << endl;
        c->validate(command->getCommand(), "start");
        c->validate(command->getCommand(), "maploaded");
        c->validate(command->getCommand(), "mapvalidated");
        c->validate(command->getCommand(), "playersadded");
        c->validate(command->getCommand(), "win");
    }
    return 0;

}

