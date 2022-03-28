//
// Created by deepp on 2022-03-26.
//

#include "../Headers/CommandProcessing.h"
#include "../Headers/Orders.h"
#include "../Headers/GameEngine.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

   /* auto* c1 = new Command("loadmap");
    if (dynamic_cast<ILoggable*>(c1) != nullptr)
    {
        std::cout << "C1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(c1) != nullptr)
    {
        std::cout << "C1 is a subclass of Subject" << std::endl;
    }

    auto* cp1 = new CommandProcessor;
    if (dynamic_cast<ILoggable*>(cp1) != nullptr)
    {
        std::cout << "CP1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(cp1) != nullptr)
    {
        std::cout << "CP1 is a subclass of Subject" << std::endl;
    }

    auto* o1 = new Deploy();
    if (dynamic_cast<ILoggable*>(o1) != nullptr)
    {
        std::cout << "O1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(o1) != nullptr)
    {
        std::cout << "O1 is a subclass of Subject" << std::endl;
    }

    auto* ol1 = new OrdersList();
    if (dynamic_cast<ILoggable*>(ol1) != nullptr)
    {
        std::cout << "OL1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(o1) != nullptr)
    {
        std::cout << "OL1 is a subclass of Subject" << std::endl;
    }*/

    /*auto* ge1 = new GameEngine();
    if (dynamic_cast<ILoggable*>(ge1) != nullptr)
    {
        std::cout << "OL1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(o1) != nullptr)
    {
        std::cout << "OL1 is a subclass of Subject" << std::endl;
    }*/

    Command* command1 = new Command("loadmap");
    command1->saveEffect("maploaded");


    /*CommandProcessor* c = new CommandProcessor;
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
    c->getCommand();*/
    return 0;
}

