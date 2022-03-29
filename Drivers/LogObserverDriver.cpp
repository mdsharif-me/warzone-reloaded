//
// Created by tigerrrr on 3/29/2022.
//

//
// Created by deepp on 2022-03-26.
//

#include "../Headers/CommandProcessing.h"
#include "../Headers/Orders.h"
#include "../Headers/GameEngine.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    // 5.2.9
    //Driver clearly demonstrates that the Command, class is a subclass of the Subject and ILoggable classes
     auto* c1 = new Command("loadmap");
     if (dynamic_cast<ILoggable*>(c1) != nullptr)
     {
         std::cout << "C1 is a subclass of ILoggable" << std::endl;
     }
     if (dynamic_cast<Subject*>(c1) != nullptr)
     {
         std::cout << "C1 is a subclass of Subject" << std::endl;
     }


      // 5.2.9
     //Driver clearly demonstrates that the CommandProcessor, class is a subclass of the Subject and ILoggable classes
     auto* cp1 = new CommandProcessor;
     if (dynamic_cast<ILoggable*>(cp1) != nullptr)
     {
         std::cout << "CP1 is a subclass of ILoggable" << std::endl;
     }
     if (dynamic_cast<Subject*>(cp1) != nullptr)
     {
         std::cout << "CP1 is a subclass of Subject" << std::endl;
     }


      // 5.2.9
     //Driver clearly demonstrates that the Order, class is a subclass of the Subject and ILoggable classes

     auto* o1 = new Deploy();
     if (dynamic_cast<ILoggable*>(o1) != nullptr)
     {
         std::cout << "O1 is a subclass of ILoggable" << std::endl;
     }
     if (dynamic_cast<Subject*>(o1) != nullptr)
     {
         std::cout << "O1 is a subclass of Subject" << std::endl;
     }


     // 5.2.9
    //Driver clearly demonstrates that the OrderList, class is a subclass of the Subject and ILoggable classes

     auto* ol1 = new OrdersList();
     if (dynamic_cast<ILoggable*>(ol1) != nullptr)
     {
         std::cout << "OL1 is a subclass of ILoggable" << std::endl;
     }
     if (dynamic_cast<Subject*>(ol1) != nullptr)
     {
         std::cout << "OL1 is a subclass of Subject" << std::endl;
     }


    // 5.2.9
    //Driver clearly demonstrates that the GameEngine, class is a subclass of the Subject and ILoggable classes

    auto* ge1 = new GameEngine();
    if (dynamic_cast<ILoggable*>(ge1) != nullptr)
    {
        std::cout << "OL1 is a subclass of ILoggable" << std::endl;
    }
    if (dynamic_cast<Subject*>(ge1) != nullptr)
    {
        std::cout << "OL1 is a subclass of Subject" << std::endl;
    }


    // 5.2.10
     // Driver clearly demonstrates that the CommandProcessor::saveCommand() are effectively using
     // the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
    auto* cp2 = new CommandProcessor;
    // get command internally uses read command. Read command internally uses save command.
    cp2->getCommand();

    // 5.2.10
     // Driver clearly demonstrates that the Order::execute() are effectively using
     // the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
     auto* player = new Player;
     auto* enemy = new Player;
     player->setName("player");
     enemy->setName("enemy");
    Order* order = new Negotiate(player, enemy);
    order->execute();

    // Driver clearly demonstrates that the Order::execute() are effectively using
    // the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
    auto* command1 = new Command("loadmap");
    command1->saveEffect("maploaded");


   // 5.2.10
    // Driver clearly demonstrates that the OrderList::addOrder(), are effectively using
    // the Observer patterns’ Notify(Subject) method to trigger the writing of an entry in the log file
    auto* player2 = new Player;
    auto* enemy2 = new Player;
    player2->setName("player");
    enemy2->setName("enemy");
    Order* order2 = new Negotiate(player2, enemy2);
    auto* ordersList = new OrdersList;
    ordersList->add(order2);

    // 5.2.10
    // Driver clearly demonstrates that the GameEngine::transition(, are effectively using the Observer patterns’ Notify(Subject) method
    // to trigger the writing of an entry in the log file
    auto* gameEngine2 = new GameEngine;
    gameEngine2->transition("win");


    // 5.2.11
    // Driver clearly demonstrates that when commands are entered on the console or read from a file,
    // the commands are written to the gamelog.txt file, and their effect is written to the log file when the commands are executed
    // use console

    //  5.2.12
    // Driver clearly demonstrates that when an order is added to the order list of a player,
    // the game log observer is notified which results in outputting the order to the log file
    auto* player3 = new Player;
    auto* enemy3 = new Player;
    auto* ordersList3 = new OrdersList;
    player3->setOrderList(ordersList3);
    player3->getOrderList()->add(new Negotiate(player3, enemy3));

    //  5.2.13
    // Driver clearly demonstrates that when an order is executed,
    // the game log observer is notified which results in outputting the effect of the order to the log file
    auto* player4 = new Player;
    auto* enemy4 = new Player;
    player4->setName("player4");
    enemy4->setName("enemy4");
    Order* order4 = new Negotiate(player4, enemy4);
    order4->execute();

    // 5.2.14
    // Driver clearly demonstrates that when the GameEngine changes its state,
    // the game log observer is notified and the new state is output to the log file.
    auto* gameEngine3 = new GameEngine;
    gameEngine3->setState("start");
    gameEngine3->transition("maploaded");



    return 0;
}



