#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include<iostream>
#include "Map.h"
#include "Player.h"
#include "Cards.h"
using namespace std;
class GameEngine{
public:
    GameEngine() = default;
    GameEngine(vector<Player*> players_list, Map* map, Deck* deck);
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
    void createPlayers();
    void reinforcementPhase(); //Assignment 2 Part 3
    void issueOrdersPhase(); //Assingment 2 Part 3
    void excuteOrderPhase(); //Assignment 2 Part 3
    vector<Player *> getPlayersList();
    Map *getMap() const;
    void setMap(Map *map);
    const vector<Player *> &getPlayerList() const;
    void setPlayerList(const vector<Player *> &playerList);
    Deck *getDeck() const;
    void setDeck(Deck *deck);
private:
    Map* map;									//initialized Map for the game
    vector<Player*> player_list;				//initialized Player Array for the gamePlayer array
    Deck* deck;

};

#endif // GAMEENGINE_H_INCLUDED


