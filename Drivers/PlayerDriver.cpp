#include <vector>
#include <string>
#include <iostream>
#include "../Headers/Player.h"
using namespace std;

int main()
{
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
    Player* player = new Player("Deep",territoriesToAttack, territoriesToDefend, cards);
    //Issuing orders using issueOrder() method
    player ->issueOrder("Deploy");
    player->issueOrder("Bomb");

    //Printing Player's name
    cout << "Players name is: " << player->getPlayerName() <<endl;
    //Printing all the orders issued
    cout << "All the orders are: \n";
    cout << *player->getOrderList() << endl;

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