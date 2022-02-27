#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include<iostream>
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
    void mainGameLoop();

private:
    string state;
};

#endif // GAMEENGINE_H_INCLUDED


