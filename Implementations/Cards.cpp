//
// Created by tigerrrr on 2/13/2022.
//
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "../Headers/Cards.h"
#include <vector>

using namespace std;

class Player;
class Bomb;


enum cardType {bomb, reinforcement, blockade, airlift, diplomacy};
cardType aType;

//************************** * Card Class implementation * ***********************************************


/**
 * Card class parameterized constructor
 * @param type
 */
Card::Card(std::string type) {this->type = std::move(type);}

/**
 * Card class destructor
 */
Card::~Card() {
    type.clear();
}

/**
 * Assignment operator
 * @param card
 * @return
 */
Card &Card::operator=(Card *card) {
    this->type = card->type;
    return *this;
}

/**
 * Accessor for card type
 * @return
 */
std::string Card::getType() const {return type;}

/**
 * Mutator for card type
 * @param newType
 */
void Card::setType(const string & newType) {
    this->type = newType;
}

/**
 * Stream assignment operator implementation
 * @param ostream
 * @param card
 * @return
 */
ostream &operator<<(ostream &ostream, const Card &card) {
    ostream << "[";
    cout << card.getType();
    ostream << "]\n";
    return ostream;
}

/**
 * Method to add the order to the orderList, then place back the order to the deck
 * @param typeOfCard
 * @param player
 * @param hand
 * @param deck
 */
void Card::play(const std::string &typeOfCard, Player *player, Deck* deck) {
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
    for (int i = 0; i < player->getPlayerHand()->getHandCards().size(); i++) {
        if (player->getPlayerHand()->getHandCards().at(i)->type == result) {
            card = player->getPlayerHand()->getHandCards().at(i);
            // remove the card from hand
            player->getPlayerHand()->removeFromHand(i);
            //add the card to the deck
            deck->addToDeck(card);
            break;
        }
    }
}


//************************** * Hand Class implementation * ***********************************************

/**
 * Hand class parametrized constructor
 * @param hand
 */
Hand::Hand(vector<Card *> hand) {this->handCards = std::move(hand);}

/**
 * Hand destructor
 */
Hand::~Hand() = default;

/**
 * Method to return all available cards in the hand
 * @return
 */
vector<Card *> Hand::getHandCards() {
    return handCards;
}

/**
 * Method to add a card to the hand
 * @param card
 */
void Hand::addToHand(Card* card) {
    handCards.push_back(card);
}

/**
 * Method to remove a card from the hand
 * @param index
 */
void Hand::removeFromHand(int index) {
    handCards.erase(handCards.begin() + index);
}

/**
 * Assignment operator
 * @param hand
 * @return
 */
Hand &Hand::operator=(Hand *hand) {
    this->handCards = hand->handCards;
    return *this;
}

/**
 * Method to print all card in the player hand
 */
void Hand::print() {
    cout << "The Hand has the following cards:\n" << endl;
    for (int i = 0; i < handCards.size(); ++i) {
        cout << *handCards[i] << endl;
    }
}

//************************* * Deck Class Implementation * *******************************************

/**
 * Deck class parameterized constructor
 * @param dc
 */
Deck::Deck(vector<Card *> dc) { this->deckCards = dc;}

/**
 * Deck class destructor
 */
Deck::~Deck() = default;;

/**
 * Assignment operator
 * @param deck
 * @return
 */
Deck &Deck::operator=(Deck *deck) {
    this->deckCards = deck->deckCards;
    return *this;
}

/**
 * Accessor for deck vector
 * @return
 */
vector<Card *> Deck::getDeckCards() {return deckCards;}

/**
 * Mutator for deck vector
 * @param newDeckCards
 */
void Deck::setDeckCards(const vector<Card *> &newDeckCards) {
    Deck::deckCards = newDeckCards;
}

/**
 * Method to add a card to the deck
 * @param card
 */
void Deck::addToDeck(Card* card) {
    deckCards.push_back(card);
}

/**
 * Method to remove a card from the deck
 * @param index
 */
void Deck::removeFromDeck(int index) {
    deckCards.erase(deckCards.begin() + index);
}

/**
 * Method that implements draw() functionality
 * @param player
 */
void Deck::draw(Player* player) {
    int random = rand() % deckCards.size();
    if (random < 0 || random > deckCards.size()) {
        throw std::invalid_argument("generated random number is our of vector bonds");
    }

    Card* card = deckCards.at(random);
    this->removeFromDeck(random);
    player->getPlayerHand()->addToHand(card);
}

/**
 * Method to print all cards in the deck.
 */
void Deck::print() {
    cout << "The Deck has the following cards:\n" << endl;
    for (auto & deckCard : deckCards) {
        cout << *deckCard << endl;
    }
}