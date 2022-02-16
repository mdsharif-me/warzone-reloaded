#include <iostream>
#include <string>
#include "GameEngine.h"
using namespace std;

//class
GameEngine::GameEngine(){
this->state=state[0];
}

//commands
string state[]= {"start","maploaded","mapvalidated","playersadded","assignreinforcement","issueorders","executeorders","win"};


//functions
string loadmap(string currentphase){
if (currentphase==state[0]|| currentphase==state[1]){
    cout<< "Map loaded"; // success msg
    return state[1]; // new currentphase return
} else {
    cout<< "Error: This command is not available at this stage."; // error message
return currentphase;
}
}

//functions
string validatemap(string currentphase){
if (currentphase==state[1]){
    cout<< "map validated";
    return state[2];

}else {
cout<<"Error: This command is not available at this stage.";
return currentphase;
}
}


//functions
string addplayer(string currentphase){
if (currentphase == state[2]||currentphase == state[3]){
    cout<< "players added";
    return state[3];

}else {
cout<<"Error: This command is not available at this stage.";
return currentphase;
}
}

//functions
string assigncountries(string currentphase){
if (currentphase == state[3]||currentphase == state[6]){
    cout<< "assign reinforcement";
    return state[4];

}else {
cout<<"Error: This command is not available at this stage.";
return currentphase;
}
}

//functions
string issueorder(string currentphase){
if (currentphase==state[4]|| currentphase == state[5]){
    cout<< "issue orders";
    return state[5];

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}
}

//functions
string endissueorders(string currentphase){
if (currentphase==state[5]||currentphase == state[6]){
    cout<< "execute orders";
    return state[6];

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}
}

//functions
string execorder(string currentphase){
if (currentphase==state[6] ){
    cout<< "execute orders";
    return state[6];

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}
}

//functions
string endexecorders(string currentphase){
if (currentphase==state[6] ){
    cout<< "execute orders";
    return state[4];

} else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}
}


//functions
string win(string currentphase){
if (currentphase==state[6]){
    cout<< "win";
    return state[7];

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}
}

//functions
string end(string currentphase){
if (currentphase==state[7]){
    cout<< "The end";
    return "exit";

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
} }

//functions
string play(string currentphase){
if (currentphase==state[7]){
    cout<< "Play again";
    return state[0];

}else {
cout<<"Error: This command is not available at this stage";
return currentphase;
}

}









