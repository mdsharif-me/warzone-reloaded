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
    for(int i = 0; i < 5;i++) {
        c->getCommand();
    }
    cout << "The list of commands in the command processor:" << endl;
    for(auto command: c->getCommandList()){
        cout << command->getCommand() << endl;
        if(c->validate(command->getCommand(), "start")){
            command->saveEffect("Change State to: 'maploaded'");
            cout << command->getEffect() << endl;
        }
        else if(c->validate(command->getCommand(), "maploaded")){
            command->saveEffect("EFFECT: Change State to: 'mapvalidated'");
            cout << command->getEffect() << endl;
        }
        else if(c->validate(command->getCommand(), "mapvalidated")){
            command->saveEffect("Change State to: 'playersadded'");
            cout << command->getEffect() << endl;
        }
        else if(c->validate(command->getCommand(), "playersadded")){
            command->saveEffect("Change State to: 'win'");
            cout << command->getEffect() << endl;
        }
        else if(c->validate(command->getCommand(), "win")){
            command->saveEffect("Game over!");
            cout << command->getEffect() << endl;
        }
    }
    return 0;

}

