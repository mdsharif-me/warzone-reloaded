
#ifndef COMP345_LOGOBSERVER_H
#define COMP345_LOGOBSERVER_H

 #include <iostream>
 #include <fstream>
#include <string>
//#include "...Implementations/GameEngine.cpp"

using namespace std;

/**
 * ILoggable class definition
 */

class ILoggable {
private:
    std::string message_to_output;

public:
    ILoggable() = default;
    ~ILoggable() = default;
    virtual void stringToLog() = 0;

    [[nodiscard]] const string &getMessageToOutput() const;                     // GETTER
    void setMessageToOutput(const string &messageToOutput);                     // SETTER
};


/**
 * Observer interface
 */
 class Observer {
 public:
     virtual ~Observer()= default;;
     virtual void Update(ILoggable* iLoggable) = 0;
 };

 /**
  * ISubject Interface
  */
 class ISubject {
 public:
     virtual ~ISubject()= default;;
     virtual void Attach(Observer *observer) = 0;
     virtual void Detach(Observer *observer) = 0;
     virtual void Notify(ILoggable* iLoggable) = 0;
 };

 /**
  * Subject class definition
  */
 class Subject : public ISubject{
 private:
     std::vector<Observer *> list_observer;
     std::string message;

 public:
     ~Subject() override;
     void Attach(Observer *observer) override;
     void Detach(Observer *observer) override;
     void Notify(ILoggable* iLoggable) override;
     void CreateMessage(ILoggable* iLoggable);

     [[nodiscard]] const vector<Observer *> &getListObserver() const;   // GETTER
     void setListObserver(const vector<Observer *> &listObserver);      // SETTER
     [[nodiscard]] const string &getMessage() const;                    // GETTER
     void setMessage(const string &message);                            // SETTER
 };

 /**
  * Log Observer Class definition
  */
 class LogObserver: public Observer, public ILoggable{
 private:
     std::string message_from_subject;
     Subject &subject;
     std::string name_of_observer;


 public:
     explicit LogObserver(Subject &subject);
     ~LogObserver() override;
     void Update(ILoggable* iLoggable) override;
     void RemoveObserverFromTheList();
     void PrintInfo();
     void stringToLog() override;
     [[nodiscard]] const string &getNameOfObserver() const;                         // GETTER
     void setNameOfObserver(const string &nameOfObserver);                          // SETTER
     [[nodiscard]] const string &getMessageFromSubject() const;                     // GETTER
     void setMessageFromSubject(const string &messageFromSubject);                  // SETTER
     [[nodiscard]] Subject &getSubject() const;                                     // GETTER
     void setSubject(Subject &subject);                                             // SETTER

 };

#endif // COMP345_LOGOBSERVER_H
