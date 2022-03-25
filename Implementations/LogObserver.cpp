#include <iostream>
#include <fstream>
#include <string>
#include "../Headers/LogObserver.h"
#include "../Headers/LogObserver.h"
using namespace std;

LogObserver::LogObserver() = default;


 Subject:: Subject() = default;
 
 void Subject:: notify(Illogable* illogable){
 	Observer(illogable);
 }
 
   Observer:: Observer(Illogable* illogable){
      this.update(illogable);  	
   } 
   
   Observer:: update(Illogable* illogable){
   	 illogable.stringToLog();
   }
   
   Iloggable:: Illogable() = default;
   
   Iloggable:: stringToLog(){
   	 ofstream myfile ("log.txt");
  if (myfile.is_open())
  {
    myfile << &this;
    myfile.close();
  }
   else
   {
   	myfile.open ("log.txt");
   	 stringToLog();
   }
   }
