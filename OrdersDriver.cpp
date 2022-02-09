#include <iostream>
#include "headers/Orders.h"

using namespace std;

int main() {

    Territory* territory1 = new Territory;
    Territory* territory2 = new Territory;
    Player* player = new Player();

    Deploy* deploy = new Deploy();
    Airlift* airlift = new Airlift();
    Bomb* bomb = new Bomb();

    OrdersList* ordersList = new OrdersList();
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

