//
// Created by tigerrrr on 3/25/2022.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include "../Headers/LogObserver.h"
#include "../Headers/Orders.h"
using namespace std;



/**
 * ILogger class implementation
 */


/**
 * Subject Class Implementation
 */

/**
 * Subject destructor
 */
Subject::~Subject() {
    //std::cout << "Subject deleted.\n";

}

/**
 * Method to attach an Observer
 * @param observer
 */
void Subject::Attach(LogObserver *observer){
    list_observer.push_back(observer);
}

/**
 * Method to detach an Observer
 * @param observer
 */
void Subject::Detach(LogObserver *observer) {
    std::remove(list_observer.begin(), list_observer.end(), observer );
}

/**
 * Method to Notify all Observers
 */
void Subject::Notify(ILoggable* iLoggable) {
    std::string message = "";
    for(LogObserver* logObserver: list_observer) {
        if (dynamic_cast<const Deploy*>(iLoggable) != nullptr) {
            message = "Order executed: Deploy";
        } else if (dynamic_cast<const Advance*>(iLoggable) != nullptr) {
            message = "Order executed: Advance";

        } else if (dynamic_cast<const Bomb*>(iLoggable) != nullptr) {
            message = "Order executed: Bomb";

        } else if (dynamic_cast<const Airlift*>(iLoggable) != nullptr) {
            message = "Order executed: Airlift";

        } else if (dynamic_cast<const Blockade*>(iLoggable) != nullptr) {
            message = "Order executed: Blockade";

        } else if (dynamic_cast<const Negotiate*>(iLoggable) != nullptr) {
            message = "Order executed: Negotiate";

        }


        logObserver->Update(message);
    }
}


/**
 * Getter for the list of observers
 * @return
 */
const vector<LogObserver *> &Subject::getListObserver() const {
    return list_observer;
}

void Subject::setListObserver(const vector<LogObserver *> &listObserver) {
    list_observer = listObserver;
}

/**
 * Getter for observer message
 * @return
 */
const std::string &Subject::getMessage() const {
    return message;
}

void Subject::setMessage(const std::string &message_) {
    message = message_;
}



/**
 * LogObserver class Implementation
 */

/**
 * LogObserver parametrized constructor
 * @param subject
 */
LogObserver::LogObserver(Subject &subject) : subject(subject) {
    message_from_subject = "";
    name_of_observer = "";
    this->subject.Attach(this);
}

/**
 * LogObserver Destructor
 */
LogObserver::~LogObserver() {
    //std::cout << "Observer deleted.\n";
}


/**
 * Method to update the message of LogObserver
 * @param message_from_subject
 */
void LogObserver::Update(const std::string& message_) {
    message_from_subject = message_;
    stringToLog();
    //PrintInfo();
}

/**
 * Method to remove a LogObserver from the list
 */
void LogObserver::RemoveObserverFromTheList() {
    subject.Detach(this);
}

/**
 * Method to display on screen a notification if a message is available
 */
void LogObserver::PrintInfo() {
    std::cout << "a new message is available";
}


void LogObserver::stringToLog() {
    ofstream myFile;
    myFile.open("../gamelog.txt", ios::app);
    if (myFile.is_open()) {
        myFile << this->getMessageFromSubject();
        myFile << "\n";
        myFile.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
}

/**
 * Getter for NameOfObserver
 * @return
 */
const string &LogObserver::getNameOfObserver() const {
    return name_of_observer;
}

void LogObserver::setNameOfObserver(const string &nameOfObserver) {
    name_of_observer = nameOfObserver;
}

/**
 * Getter for MessageFromSubject
 * @return
 */
const string &LogObserver::getMessageFromSubject() const {
    return message_from_subject;
}

void LogObserver::setMessageFromSubject(const string &messageFromSubject) {
    message_from_subject = messageFromSubject;
}

/**
 * Getter for Subject
 * @return
 */
Subject &LogObserver::getSubject() const {
    return subject;
}

void LogObserver::setSubject(Subject &subject_) {
    subject = subject_;
}