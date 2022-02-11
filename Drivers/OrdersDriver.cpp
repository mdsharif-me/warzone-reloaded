//
// Created by tigerrrr on 2/11/2022.
//

#include <iostream>
#include "../Headers/Orders.h"

using namespace std;

int main() {

    auto* territory1 = new Territory;
    auto* territory2 = new Territory;
    auto* player = new Player();

    auto* deploy = new Deploy();
    auto* airlift = new Airlift();
    Bomb* bomb = new Bomb();

    auto* ordersList = new OrdersList();
    ordersList->add(deploy);
    ordersList->add(airlift);
    ordersList->add(bomb);

    cout << *ordersList;

    ordersList->move(0, 2);

    cout << *ordersList;

    ordersList->remove(0);

    cout << *ordersList;


    return 0;
}

