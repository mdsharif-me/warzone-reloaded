#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include "../Headers/LogObserver.h"
using namespace std;


/**
 * ILogger class implementation
 */

const string &ILoggable::getMessageToOutput() const {
    return message_to_output;
}

void ILoggable::setMessageToOutput(const string &messageToOutput) {
    message_to_output = messageToOutput;
}

/**
 * Subject Class Implementation
 */

/**
 * Subject destructor
 */
Subject::~Subject() {
    std::cout << "Subject deleted.\n";

}

/**
 * Method to attach an Observer
 * @param observer
 */
void Subject::Attach(Observer *observer){
    list_observer.push_back(observer);
}

/**
 * Method to detach an Observer
 * @param observer
 */
void Subject::Detach(Observer *observer) {
    std::remove(list_observer.begin(), list_observer.end(), observer );
}

/**
 * Method to Notify all Observers
 */
void Subject::Notify(ILoggable* iLoggable) {
    std::vector<Observer *>::iterator iterator = list_observer.begin();
    while (iterator != list_observer.end()) {
        (*iterator)->Update(iLoggable);
        ++iterator;
    }
}


/**
 * Method to create a new message and notify all observers
 * @param message
 */
void Subject::CreateMessage(ILoggable* iLoggable) {
    this->message = iLoggable->getMessageToOutput();
    Notify(iLoggable);
}


/**
 * Getter for the list of observers
 * @return
 */
const vector<Observer *> &Subject::getListObserver() const {
    return list_observer;
}

void Subject::setListObserver(const vector<Observer *> &listObserver) {
    list_observer = listObserver;
}

/**
 * Getter for observer message
 * @return
 */
const string &Subject::getMessage() const {
    return message;
}

void Subject::setMessage(const string &message_) {
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
    std::cout << "Observer deleted.\n";
}


/**
 * Method to update the message of LogObserver
 * @param message_from_subject
 */
void LogObserver::Update(ILoggable* iLoggable) {
    message_from_subject = iLoggable->getMessageToOutput();
    PrintInfo();
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
    myFile.open("gamelog.txt", ios::app);
    if (myFile.is_open()) {
        myFile << this->getMessageFromSubject();
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




