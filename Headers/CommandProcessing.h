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
    Command(const Command&);
    string getCommand();
    string getEffect();
    void stringToLog(const std::string& message) override;
    Command& operator=(const Command& command);    //assignment operator
    friend ostream& operator << (ostream& os, const Command& command); //stream insertion operator
    void saveEffect(const string& effect);

private:
	string command;
	string effect;
};

class FileLineReader{
public:
    FileLineReader() = default;
    FileLineReader(const FileLineReader&);
    ~FileLineReader();
    FileLineReader(const string& filePath);
    string readLineFromFile();
    void setFilePath(const string& filePath);
    FileLineReader& operator=(const FileLineReader& fileLineReader);    //assignment operator
    friend ostream& operator << (ostream& os, const FileLineReader& fileLineReader); //stream insertion operator

private:
    string filePath;
    ifstream myFile;
};

/* This class reads commands from console */
class CommandProcessor: virtual public ILoggable, public Subject{
public:
	CommandProcessor() = default;
    CommandProcessor(CommandProcessor&);
	Command* getCommand();
    bool validate(const string& command, const string& currentState);
    void stringToLog(const std::string& message) override;
    vector<Command*> getCommandList();
    CommandProcessor& operator=(const CommandProcessor& commandProcessor);    //assignment operator
    friend ostream& operator << (ostream& os, const CommandProcessor& commandProcessor); //stream insertion operator

protected:
    virtual Command* readCommand();
    Command* saveCommand(const string& command);
private:
	vector<Command*> commandsList;
};

class FileCommandProcessorAdapter: public CommandProcessor{
public:
    FileCommandProcessorAdapter() = default;
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter&);
    FileCommandProcessorAdapter(const string& filePath);
    Command* readCommand() override;
    ~FileCommandProcessorAdapter();
    FileCommandProcessorAdapter& operator=(const FileCommandProcessorAdapter& f);    //assignment operator
    friend ostream& operator << (ostream& os, const FileCommandProcessorAdapter& f); //stream insertion operator

private:
    FileLineReader* flr;
};


