//
// Created by tigerrrr on 2/11/2022.
//

#include <iostream>
#include "../Headers/Orders.h"

using namespace std;

int main() {

    auto * order = new Order();
    auto* deploy = new Deploy();
    auto* advance = new Advance();
    auto * bomb = new Bomb();
    auto * blockade = new Blockade();
    auto* airlift = new Airlift();
    auto * negotiate = new Negotiate();

    cout << "adding orders to orderList...\n";
    auto* ordersList = new OrdersList();
    ordersList->add(order);
    ordersList->add(deploy);
    ordersList->add(advance);
    ordersList->add(bomb);
    ordersList->add(blockade);
    ordersList->add(airlift);
    ordersList->add(negotiate);

    cout << "displaying orders...\n";
    cout << *ordersList;

    //move first order from index 0 to index 2
    cout << "moving order at index 0 to index 2\n";
    ordersList->move(0, 2);

    cout << "displaying changes\n";
    cout << *ordersList << endl;

    //move first order from index 1 to index 3
    cout << "moving order at index 1 to index 3\n";
    ordersList->move(1, 3);
    cout << "displaying changes\n";
    cout << *ordersList << endl;


    // remove the order at position 0
    cout << "removing order at index 0...\n";
    ordersList->remove(0);
    cout << "displaying changes\n";
    cout << *ordersList;

    // remove the order at position 3
    cout << "removing order at index 3...\n";
    ordersList->remove(3);
    cout << "displaying changes\n";
    cout << *ordersList;

    cout << "validating negotiate order...\n";
    if (negotiate->validate() == true) {}
    cout << "order Negotiate is validated\n\n";

    cout << "executing orders...\n";
    deploy->execute();
    advance->execute();
    bomb->execute();
    blockade->execute();
    airlift->execute();
    negotiate->execute();

    delete ordersList;

    return 0;
}

