/*
Author: Mohammad Shariful Islam/Deep Patel
Last updated: 22 Feb, 2022
*/
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


/* This class holds/saves the commands */
class Command {
public:
	Command(string command);
    string getCommand();
    string getEffect();
private:
	void saveEffect(string effect);
	string command;
	string effect;
};

class FileLineReader{
public:
    FileLineReader() = default;
    ~FileLineReader();
    FileLineReader(string filePath);
    string readLineFromFile();
    void setFilePath(string filePath);

private:
    string filePath;
    ifstream myFile;
};

/* This class reads commands from console */
class CommandProcessor {
public:
	CommandProcessor() = default;
	Command* getCommand();
    Command* saveCommand(string command);
    bool validate(string command, string currentState);
private:
	virtual Command* readCommand();
    string commands[6];
    string command;
	vector<Command*> commandsList;
};

class FileCommandProcessorAdapter: public CommandProcessor{
public:
    FileCommandProcessorAdapter() = default;
    FileCommandProcessorAdapter(string filePath);
    Command* readCommand();
    ~FileCommandProcessorAdapter();
private:
    FileLineReader* flr;
};


