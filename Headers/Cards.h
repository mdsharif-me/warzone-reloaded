//
// Created by tigerrrr on 2/13/2022.
//

#ifndef COMP345_CARDS_H
#define COMP345_CARDS_H

#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "Player.h"
using namespace std;

enum cardType {bomb,
        reinforcement,
        blockade,
        airlift,
        diplomacy};
class Hand;
class Deck;
class Player;

/**
 * Class declaration to manage cards
 */
class Card {
private:
    //string type;
    cardType* type;

public:
    Card() = default;
    Card(string type);
    ~Card();
    void play(Player* player, Deck* deck, Territory* target);
    void play(Player* player, Deck* deck, Territory* start, Territory* target, int army);
    void play(Player* player, Deck* deck, Territory* target, int army);
    void play(Player* player, Deck* deck, Player* target);
    Card& operator = (Card *card);
    friend ostream& operator << (ostream &os, const Card &card);
    cardType* getType() const;
    void setType(cardType*);
};

/**
 * Class declaration to manage player Hand
 */
class Hand {
    vector<Card *> handCards; //Cards in Hand

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
    int findCard(string type);

};


/**
 * Class declaration to manage Deck
 */
class Deck {
private:
    vector<Card *> deckCards;

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
