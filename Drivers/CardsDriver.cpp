//
// Created by tigerrrr on 2/13/2022.
//

#include <iostream>
#include "../Headers/Cards.h"

using namespace std;

int main() {
    Card* card1 = new Card("Bomb");
    Card* card2 = new Card("Airlift");
    const char * CardTypes[5] = {  "Blockade",  "Bomb", "Reinforcement", "Diplomacy", "airlift"};
    
    Deck* deck = new Deck();
    deck->addToDeck(card1);
    deck->addToDeck(card2);
    deck->print();
    
    //Adding 50 cards to complete the deck
    for (int i = 0; i < 50; i++)
   {
    int r = rand() % 5;
    Card *card = new Card(CardTypes[r]);
    deck->addToDeck(card);
    }
    Hand* hand = new Hand();

    deck->draw(hand);
    deck->draw(hand);

    deck->print();
    hand->print();

}


