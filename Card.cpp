#include <iostream>
#include <iomanip>

#include "Card.h"

#include <cstdlib>

#include <string>

#include <vector>

using std::vector;
using std::cout;
using std::endl;
class Card {
  public:
    vector <string> Cards;

 

};
Card deck;
Card hand;

string draw() {
  int r2 = rand() % Cards.size();
  
  string a = Cards[r2];
  //pointer to string for future use
  string *c = &a;
  Cards.erase(Cards.begin() + r2);
  return a;
}
string play() {
  string b = Cards[0];
  
    cout << "\n Played card: " << b;
  Cards.erase(Cards.begin());
  return b;
}

