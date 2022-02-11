//
// Created by deepp on 2022-02-10.
//

#ifndef UNTITLED_ORDERFORPLAYER_H
#define UNTITLED_ORDERFORPLAYER_H
#include<iostream>
#include<string>

using namespace std;

class Order{
private:
    string name;

public:
    Order();
    Order(string);
    ~Order();
    string getOrderName();
    void setOrderName(string);

};
#endif //UNTITLED_ORDERFORPLAYER_H
