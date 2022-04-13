#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include<iostream>
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "CommandProcessing.h"
using namespace std;
class GameEngine : virtual public ILoggable, public Subject{
public:
    GameEngine() = default;
    GameEngine(vector<Player*> players_list, Map* map, Deck* deck);
    ~GameEngine();
    GameEngine(const GameEngine&);
    void startupPhase(CommandProcessor* cp); //Assignment 2 Part 2
    void mainGameLoop(int); //Assignment 2 Part 3
    void reinforcementPhase(); //Assignment 2 Part 3
    void issueOrdersPhase(); //Assingment 2 Part 3
    void executeOrderPhase(); //Assignment 2 Part 3
    void clear();
    void setState(const string& state_);
    string getState();
    vector<Player *> getPlayersList();
    Map *getMap() const;
    void setMap(Map *map);
    void setPlayerList(const vector<Player *> &playerList);
    Deck *getDeck() const;
    void setDeck(Deck *deck);
    GameEngine& operator=(const GameEngine& gameEngine);    //assignment operator
    friend ostream& operator << (ostream& os, const GameEngine& gameEngine); //stream insertion operator for Player
    void stringToLog(const std::string& message) override;
    void transition(const string& state_);
    void addPlayer(string command, string strategy);
    void loadAndValidateMap(string& path);
    void gameStart(int);
    void results(vector<vector<string>>);

private:
    Map* map;									//initialized Map for the game
    vector<Player*> player_list;				//initialized Player Array for the gamePlayer array
    Deck* deck;
    string state;
};
#endif // GAMEENGINE_H_INCLUDED