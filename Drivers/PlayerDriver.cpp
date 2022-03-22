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
    territoriesToAttack.push_back(new Territory("China", "Asia"));
    territoriesToAttack.push_back(new Territory("USA", "NAmerica"));
    territoriesToDefend.push_back(new Territory("Brazil", "SAmerica"));
    territoriesToDefend.push_back(new Territory("Germany", "Europe"));

    //Adding hand of cards owned by the player
    Hand * playerHand = new Hand();
    playerHand->addToHand(new Card("bomb"));
    playerHand->addToHand(new Card("reinforcement"));
    playerHand->addToHand(new Card("blockade"));

    //Creating Player object.
    string playerName = "Deep";
    Player* player = new Player(playerName, territoriesToAttack, territoriesToDefend, playerHand);
    //Issuing orders using issueOrder() method
    //player ->issueOrder("Deploy");
    //player->issueOrder("Bomb");

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

    //Printing all the card owned by players
    Hand* handOwnedByPlayer = (*player).getPlayerHand();
    vector<Card*> cardsOwnedByPlayer = handOwnedByPlayer->getHandCards();
    cout << "Cards owned: ";
    for(int i = 0; i < cardsOwnedByPlayer.size(); i++){
        cout << cardsOwnedByPlayer[i]->getType() << ", ";
    }
    cout << endl;
}