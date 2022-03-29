//
// Created by deepp on 2022-03-26.
//

#include "../Headers/CommandProcessing.h"
#include "../Headers/Orders.h"
#include "../Headers/GameEngine.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {



    CommandProcessor* c = new CommandProcessor;
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
    c->getCommand();
    return 0;
}

