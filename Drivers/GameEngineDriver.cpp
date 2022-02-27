#include <iostream>
#include <string>
#include "../Headers/GameEngine.h"
using namespace std;

int main(){
    string currentState="start";
    string input;
    cout << "Game has started\n";
    GameEngine* g = new GameEngine();
    while (true){
        cout<<"\nCurrent state: "<< currentState << "\n";
        cout<<"Type a command: ";
        cin >> input;
        if (input=="loadmap"){
            currentState=g->loadMap(currentState);
        }else if(input=="validatemap"){
            currentState=g->validateMap(currentState);
        }else if(input=="addplayer"){
            currentState=g->addPlayer(currentState);
        }else if(input=="assigncountries"){
            currentState=g->assignCountries(currentState);
        }else if(input=="issueorder"){
            currentState=g->issueOrder(currentState);
        }else if(input=="endissueorders"){
            currentState=g->endIssueOrders(currentState);
        }else if(input=="execorder"){
            currentState=g->execOrder(currentState);
        }else if(input=="endexecorders"){
            currentState=g->endExecOrders(currentState);
        }else if(input=="win"){
            currentState=g->win(currentState);
        }else if(input=="end"){
            currentState=g->end(currentState);
            if (currentState=="exit"){
            return 0;
            }
        }else if(input=="play"){
            currentState =g->play(currentState);
        }else {
            cout<< "Invalid input\n";
        }
    }
    delete g;
}

