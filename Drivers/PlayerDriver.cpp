#include <vector>
#include <string>
#include <iostream>
#include "../Headers/Player.h"
using namespace std;

int main()
{
    vector<Territory*> territoriesToDefend;
    vector<Territory*> territoriesToAttack;

    //Adding arbitrary list of territories that are to be attacked and defended.
    territoriesToAttack.push_back(new Territory("Asia"));
    territoriesToAttack.push_back(new Territory("NAmerica"));
    territoriesToDefend.push_back(new Territory("SAmerica"));
    territoriesToDefend.push_back(new Territory("Europe"));

    //Adding hand of cards owned by the player
    vector<string*> cards;
    string bomb = "bomb";
    string reinforcement = "reinforcement";
    string blockade = "blockade";
    cards.push_back(&bomb);
    cards.push_back(&reinforcement);
    cards.push_back(&blockade);

    //Creating Player object.
    string playerName = "Deep";
    Player* player = new Player(playerName, territoriesToAttack, territoriesToDefend, cards);
    //Issuing orders using issueOrder() method
    player ->issueOrder("Deploy");
    player->issueOrder("Bomb");

    //Printing Player's name
    cout << "Players name is: " << player->getPlayerName() <<endl;
    //Printing all the orders issued
    cout << "All the orders are: \n";
    cout << *player->getOrderList() << endl;

    //Printing all the territories to be attacked
    vector<Territory*> toAttack = (*player).toAttack();
    cout << "Territories to be Attacked: ";
    for(int i = 0; i < toAttack.size(); i++){
        cout << toAttack[i]->getTerritoryName() << ", ";
    }
    cout << endl;

    //Printing all the territories
    vector<Territory*> toDefend = (*player).toDefend();
    cout << "Territories to be Defended: ";
    for(int i = 0; i < toDefend.size(); i++){
        cout << toDefend[i]->getTerritoryName() << ", ";
    }
    cout << endl;

}