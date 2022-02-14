#include <iostream>
#include <string>
//#include <GameEngine.h>

using namespace std;

class start{
public:
    string state="Game has started";
};

class map_loaded{
public:
    string state="Map loaded";
};

class map_validated{
public:
    string state="Map validated";

};

class player_added{
public:
    string state="Player added";

};

class assign_reinforcement{
string state="reinforcement assigned";
};

class issue_order{
string state="order issued";
};

class execute_orders{
string state="order executed";
};

class win{
string state="Win";
};

string loadmap(string currentphase){
if (currentphase=="start"){
    //cout<< "LoadMap created";
    return "maploaded";

}else {
cout<<"Invalid";
return currentphase;
}
}

string validatemap(string currentphase){
if (currentphase=="maploaded"){
    //cout<< "map validated";
    return "mapvalidated";

}else {
cout<<"Invalid";
return currentphase;
}
}


string addplayer(string currentphase){
if (currentphase=="addplayer" || currentphase=="mapvalidated"){
    //cout<< "players added";
    return "playersadded";

}else {
cout<<"Invalid";
return currentphase;
}
}

string assigncountries(string currentphase){
if (currentphase=="addplayer"){
    //cout<< "assign reinforcement";
    return "assignreinforcement";

}else {
cout<<"Invalid";
return currentphase;
}
}

string issueorder(string currentphase){
if (currentphase=="assigncountries"){
    //cout<< "issue orders";
    return "issueorder";

}else {
cout<<"Invalid";
return currentphase;
}
}

string endissueorders(string currentphase){
if (currentphase=="issueorder"){
    //cout<< "execute orders";
    return "executeorders";

}else {
cout<<"Invalid";
return currentphase;
}
}

string endexecorders(string currentphase){
if (currentphase=="endissueorders" ){
    //cout<< "execute orders";
    return "executeorders";

} else {
cout<<"Invalid";
return currentphase;
}
}

string execorder(string currentphase){
if (currentphase=="executeorders" ){
    //cout<< "execute orders";
    return "executeorders";

}else {
cout<<"Invalid";
return currentphase;
}
}

string win(string currentphase){
if (currentphase=="execorder"){
    //cout<< "win";
    return "win ";

}else {
cout<<"Invalid";
return currentphase;
}
}
string end(string currentphase){
if (currentphase=="win"){
    //cout<< "end";
    return "end ";

}else {
cout<<"Invalid";
return currentphase;
} }

string play(string currentphase){
if (currentphase=="win"){
    //cout<< "end";
    return "start";

}else {
cout<<"Invalid";
return currentphase;
}

}








