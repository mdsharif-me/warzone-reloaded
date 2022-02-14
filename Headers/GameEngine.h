#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include<iostream>

using namespace std;

string loadmap(string currentphase);
string validatemap(string currentphase);
string addplayer(string currentphase);
string assigncountries(string currentphase);
string issueorder(string currentphase);
string endissueorders(string currentphase);
string endexecorders(string currentphase);
string win(string currentphase);
string execorder(string currentphase);
string end(string currentphase);
string play(string currentphase);





#endif // GAMEENGINE_H_INCLUDED


