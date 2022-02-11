
#include <vector>
#include <string>
#include <iostream>
#include "headers/Player.h"
using namespace std;

int main()
{
    vector<Order*> orderList;
    vector<string*> territoriesToDefend;
    vector<string*> territoriesToAttack;
    string territory1 = "Asia";
    string territory2 = "NAmerica";
    string territory3 = "SAmerica";
    string territory4 = "Europe";

    //Adding arbitrary list of territories that are to be attacked and defended.
    territoriesToAttack.push_back(&territory1);
    territoriesToAttack.push_back(&territory2);
    territoriesToDefend.push_back(&territory3);
    territoriesToDefend.push_back(&territory4);

    //Adding hand of cards owned by the player
    vector<string*> cards;
    string bomb = "bomb";
    string reinforcement = "reinforcement";
    string blockade = "blockade";
    cards.push_back(&bomb);
    cards.push_back(&reinforcement);
    cards.push_back(&blockade);

    //Creating Player object.
    Player* player = new Player("Deep",territoriesToAttack, territoriesToDefend, cards, orderList);
    //Issuing orders using issueOrder() method
    (*player).issueOrder("order1");
    (*player).issueOrder("order2");

    //Printing all the orders issued
    vector<Order*> orders = (*player).getOrderList();
    cout << "All the orders are: ";
    for (int i = 0; i < orders.size(); i++)
    {
        cout << orders[i]->getOrderName() << " ";
    }
    cout << endl;

    //Printing all the territories to be attacked
    vector<string*> toAttack = (*player).toAttack();
    cout << "Territories to be Attacked: ";
    for(int i = 0; i < toAttack.size(); i++){
        cout << *toAttack[i] << ", ";
    }
    cout << endl;

    //Printing all the territories
    vector<string*> toDefend = (*player).toDefend();
    cout << "Territories to be Defended: ";
    for(int i = 0; i < toDefend.size(); i++){
        cout << *toDefend[i] << ", ";
    }
    cout << endl;

}