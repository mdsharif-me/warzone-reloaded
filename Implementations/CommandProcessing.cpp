#include "../Headers/CommandProcessing.h"

/**
 *  Command class Implementation
 *
 */
Command::Command(const string& command) {
	this->command = command;
}
string Command::getCommand() {
    return this->command;
}
string Command::getEffect() {
    return this->effect;
}
void Command::saveEffect(const string& effect) {
    this->effect = effect;
    Subject* subject = new Subject;
    LogObserver* logObserver = new LogObserver(subject);
    subject->setMessage("Command's effect: " + this->getEffect());
    subject->Notify(this);
    delete logObserver;
    delete subject;
    logObserver = nullptr;
    subject = nullptr;
}

void Command::stringToLog(const string &message) {
    ofstream myFile;
    myFile.open("../gamelog.txt", ios::app);
    if (myFile.is_open()) {
        myFile << message;
        myFile << "\n";
        myFile.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
}

/**
 *  CommandProcessor class Implementation
 *
 */
Command* CommandProcessor::readCommand() {
	string userInput;
	cout << "\nType a command: ";
	getline(cin, userInput);
    return this->saveCommand(userInput);
}
Command* CommandProcessor::saveCommand(const string& command) {
    Command* c = new Command(command);
	commandsList.push_back(c);
    Subject* subject = new Subject;
    LogObserver* logObserver = new LogObserver(subject);
    subject->setMessage("Command: " + command);
    subject->Notify(this);
    delete logObserver;
    delete subject;
    logObserver = nullptr;
    subject = nullptr;
    return c;
}
Command* CommandProcessor::getCommand() {
    return readCommand();
}
// Check if a command is valid, and if it's allowed in the current state
bool CommandProcessor::validate(const string& command,const string& currentState) {
	string validCommands[6] = { "loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit" };
	string gameStates[5] = { "start", "maploaded", "mapvalidated", "playersadded", "win" };
	int validIn[6][2] = { {0, 1},{1, 1},{2, 3},{3, 3},{4, 4},{4, 4} };
	for (int i = 0; i < 6; i++) {
		// if the command is one of the valid commands...
		if (command.find(validCommands[i]) != string::npos) {
			// if the command allowed in current state...
			if (!currentState.compare(gameStates[validIn[i][0]]) || !currentState.compare(gameStates[validIn[i][1]])) {
                cout << "COMMAND VALIDATION: true" << endl;
				return true;
			}else {
                cout << "COMMAND VALIDATION: false" << endl;
                return false;
            }
		}
	}
	return false;
}

void CommandProcessor::stringToLog(const string &message) {
    ofstream myFile;
    myFile.open("../gamelog.txt", ios::app);
    if (myFile.is_open()) {
        myFile << message;
        myFile << "\n";
        myFile.close();
    } else {
        cout << "Unable to open the file" << endl;
    }
}


/**
 *  FileComandProcessorAdapter class Implementation
 *
 */
Command* FileCommandProcessorAdapter::readCommand() {
    string command = this->flr->readLineFromFile();
    if (command == "No command found in the file") {
        cout << command << endl;
        return nullptr;
    }
    else {
        return this->saveCommand(command);
    }
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const string& filePath) {
    flr = new FileLineReader(filePath);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
}

/**
 *  FileLineReader class Implementation
 *
 */

FileLineReader::FileLineReader(const string& filePath) {
    this->myFile.open(filePath);
    if(myFile.is_open()){
        cout << "Successfully opened command file!" << endl;
    }
    else{
        cout << "Failed to open command file" << endl;
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


void FileLineReader::setFilePath(const string& filePath) {
    this->filePath = filePath;
}
