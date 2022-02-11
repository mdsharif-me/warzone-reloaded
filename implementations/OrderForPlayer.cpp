//
// Created by deepp on 2022-02-10.
//
#include "../headers/OrderForPlayer.h"
using namespace std;

Order::Order()
{
    string orderName;

}

Order::Order(string n)
{
    this->name = n;

}

Order::~Order()
{
    name.clear();
}

string Order::getOrderName()
{
    return name;
}

void Order::setOrderName(string n) {
    this->name = n;
}
