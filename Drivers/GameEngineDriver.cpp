#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

int main(){
    string currentState="start";
    string input;
    cout << "Game has started\n";

    while (true){
        cout<<"\nCurrent state: "<< currentState << "\n";
            cout<<"Type a command: ";
    cin >> input;
    if (input=="loadmap"){
        currentState=loadmap(currentState);

    }else if(input=="validatemap"){
         currentState=validatemap(currentState);


    }else if(input=="addplayer"){
         currentState=addplayer(currentState);


    }else if(input=="assigncountries"){
        currentState=assigncountries(currentState);

    }else if(input=="issueorder"){
         currentState=issueorder(currentState);


    }else if(input=="endissueorders"){
         currentState=endissueorders(currentState);

    }else if(input=="execorder"){
        currentState=execorder(currentState);

    }else if(input=="endexecorders"){
        currentState=endexecorders(currentState);

    }else if(input=="win"){
         currentState=win(currentState);

    }else if(input=="end"){
         currentState=end(currentState);
         if (currentState=="exit"){
            return 0;
         }

    }else if(input=="play"){
         currentState = play(currentState);

    }else {
        cout<< "Invalid input\n";
    }

}

}

