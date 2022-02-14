//
// Created by tigerrrr on 2/13/2022.
//
#include <iostream>
#include <vector>
#include <string>
#include "../Headers/Cards.h"
#include <vector>

using namespace std;

class Player;
class Bomb;
enum cardType {bomb, reinforcement, blockade, airlift, diplomacy};
cardType aType;

/**
 * Card Class Implementation
 *
 */

Card::Card(std::string type) {this->type = type;}
Card::~Card() {
    type.clear();
}

Card &Card::operator=(Card *card) {
    this->type = card->type;
    return *this;
}

std::string Card::getType() const {return type;}

ostream &operator<<(ostream &ostream, const Card &card) {
    ostream << "[";
    cout << card.getType();
    ostream << "]\n";
    return ostream;

}

/**
 * Method to add the order to the orderList, then place back the order to the deck
 */
void Card::play(const std::string &typeOfCard, Player *player, Hand* hand, Deck* deck) {
    string result;
    if (type == to_string(bomb)) {
        player->getOrderList()->add(new Bomb());
        result = to_string(bomb);
    } else if (type == to_string(reinforcement)) {
        player->getOrderList()->add(new Deploy());
    } else if (type == to_string(blockade)) {
        player->getOrderList()->add(new Blockade());

    } else if (type == to_string(airlift)) {
        player->getOrderList()->add(new Airlift());

    } else if (type == to_string(diplomacy)) {
        player->getOrderList()->add(new Negotiate());

    } else {
        player->getOrderList()->add(nullptr);

    }

    Card* card;
    for (int i = 0; i < hand->getHandCards().size(); i++) {
        if (hand->getHandCards().at(i)->type == result) {
            card = hand->getHandCards().at(i);
            // remove the card from hand
            hand->removeFromHand(i);
            //add the card to the deck
            deck->addToDeck(card);
            break;
        }
    }
}



Hand::Hand(vector<Card *> hand) {this->handCards = hand;}
Hand::~Hand() {}

vector<Card *> Hand::getHandCards() {
    return handCards;
}


void Hand::addToHand(Card* card) {
    handCards.push_back(card);
}
void Hand::removeFromHand(int index) {
    handCards.erase(handCards.begin() + index);
}

Hand &Hand::operator=(Hand *hand) {
    this->handCards = hand->handCards;
    return *this;
}

void Hand::print() {
    cout << "The Hand has the following cards:\n" << endl;
    for (int i = 0; i < handCards.size(); ++i) {
        cout << *handCards[i] << endl;
    }
}


/**
 * Deck Class Implementation
 */
Deck::Deck(vector<Card *> dc) { this->deckCards = dc;}
Deck::~Deck() {};

Deck &Deck::operator=(Deck *deck) {
    this->deckCards = deck->deckCards;
    return *this;
}

vector<Card *> Deck::getDeckCards() {return deckCards;}

void Deck::addToDeck(Card* card) {
    deckCards.push_back(card);
}
void Deck::removeFromDeck(int index) {
    deckCards.erase(deckCards.begin() + index);
}

void Deck::draw(Hand* hand) {
    int random = rand() % deckCards.size();
    if (random < 0 || random > deckCards.size()) {
        throw std::invalid_argument("generated random number is our of vector bonds");
    }

    Card* card = deckCards.at(random);
    this->removeFromDeck(random);
    hand->addToHand(card);
}

void Deck::print() {
    cout << "The Deck has the following cards:\n" << endl;
    for (int i = 0; i < deckCards.size(); ++i) {
        cout << *deckCards[i] << endl;
    }
}