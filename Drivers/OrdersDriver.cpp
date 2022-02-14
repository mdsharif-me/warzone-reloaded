//
// Created by tigerrrr on 2/11/2022.
//

#include <iostream>
#include "../Headers/Orders.h"

using namespace std;

int main() {

    auto* player = new Player();

    auto* deploy = new Deploy();
    auto* airlift = new Airlift();
    Bomb* bomb = new Bomb();

    auto* ordersList = new OrdersList();
    ordersList->add(deploy);
    ordersList->add(airlift);
    ordersList->add(bomb);

    cout << *ordersList;

    //move first order from index 0 to index 2
    ordersList->move(0, 2);

    cout << *ordersList;

    // remove the order at position 0
    ordersList->remove(0);

    cout << *ordersList;

    delete ordersList;

    return 0;
}

