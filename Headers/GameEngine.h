#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include<iostream>
#include "Map.h"
#include "Player.h"
#include "Cards.h"
using namespace std;
class GameEngine{
public:
    GameEngine();
    GameEngine(const string state);
    ~GameEngine();
    string loadMap(string currentPhase);
    string validateMap(string currentPhase);
    string addPlayer(string currentPhase);
    string assignCountries(string currentPhase);
    string issueOrder(string currentPhase);
    string endIssueOrders(string currentPhase);
    string endExecOrders(string currentPhase);
    string win(string currentPhase);
    string execOrder(string currentPhase);
    string end(string currentPhase);
    string play(string currentPhase);

    void startupPhase(); //Assignment 2 Part 2
    void mainGameLoop(); //Assignment 2 Part 3

    //void reinforcementPhase(); //Assignment 2 Part 3
    //void issueOrdersPhase(); //Assignment 2 Part 3
    //void executeOrderPhase(); //Assignment 2 Part 3
    void createPlayers();
    void reinforcementPhase(); //Assignment 2 Part 3
    void issueOrdersPhase(vector<Player*>, vector<Territory*>); //Assingment 2 Part 3
    void excuteOrderPhase(); //Assignment 2 Part 3
    vector<Player *> getPlayersList();


private:
    string state;
    Map* map;									//initialized Map for the game
    MapLoader* map_loader;						//initialized MapLoader for the game
    vector<Player*> player_list;				//initialized Player Array for the gamePlayer array
    Deck* deck;

};

#endif // GAMEENGINE_H_INCLUDED


