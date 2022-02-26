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

/**
 * Class declaration to manage cards
 */
class Card {
private:
    std::string type;

public:
    Card() = default;
    Card(std::string type);
    ~Card();
    void play(const std::string& type, Player* player, Deck* deck);
    Card& operator = (Card *card);
    friend ostream& operator << (ostream &os, const Card &card);
    std::string getType() const;
    void setType(const string&);

};

/**
 * Class declaration to manage player Hand
 */
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


/**
 * Class declaration to manage Deck
 */
class Deck {
private:
    std::vector<Card *> deckCards;

public:
    Deck() = default;
    Deck(vector<Card *> dc);
    ~Deck();
    Deck& operator = (Deck *deck);
    friend ostream& operator << (ostream &os, const Deck &deck);
    void draw(Player* player);
    void removeFromDeck(int);
    void addToDeck(Card*);
    void print();

    vector<Card *> getDeckCards();
    void setDeckCards(const vector<Card *> &newDeckCards);

};



#endif //COMP345_CARDS_H
