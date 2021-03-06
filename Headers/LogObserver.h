//
// Created by tigerrrr on 3/25/2022.
//

#ifndef COMP345_LOGOBSERVER_H
#define COMP345_LOGOBSERVER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Subject;
class LogObserver;

/**
 * ILoggable class definition
 */

class ILoggable {
public:
    ILoggable() = default;
    ~ILoggable() = default;
    virtual void stringToLog(const std::string& message) = 0;
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
 * Log Observer Class definition
 */
class LogObserver: public Observer{
private:
    std::string message_from_subject;
    Subject &subject;
    std::string name_of_observer;


public:
    LogObserver(Subject* subject);
    ~LogObserver() override;
    void Update(ILoggable* iLoggable) override;
    void RemoveObserverFromTheList();
    void PrintInfo();
    const std::string &getNameOfObserver() const;                         // GETTER
    void setNameOfObserver(const string &nameOfObserver);                          // SETTER
    const std::string &getMessageFromSubject() const;                     // GETTER
    void setMessageFromSubject(const string &messageFromSubject);                  // SETTER
    Subject &getSubject() const;                                     // GETTER
    void setSubject(Subject &subject);                                             // SETTER

};


/**
 * Subject class definition
 */
class Subject{
private:
    std::vector<LogObserver *> list_observer;
    std::string message;

public:
    ~Subject();
    void Attach(LogObserver *observer);
    void Detach(LogObserver *observer);
    void Notify(ILoggable* iLoggable);

    [[nodiscard]] const vector<LogObserver *> &getListObserver() const;   // GETTER
    void setListObserver(const vector<LogObserver *> &listObserver);      // SETTER
    [[nodiscard]] const std::string &getMessage() const;                    // GETTER
    void setMessage(const std::string &message);                            // SETTER
};

#endif //COMP345_LOGOBSERVER_H
