#include <iostream>
#include <string>
#include "../Headers/GameEngine.h"
using namespace std;

//class
GameEngine::GameEngine(){
    this->state=state[0];
}

//commands
string states[]= {"start","maploaded","mapvalidated","playersadded","assignreinforcement","issueorders","executeorders","win"};


//functions
string GameEngine::loadMap(string currentPhase){
    if (currentPhase == states[0]|| currentPhase == states[1]){
        cout<< "Map loaded"; // success msg
        return states[1]; // new currentPhase return
    }
    else {
        cout<< "Error: This command is not available at this stage."; // error message
        return currentPhase;
    }
}

//functions
string GameEngine::validateMap(string currentPhase){
    if (currentPhase==states[1]){
        cout<< "map validated";
        return states[2];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}


//functions
string GameEngine::addPlayer(string currentPhase){
    if (currentPhase == states[2]||currentPhase == states[3]){
        cout<< "players added";
        return states[3];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}

//functions
string GameEngine::assignCountries(string currentPhase){
    if (currentPhase == states[3]||currentPhase == states[6]){
        cout<< "assign reinforcement";
        return states[4];
    }
    else {
        cout<<"Error: This command is not available at this stage.";
        return currentPhase;
    }
}

//functions
string GameEngine::issueOrder(string currentPhase){
    if (currentPhase == states[4]|| currentPhase == states[5]){
        cout<< "issue orders";
        return states[5];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::endIssueOrders(string currentPhase){
    if (currentPhase == states[5]||currentPhase == states[6]){
        cout<< "execute orders";
        return states[6];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::execOrder(string currentPhase){
    if (currentPhase == states[6] ){
        cout<< "execute orders";
        return states[6];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::endExecOrders(string currentPhase){
    if (currentPhase == states[6] ){
        cout<< "execute orders";
        return states[4];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}


//functions
string GameEngine::win(string currentPhase){
    if (currentPhase == states[6]){
        cout<< "win";
        return states[7];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::end(string currentPhase){
    if (currentPhase == states[7]){
        cout<< "The end";
        return "exit";
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}

//functions
string GameEngine::play(string currentPhase){
    if (currentPhase == states[7]){
        cout<< "Play again";
        return states[0];
    }
    else {
        cout<<"Error: This command is not available at this stage";
        return currentPhase;
    }
}









