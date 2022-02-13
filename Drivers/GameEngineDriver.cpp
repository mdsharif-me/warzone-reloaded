#include <iostream>
#include <string>
#include "GameEngine.h"

using namespace std;

int main(){
    string currentphase= "start";
    string input;
    cout << "Game has started\n";
    cin >> input;


    if (input=="loadmap"){
        cout <<"Map loaded\n";
        currentphase=loadmap(currentphase);

    }else if(input=="validatemap"){
         cout <<"Map validated\n";
         currentphase=validatemap(currentphase);


    }else if(input=="addplayer"){
         cout <<"players added\n";
         currentphase=addplayer(currentphase);


    }else if(input=="assigncountries"){
         cout <<"assign reinforcement\n";
         currentphase=assigncountries(currentphase);

    }else if(input=="issueorder"){
         cout <<"issue orders\n";
         currentphase=issueorder(currentphase);


    }else if(input=="endissueorders"){
         cout <<"execute orders\n";
         currentphase=endissueorders(currentphase);

    }else if(input=="execorder"){
         cout <<"execute orders\n";
         currentphase=execorder(currentphase);

    }else if(input=="endexecorders"){
         cout <<"assign reinforcement\n";
         currentphase=endexecorders(currentphase);

    }else if(input=="win"){
         cout <<"win\n";
         currentphase=win(currentphase);

    }else if(input=="end"){
         cout <<"Program Ended";
         currentphase=end(currentphase);

    }else if(input=="play"){
         cout <<"Started again\n";
         currentphase=play(currentphase);

    }else {
        cout<< "Invalid input\n";

    }

}
