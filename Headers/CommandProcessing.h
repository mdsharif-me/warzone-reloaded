/*
Author: Mohammad Shariful Islam/Deep Patel
Last updated: 22 Feb, 2022
*/
#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "../Headers/LogObserver.h"

using namespace std;


/* This class holds/saves the commands */
class Command: virtual public ILoggable, public Subject{
public:
	Command(const string& command);
    string getCommand();
    string getEffect();
    void stringToLog(const std::string& message) override;
private:
	void saveEffect(const string& effect);
	string command;
	string effect;
};

class FileLineReader{
public:
    FileLineReader() = default;
    ~FileLineReader();
    FileLineReader(const string& filePath);
    string readLineFromFile();
    void setFilePath(const string& filePath);

private:
    string filePath;
    ifstream myFile;
};

/* This class reads commands from console */
class CommandProcessor: virtual public ILoggable, public Subject{
public:
	CommandProcessor() = default;
	Command* getCommand();
    Command* saveCommand(const string& command);
    bool validate(const string& command, const string& currentState);
    void stringToLog(const std::string& message) override;
private:
	virtual Command* readCommand();
    string commands[6];
    string command;
	vector<Command*> commandsList;
};

class FileCommandProcessorAdapter: public CommandProcessor{
public:
    FileCommandProcessorAdapter() = default;
    FileCommandProcessorAdapter(const string& filePath);
    Command* readCommand();
    ~FileCommandProcessorAdapter();
private:
    FileLineReader* flr;
};


