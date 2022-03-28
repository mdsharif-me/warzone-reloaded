//
// Created by tigerrrr on 2/13/2022.
//
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "../Headers/Cards.h"
using namespace std;

class Player;
class Bomb;


//************************** * Card Class implementation * ***********************************************

/**
 * Card class parameterized constructor
 * @param type
 */
Card::Card(string type){
    if(type == "bomb")
        this->type = new cardType(bomb);
    else if(type == "reinforcement")
        this->type = new cardType(reinforcement);
    else if(type == "blockade")
        this->type = new cardType(blockade);
    else if(type == "airlift")
        this->type = new cardType(airlift);
    else if(type == "diplomacy")
        this->type = new cardType(diplomacy);
}
/**
 * Card class destructor
 */
Card::~Card() {
    delete type;
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
cardType* Card::getType() const {return type;}

/**
 * Mutator for card type
 * @param newType
 */
void Card::setType(cardType* newType) {
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
void Card::play(Player *player, Deck* deck, Territory* target) {
    // Adding the played card as an order to player's list of orders
    if (*this->type == bomb) {
        player->getOrderList()->add(new Bomb(player, target));
    } else if (*this->type == blockade) {
        player->getOrderList()->add(new Blockade(player, target));
    }
    // The card is then placed from the player's hand to the deck
    for (int i = 0; i < player->getPlayerHand()->getHandCards().size(); i++) {
        if (player->getPlayerHand()->getHandCards().at(i)->type == this->type) {
            //card = player->getPlayerHand()->getHandCards().at(i);
            //add the card to the deck
            deck->addToDeck(this);
            // remove the card from hand
            player->getPlayerHand()->removeFromHand(i);
            break;
        }
    }
}
void Card::play(Player *player, Deck* deck, Territory* start, Territory* target, int army) {
    // Adding the played card as an order to player's list of orders
    if (*this->type == airlift) {
        player->getOrderList()->add(new Airlift(player, start, target, army));
    }
    // The card is then placed from the player's hand to the deck
    for (int i = 0; i < player->getPlayerHand()->getHandCards().size(); i++) {
        if (player->getPlayerHand()->getHandCards().at(i)->type == this->type) {
            //card = player->getPlayerHand()->getHandCards().at(i);
            //add the card to the deck
            deck->addToDeck(this);
            // remove the card from hand
            player->getPlayerHand()->removeFromHand(i);
            break;
        }
    }
}
void Card::play(Player *player, Deck* deck, Territory* target, int army) {
    // Adding the played card as an order to player's list of orders
    if (*this->type == reinforcement) {
        player->getOrderList()->add(new Deploy(player, target, army));
    }
    // The card is then placed from the player's hand to the deck
    for (int i = 0; i < player->getPlayerHand()->getHandCards().size(); i++) {
        if (player->getPlayerHand()->getHandCards().at(i)->type == this->type) {
            //card = player->getPlayerHand()->getHandCards().at(i);
            //add the card to the deck
            deck->addToDeck(this);
            // remove the card from hand
            player->getPlayerHand()->removeFromHand(i);
            break;
        }
    }
}
void Card::play(Player *player, Deck* deck, Player* target) {
    // Adding the played card as an order to player's list of orders
    if (*type == diplomacy) {
        player->getOrderList()->add(new Negotiate(player, target));
    }
    // The card is then placed from the player's hand to the deck
    for (int i = 0; i < player->getPlayerHand()->getHandCards().size(); i++) {
        if (player->getPlayerHand()->getHandCards().at(i)->type == this->type) {
            //card = player->getPlayerHand()->getHandCards().at(i);
            //add the card to the deck
            deck->addToDeck(this);
            // remove the card from hand
            player->getPlayerHand()->removeFromHand(i);
            break;
        }
    }
}

string Card::printType(cardType* ct) {
    if(ct == new cardType(bomb))
        return "bomb";
    else if(ct == new cardType(reinforcement))
        return "reinforcement";
    else if(ct == new cardType(blockade))
        return "blockade";
    else if(ct == new cardType(airlift))
        return "airlift";
    else if(ct == new cardType(diplomacy))
        return "diplomacy";
    return "";
}


//************************** * Hand Class implementation * ***********************************************

/**
 * Hand class parametrized constructor
 * @param hand
 */
Hand::Hand(vector<Card *> hand) {this->handCards = move(hand);}

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

int Hand::findCard(string type) {
    cardType* findingType;
    if (type == "bomb") {
        findingType = new cardType(bomb);
    } else if (type == "reinforcement") {
        findingType = new cardType(bomb);
    } else if (type == "blockade") {
        findingType = new cardType(bomb);
    } else if (type == "airlift") {
        findingType = new cardType(bomb);
    } else if (type == "diplomacy") {
        findingType = new cardType(bomb);
    }
    for(int i = 0; i < handCards.size(); i++){
        if(handCards[i]->getType() == findingType){
            delete findingType;
            return i;
        }
    }
    return -1;
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
        throw invalid_argument("generated random number is our of vector bonds");
    }
    Card* card = deckCards.at(random);
    this->removeFromDeck(random);
    cout << "CARD PICKED BY: "<< player->getPlayerName() << ". CARD TYPE: " << card->getType();
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