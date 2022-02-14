//
// Created by tigerrrr on 2/13/2022.
//

#ifndef COMP345_CARDS_H
#define COMP345_CARDS_H

#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Orders.h"

using namespace std;

//enum cardType {bomb, reinforcement, blockade, airlift, diplomacy};
class Hand;
class Deck;

class Card {
private:
    std::string type;

public:
    Card() = default;
    Card(std::string type);
    ~Card();
    void play(const std::string& type, Player* player, Hand* hand, Deck* deck);
    Card& operator = (Card *card);
    friend ostream& operator << (ostream &os, const Card &card);
    std::string getType() const;

};

class Hand {
    std::vector<Card *> handCards;


public:
    Hand() = default;
    Hand(vector<Card *> hand);
    ~Hand();
    vector<Card *> getHandCards();
    Hand& operator = (Hand *hand);
    friend ostream& operator << (ostream &os, const Hand &hand);
    void removeFromHand(int);
    void addToHand(Card* card);
    void print();


};


class Deck {
private:
    std::vector<Card *> deckCards;

public:
    Deck() = default;
    Deck(vector<Card *> dc);
    ~Deck();
    vector<Card *> getDeckCards();
    Deck& operator = (Deck *deck);
    friend ostream& operator << (ostream &os, const Deck &deck);
    void draw(Hand* hand);
    void removeFromDeck(int);
    void addToDeck(Card*);
    void print();

};



#endif //COMP345_CARDS_H
