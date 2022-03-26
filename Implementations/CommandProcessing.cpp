#include "../Headers/CommandProcessing.h"

/**
 *  Command class Implementation
 *
 */
Command::Command(string command) {
	this->command = command;
}
string Command::getCommand() {
    return this->command;
}
string Command::getEffect() {
    return this->effect;
}
void Command::saveEffect(string effect) {
    this->effect = effect;
}

/**
 *  CommandProcessor class Implementation
 *
 */
void CommandProcessor::readCommand() {
	string userInput;
	cout << "\nType a command: ";
	cin >> userInput;
	this->saveCommand(userInput);
}
void CommandProcessor::saveCommand(string command) {
	commandsList.push_back(new Command(command));
}
Command* CommandProcessor::getCommand() {
    readCommand();
}
// Check if a command is valid, and if it's allowed in the current state
bool CommandProcessor::validate(string command, string currentState) {
	string validCommands[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
	string gameStates[5] = { "start", "maploaded", "mapvalidated", "playersadded", "win" };
	int validIn[6][2] = { {0, 1},{1, 1},{2, 3},{3, 3},{4, 4},{4, 4} };

	for (int i = 0; i < 6; i++) {
		// if the command is one of the valid commands..
		if (!command.compare(validCommands[i])) {
			// if the command allowed in current state..
			if (!currentState.compare(gameStates[validIn[i][0]]) || !currentState.compare(gameStates[validIn[i][1]])) {
				return true;
			}
			else { return false; }
		}
	}
	return false;
}


/**
 *  FileComandProcessorAdapter class Implementation
 *
 */
void FileCommandProcessorAdapter::readCommand() {
    string command = this->flr->readLineFromFile();
    if (command == "No command found in the file") {
        cout << command << endl;
    } else {
        this->saveCommand(command);
    }
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filePath) {
    flr = new FileLineReader(filePath);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
}

/**
 *  FileLineReader class Implementation
 *
 */

FileLineReader::FileLineReader(string filePath) {
    this->myFile.open(filePath);
    if(myFile.is_open()){
        cout << "Successfully opened command file!" << endl;
    }
    else{
        cout << "failed to open command file" << endl;
    }
}

string FileLineReader::readLineFromFile() {
    string line;
    if(getline(myFile,line)){
        return line;
    }
    else{
        return "No command found in the file";
    }
}

FileLineReader::~FileLineReader() {
    myFile.close();
}


void FileLineReader::setFilePath(string filePath) {
    this->filePath = filePath;
}
