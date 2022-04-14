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

Command::Command(const Command& c) {
    this->command = c.command;
    this->effect = c.effect;
}

Command &Command::operator=(const Command &command) {
    this->command = command.command;
    this->effect = command.effect;
    return *this;
}

ostream &operator<<(ostream &os, const Command &command) {
    os << "Command Name: " << command.command << endl;
    return os;
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
                cout << "COMMAND VALIDATION: true, STATE: " << currentState << endl;
				return true;
			}else {
                cout << "COMMAND VALIDATION: false, STATE: " << currentState << endl;
                return false;
            }
		}
	}
    if(command.find("tournament") != string::npos && currentState == "start"){
        return true;
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

vector<Command *> CommandProcessor::getCommandList() {
    return this->commandsList;
}

CommandProcessor::CommandProcessor(CommandProcessor& cp) {
    this->commandsList = cp.commandsList;
}

CommandProcessor &CommandProcessor::operator=(const CommandProcessor &commandProcessor) {
    this->commandsList = commandProcessor.commandsList;
    return *this;
}

ostream &operator<<(ostream &os, const CommandProcessor &commandProcessor) {
    for(auto c: commandProcessor.commandsList) {
        os << "Command name: " << c->getCommand() << endl;
    }
    return os;
}


/**
 *  FileComandProcessorAdapter class Implementation
 *
 */
Command* FileCommandProcessorAdapter::readCommand() {
    string command = this->flr->readLineFromFile();
    cout<< "COMMAND READ FROM THE FILE: " << command << endl;
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

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter& fAdapter) {
    this->flr = fAdapter.flr;
}

FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &f) {
    this->flr = f.flr;
    return *this;
}

ostream &operator<<(ostream &os, const FileCommandProcessorAdapter &f) {
    os << "File Reader for: " << f.flr;
    return os;
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

FileLineReader::FileLineReader(const FileLineReader& f) {
    this->filePath = f.filePath;
}

FileLineReader &FileLineReader::operator=(const FileLineReader &fileLineReader) {
    this->filePath = fileLineReader.filePath;
    return *this;
}

ostream &operator<<(ostream &os, const FileLineReader &fileLineReader) {
    os << "The file path: " << fileLineReader.filePath;
    return os;
}
