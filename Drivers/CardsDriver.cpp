//
// Created by tigerrrr on 2/13/2022.
//

#include <iostream>
#include "../Headers/Cards.h"

using namespace std;

int main() {
    Card* card1 = new Card("Bomb");
    Card* card2 = new Card("Airlift");

    Deck* deck = new Deck();
    deck->addToDeck(card1);
    deck->addToDeck(card2);
    deck->print();

    Hand* hand = new Hand();

    deck->draw(hand);
    deck->draw(hand);

    deck->print();
    hand->print();

}


