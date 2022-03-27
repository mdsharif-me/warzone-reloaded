/*
Author: Mohammad Shariful Islam/Deep Patel
Last updated: 22 Feb, 2022
*/
#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

string commands[6]; // the commands in the game

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

/* This class reads commands from console */
class CommandProcessor {
public:
	CommandProcessor() = default;
	Command* getCommand();
    void saveCommand(string command);
private:
	virtual void readCommand();
	bool validate(string command, string currentState);
	string command;
	vector<Command*> commandsList;
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

using namespace std;

class FileCommandProcessorAdapter: public CommandProcessor{
public:
    FileCommandProcessorAdapter() = default;
    FileCommandProcessorAdapter(string filePath);
    void readCommand() override;
    ~FileCommandProcessorAdapter();
private:
    FileLineReader* flr;
};


