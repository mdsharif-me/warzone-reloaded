
#include "Card.h"

#include <iostream>

#include <cstdlib>
#include <string>

#include <vector>

using std::vector;
using std::cout;
using std::endl;

using namespace std;


const char * CardTypes[5] = {
  "Blockade",
  "Bomb",
  "Reinforcement",
  "Diplomacy",
  "airlift"
};
int main() {

  Card deck;
  Card hand;
  cout << "\n Cards at deck: ";

  for (int i = 0; i < 12; i++) {
    int r = rand() % 5;
    deck.Cards.push_back(CardTypes[r]);
  }
  for (int i = 0; i < deck.Cards.size(); i++)
    cout << deck.Cards[i] << " ";

 

  cout << deck.Cards.size();

  // Taking cards to hand, from deck
  hand.Cards.push_back(deck.draw());
  hand.Cards.push_back(deck.draw());
  hand.Cards.push_back(deck.draw());

  cout << "\nCards at hand are: ";
  for (int i = 0; i < hand.Cards.size(); i++)
    cout << hand.Cards[i] << " ";
    cout << "\n Now the hand will play  \n"; 
   deck.Cards.push_back(hand.play()); 
   //Displaying cards before and after playing
   cout << "\nCards at hand are: ";
  for (int i = 0; i < hand.Cards.size(); i++)
    cout << hand.Cards[i] << " ";
    cout << "\nCards at deck are: ";
  for (int i = 0; i < deck.Cards.size(); i++)
    cout << deck.Cards[i] << " "; 
}
