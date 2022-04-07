//
// Created by deepp on 2022-03-31.
//
#include "../Headers/PlayerStrategies.h"
using namespace std;


PlayerStrategy::PlayerStrategy(Player *p) {
    this->player = p;
}
PlayerStrategy::PlayerStrategy(const PlayerStrategy &copy){
    this->player = copy.player;
}
void PlayerStrategy::setPlayer(Player *p) {
    this->player = p;
}
Player * PlayerStrategy::getPlayer() const {
    return this->player;
}
PlayerStrategy::~PlayerStrategy() {
    delete this->player;
}
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy &ps) {
    this->player = ps.player;
    return *this;
}
bool PlayerStrategy::isStartOfGame() {
    for(auto territory: this->player->getTerritories()){
        if(territory->getArmyCount() == 0){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}
ostream &operator<<(ostream &os, PlayerStrategy &ps)
{
    os << "Player strategy: " << ps.getPlayer()->getPlayerName() << endl;
    return os;
}

/**
 * Implementation of Human class
 */
Human::Human(Player *player) : PlayerStrategy(player) {}
Human::Human(const Human &h) : PlayerStrategy(h) {}
Human::~Human() {}
void Human::issueOrder(Deck* deck, vector<Player*> players_list) {
    toDefend();
    toAttack();
    cout << "Territories to Defend in priority. " << endl;
    cout << "Please deploy Army to each territory:" << endl;
    int tempArmy;
    do{
        tempArmy = this->getPlayer()->getReinforcementPool(); //Getting player
        if(tempArmy==0) {
            cout << "No more armies to deploy!";
            break;
        }
        cout << "Be sure to deploy all your armies to be able to issue other orders" << endl;
        for(Territory* territory: this->getPlayer()->toDefend()) {
            cout << "Available number of Deployable Army: " << tempArmy << endl;
            cout << territory->getTerritoryName() << ":" << endl;
            int numberOfArmies; cin >> numberOfArmies;
            if (numberOfArmies <= tempArmy) {
                // int index = this->playerHand->findCard("reinforcement");
                // playing the card from hand
                //if(index != this->playerHand->getHandCards().size())
                //    playerHand->getHandCards()[index]->play(this, deck, territory, numberOfArmies);
                Deploy *deploy = new Deploy(this->getPlayer(), territory, numberOfArmies);
                this->getPlayer()->getOrderList()->add(deploy);
                tempArmy = tempArmy - numberOfArmies;
                //else
                //cout << "You do not have any reinforcement cards!" << endl;
            }
            else{
                cout << "Sorry you do not have enough Army to Deploy" << endl;
            }
        }
    }
    while (tempArmy!=0);
    cout << "Deployment Order is complete, now other orders can be issued" << endl;
    // Other orders
    cout << "Available Orders: Advance, Bomb, Airlift, Blockade, Negotiate" << endl;
    while(true) {
        cout << "Select your next order (type 'end' to end your turn)." << endl;
        string orderString; cin >> orderString;
        if (orderString == "end"){
            cout << "Your turn has now ended." << endl;
            break;
        }
        else if (orderString == "Advance") {
            cout << "Select the source territories number from the following territories" << endl;
            for (int i = 0; i < this->getPlayer()->toDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->toDefend()[i]->getTerritoryName() << endl;
            }
            int sourceIndex;
            cin >> sourceIndex;
            vector<Territory *> adjacentTerritories;
            if (sourceIndex < this->getPlayer()->toDefend().size() && sourceIndex >= 0) {
                adjacentTerritories = this->getPlayer()->toDefend()[sourceIndex]->getAdjTerritories();
                cout << "Select the adjacent territories number to which the army should be moved to." << endl;
                for (int i = 0; i < adjacentTerritories.size(); i++) {
                    cout << i << ": " << adjacentTerritories[i]->getTerritoryName() << endl;
                }
                int targetIndex;
                cin >> targetIndex;
                if (targetIndex < adjacentTerritories.size() && targetIndex >= 0) {
                    cout << "Enter number of armies (" << this->getPlayer()->toDefend()[sourceIndex]->getArmyCount() << "):" << endl;
                    int armynum;
                    cin >> armynum;
                    if (armynum >= 0) {
                        //Advance does not require a card.
                        auto *advance = new Advance(this->getPlayer(), this->getPlayer()->toDefend()[sourceIndex],
                                                    adjacentTerritories[targetIndex], armynum);
                        this->getPlayer()->getOrderList()->add(advance);
                    }
                    else{
                        cout << "Invalid number of armies" << endl;
                    }
                }
            }
        }
        else if (orderString == "Bomb") {
            cout << "Select the target territories number from the following territories" << endl;
            for (int i = 0; i < this->getPlayer()->toAttack().size(); i++) {
                cout << i << ": " << this->getPlayer()->toAttack()[i]->getTerritoryName() << endl;
            }
            int indexToBomb;
            cin >> indexToBomb;
            if (indexToBomb < this->getPlayer()->toAttack().size() && indexToBomb >= 0) {
                string bomb = "bomb";
                int index = this->getPlayer()->getPlayerHand()->findCard(bomb);
                // playing the card from hand
                if(index != -1)
                    // the order is issued by the play method in card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    this->getPlayer()->toAttack()[indexToBomb]);
                    //Bomb *bomb = new Bomb(this, this->toAttack()[indexToBomb]);
                    //orderList->add(bomb);
                else
                    cout << "You do not have any bomb cards!" << endl;
            } else {
                cout << "Invalid Bomb order" << endl;
            }
        }
        else if(orderString == "Airlift"){
            cout << "Select the source and target territories number from the following territories" << endl;
            for (int i = 0; i < this->getPlayer()->toDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->toDefend()[i]->getTerritoryName() << endl;
            }
            int indexToAirliftFrom;
            cout << "From: " << endl;
            cin >> indexToAirliftFrom;
            int indexToAirliftTo;
            cout << "To: " << endl;
            cin >> indexToAirliftTo;
            int armyNo;
            cout << "Number of army " << endl;
            cin >> armyNo;
            if (indexToAirliftFrom < this->getPlayer()->toDefend().size() && indexToAirliftFrom >= 0 &&
                indexToAirliftTo < this->getPlayer()->toDefend().size() && indexToAirliftTo >= 0 && armyNo >= 0) {
                string airlift = "airlift";
                int index = this->getPlayer()->getPlayerHand()->findCard(airlift);
                // playing the card from hand
                if(index != -1)
                    // the order is issued in the play method on card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    this->getPlayer()->toDefend()[indexToAirliftFrom],
                                                                                    this->getPlayer()->toDefend()[indexToAirliftTo],
                                                                                    armyNo);
                    //auto *airlift = new Airlift(this, this->toDefend()[indexToAirliftFrom],
                    //                            this->toDefend()[indexToAirliftTo], armyNo);
                    //orderList->add(airlift);
                else
                    cout << "You do not have any Airlift cards!" << endl;
            } else {
                cout << "Invalid Airlift order" << endl;
            }
        }
        else if(orderString == "Blockade") {
            cout << "Select the target territories number from the following territories" << endl;
            for (int i = 0; i < this->getPlayer()->toDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->toDefend()[i]->getTerritoryName() << endl;
            }
            int indexToBlockade;
            cin >> indexToBlockade;
            if (indexToBlockade < this->getPlayer()->toDefend().size() && indexToBlockade >= 0) {
                string blockade = "blockade";
                int index = this->getPlayer()->getPlayerHand()->findCard(blockade);
                // playing the card from hand
                if(index != -1)
                    // order is issued in play method of class card
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    this->getPlayer()->toDefend()[indexToBlockade]);
                    //auto *blockade = new Blockade(this, this->toDefend()[indexToBlockade]);
                    //orderList->add(blockade);
                else
                    cout << "You do not have any Blockade cards!" << endl;
            } else {
                cout << "Invalid Blockade order" << endl;
            }
        }
        else if (orderString == "Negotiate") {
            cout << "Select the target Player number from the following Players" << endl;
            for (int i = 0; i < players_list.size(); i++) {
                if(this->getPlayer() != players_list[i]) {
                    cout << i << ": " << players_list[i]->getPlayerName() << endl;
                }
            }
            int indexToPlayer;
            cin >> indexToPlayer;
            if (indexToPlayer < players_list.size() && indexToPlayer >= 0) {
                string diplomacy = "diplomacy";
                int index = this->getPlayer()->getPlayerHand()->findCard(diplomacy);
                if(index != -1) {
                    // order issued in play method of class card
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    players_list[indexToPlayer]);
                }
                else
                    cout << "You do not have any diplomacy cards!" << endl;
            }
            else {
                cout << "Invalid diplomacy order" << endl;
            }
        }
        else{
            cout << "Invalid order." << endl;
        }
    }
}
vector<Territory*> Human::toAttack() {
    cout << "The following are enemy territories, decide priority of the territories to be attacked:" << endl;
    vector<Territory*> enemyTerritories = this->getPlayer()->get_neighbour_territories(this->getPlayer());
    for(int i = 1; i <= enemyTerritories.size(); i++){
        cout << i  << ": "<< this->getPlayer()->getTerritories()[i-1]->getTerritoryName() << endl;
    }
    cout <<"Select the order of priority by writing the number (type 0 to stop)" << endl;
    do{
        int numberOrder; cin >> numberOrder;
        if(numberOrder == 0){
            break;
        }
        if (numberOrder > enemyTerritories.size()){
            cout << "Invalid request, try again" << endl;
        }
        else{
            if(!this->getPlayer()->checkIfAlreadyExists(enemyTerritories[numberOrder-1], this->getPlayer()->getTerritoriesToAttack())) {
                this->getPlayer()->getTerritoriesToAttack().push_back(enemyTerritories[numberOrder-1]);
                cout << "Territory successfully added" << endl;
            }
            else{
                cout << "Territory already in the list" << endl;
            }
        }
    }
    while(enemyTerritories.size() != this->getPlayer()->getTerritoriesToAttack().size());

}
vector<Territory*> Human::toDefend() {
    cout << "The following are your territories, decide priority of the territories to be defended:" << endl;
    for(int i = 1; i <= this->getPlayer()->getTerritories().size(); i++){
        cout << i  << ": "<< this->getPlayer()->getTerritories()[i-1]->getTerritoryName() << endl;
    }
    cout <<"Select the order of priority by writing the number (type 0 to stop)" << endl;
    do{
        int numberOrder; cin >> numberOrder;
        if(numberOrder == 0){
            break;
        }
        if (numberOrder > this->getPlayer()->getTerritories().size()){
            cout << "Invalid request, try again" << endl;
        }
        else{
            if(!this->getPlayer()->checkIfAlreadyExists(this->getPlayer()->getTerritories()[numberOrder-1], this->getPlayer()->getTerritoriesToDefend())) {
                this->getPlayer()->getTerritoriesToDefend().push_back(this->getPlayer()->getTerritories()[numberOrder-1]);
                cout << "Territory successfully added" << endl;
            }
            else{
                cout << "Territory already in the list" << endl;
            }
        }
    }
    while(this->getPlayer()->getTerritories().size() != this->getPlayer()->getTerritoriesToDefend().size());
}

/**
 * Implementation of Aggressive class
 */
Aggressive::Aggressive(Player *player) : PlayerStrategy(player) {}
Aggressive::Aggressive(const Aggressive &aggressive) {
    this->setPlayer(aggressive.getPlayer());
}
void Aggressive::issueOrder() {

}
vector<Territory*> Aggressive::toAttack() {
    // ToAttack has order  of territories from weakest to strongest
    if(isStartOfGame()){
        int number = this->getPlayer()->getReinforcementPool() / this->getPlayer()->getTerritories().size();
        int counter = 0;
        //int territoryIndex = 0;
        for (int i = 0; i < this->getPlayer()->getTerritories().size(); i++) {
            this->getPlayer()->getTerritories()[i]->setArmyCount(number);
            this->getPlayer()->setReinforcementPool(this->getPlayer()->getReinforcementPool() - number);
        }
        int remainder = this->getPlayer()->getReinforcementPool() % this->getPlayer()->getTerritories().size();
        if (remainder != 0) {
            int currentArmyCount = this->getPlayer()->getTerritories()[0]->getArmyCount();
            this->getPlayer()->getTerritories()[0]->setArmyCount(currentArmyCount + remainder);
        }
    }

    vector<Territory*> allTerritories = this->getPlayer()->getTerritories();
    vector<Territory*> sortedTerritoriesFromWeakestToStrongest = allTerritories;
    // sort from weakest to strongest territory based on number of armies
    std::sort(sortedTerritoriesFromWeakestToStrongest.begin(), sortedTerritoriesFromWeakestToStrongest.end(),
              [](Territory* lhs, Territory* rhs) {
                  return lhs->getArmyCount() < rhs->getArmyCount();
              });
    this->getPlayer()->setTerritoriesToDefend(sortedTerritoriesFromWeakestToStrongest);

}
vector<Territory*> Aggressive::toDefend() {
    this->getPlayer()->getTerritoriesToDefend().clear();
}

/**
 * Benevolent class implementation
 */
Benevolent::Benevolent(Player *player) : PlayerStrategy(player) {}
Benevolent::Benevolent(const Benevolent &benevolent) {
    this->setPlayer(benevolent.getPlayer());
}
Benevolent::~Benevolent() {
    this->setPlayer(nullptr);
}
Benevolent &Benevolent::operator=(const Benevolent &benevolent) {
    this->setPlayer(benevolent.getPlayer());
    return *this;
}
ostream &operator<<(ostream& os, const Benevolent &benevolent) {
    os << "Benevolent player: " << benevolent.getPlayer()->getPlayerName() << endl;
    return os;
}
void Benevolent::issueOrder() {
    int numberOfArmies;
    int territoryToMoveToIndex;
    vector<Territory *> sortedTerritoriesFromStrongestToWeakest;
    vector<Territory *> adjacentTerritories;


    toAttack();
    toDefend();

    // Deployment Ordering
    int reinforcementArmies = this->getPlayer()->getReinforcementPool();
    int armiesToDeploy = 0;
    for (Territory *territory: this->toDefend()) {
        if (reinforcementArmies <= 0) {
            break;
        }
        do {
            armiesToDeploy = std::rand() % reinforcementArmies + 1;
            if (armiesToDeploy <= reinforcementArmies) {
                auto *deploy = new Deploy(this->getPlayer(), territory, armiesToDeploy);
                this->getPlayer()->getOrderList()->add(deploy);
                reinforcementArmies -= armiesToDeploy;
                break;
            }
        } while (true);

    }
    // if after all territories have been looped we have any armies left in the reinforcement pool then assign them to the weakest territory
    if (reinforcementArmies > 0) {
        auto *deploy = new Deploy(this->getPlayer(), toDefend()[0], armiesToDeploy);
        this->getPlayer()->getOrderList()->add(deploy);
    }
    cout << "Deployment Order is complete, now other orders can be issued" << endl;

    // Other orders
    // Add available orders
    vector<std::string> availableOrders;
    availableOrders.emplace_back("Advance");
    for (Card *card: this->getPlayer()->getPlayerHand()->getHandCards()) {
        availableOrders.emplace_back(card->getType());
    }
    availableOrders.emplace_back("end");

    cout << "Available Orders: ";
    for (string &order: availableOrders) {
        cout << order << ", ";
    }

    while (true) {
        int orderInt = rand() % availableOrders.size();
        string orderString = availableOrders[orderInt];

        if (orderString == "end") {
            cout << "Your turn has now ended." << endl;
            break;
        } else if (orderString == "Advance") {
            sortedTerritoriesFromStrongestToWeakest = this->getPlayer()->toDefend();
            std::sort(sortedTerritoriesFromStrongestToWeakest.begin(), sortedTerritoriesFromStrongestToWeakest.end(),
                      [](Territory *lhs, Territory *rhs) {
                          return lhs->getArmyCount() > rhs->getArmyCount();
                      });

            // Move armies from the strongest territories to the weakest
            for (Territory *startTerritory: sortedTerritoriesFromStrongestToWeakest) {
                adjacentTerritories = startTerritory->getAdjTerritories();
                do {
                    territoryToMoveToIndex = rand() % adjacentTerritories.size();
                    if (adjacentTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() ==
                        this->getPlayer()->getPlayerName()) {
                        break;
                    }
                } while (true);

                do {
                    numberOfArmies = rand() % startTerritory->getArmyCount();
                    if (numberOfArmies >= 0 && numberOfArmies <= startTerritory->getArmyCount()) {
                        break;
                    }
                } while (true);
                auto *advance = new Advance(this->getPlayer(),
                                            startTerritory,
                                            adjacentTerritories[territoryToMoveToIndex], numberOfArmies);
                this->getPlayer()->getOrderList()->add(advance);
            }
        } else if (orderString == "Bomb") {
            cout << "Benevolent Player: cannot bomb enemy territory";
        } else if (orderString == "Airlift") {
            Territory *strongestTerritory = sortedTerritoriesFromStrongestToWeakest[0];
            adjacentTerritories = strongestTerritory->getAdjTerritories();

            do {
                territoryToMoveToIndex = rand() % adjacentTerritories.size();
                if (adjacentTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() ==
                    this->getPlayer()->getPlayerName()) {
                    break;
                }
            } while (true);

            do {
                numberOfArmies = rand() % adjacentTerritories[territoryToMoveToIndex]->getArmyCount();
                if (numberOfArmies >= 0) {
                    break;
                }
            } while (true);

            auto *airlift = new Airlift(this->getPlayer(),
                                        strongestTerritory,
                                        adjacentTerritories[territoryToMoveToIndex], numberOfArmies);
            this->getPlayer()->getOrderList()->add(airlift);

        } else if (orderString == "Blockade") {
            Territory *targetTerritory;
            vector<Territory *> territoriesToBlockade = this->toDefend();
            int toBlockadeIndex = rand() % territoriesToBlockade.size();
            if (toBlockadeIndex > -1 && toBlockadeIndex <= territoriesToBlockade.size()) {
                targetTerritory = territoriesToBlockade[toBlockadeIndex];
            }
            if (targetTerritory->getOwner() == nullptr) {
                cout << "This territory is already Blockaded" << endl;
            } else {
                auto *blockade = new Blockade(this->getPlayer(), targetTerritory);
                this->getPlayer()->getOrderList()->add(blockade);
            }

        } else if (orderString == "Negotiate") {
            //this->getPlayer()->getNegotiatePlayersList()

        }
    }
}
vector<Territory*> Benevolent::toAttack() {
    this->getPlayer()->getTerritoriesToAttack().clear();
}
vector<Territory*> Benevolent::toDefend() {
    // ToDefend has order  of territories from weakest to strongest
    if(isStartOfGame()){
        int number = this->getPlayer()->getReinforcementPool() / this->getPlayer()->getTerritories().size();
        for (int i = 0; i < this->getPlayer()->getTerritories().size(); i++) {
            this->getPlayer()->getTerritories()[i]->setArmyCount(number);
            this->getPlayer()->setReinforcementPool(this->getPlayer()->getReinforcementPool() - number);
        }
        int remainder = this->getPlayer()->getReinforcementPool() % this->getPlayer()->getTerritories().size();
        if (remainder != 0) {
            int currentArmyCount = this->getPlayer()->getTerritories()[0]->getArmyCount();
            this->getPlayer()->getTerritories()[0]->setArmyCount(currentArmyCount + remainder);
        }
    }

    vector<Territory*> allTerritories = this->getPlayer()->getTerritories();
    vector<Territory*> sortedTerritoriesFromWeakestToStrongest = allTerritories;
    // sort from weakest to strongest territory based on number of armies
    std::sort(sortedTerritoriesFromWeakestToStrongest.begin(), sortedTerritoriesFromWeakestToStrongest.end(),
              [](Territory* lhs, Territory* rhs) {
                  return lhs->getArmyCount() < rhs->getArmyCount();
              });
    this->getPlayer()->setTerritoriesToDefend(sortedTerritoriesFromWeakestToStrongest);
}

/**
 * Neutral class implementation
 * @param player
 */

Neutral::Neutral(Player *player) : PlayerStrategy(player) {
}

Neutral::Neutral(const Neutral &neutral)  : PlayerStrategy(neutral) {
    this->setPlayer(neutral.getPlayer());
}

Neutral::~Neutral() {
    this->setPlayer(nullptr);
}

Neutral &Neutral::operator=(const Neutral &neutral) {
    this->setPlayer(neutral.getPlayer());
    return *this;
}

ostream &operator<<(ostream& os, const Neutral &neutral) {
    os << "Neutral Player: " << neutral.getPlayer()->getPlayerName() << endl;
    return os;
}

void Neutral::issueOrder() {
    if (dynamic_cast<Neutral*>(this->getPlayer()->getPlayerStrategy()) != nullptr) {
        if(this->getPlayer()->isPlayerWasAttacked()){
            this->getPlayer()->setPlayerStrategy(new Aggressive(this->getPlayer()));
            this->getPlayer()->setPlayerWasAttacked(false);
            cout << "Neutral player was attacked. Changing strategy to Aggressive." << endl;
        }
        cout <<  "PLAYER STRATEGY: Neutral -> Can not issue orders" << endl;

    } else if (dynamic_cast<Aggressive*>(this->getPlayer()->getPlayerStrategy()) != nullptr) {

        // code for aggressive strategy
        this->getPlayer()->getPlayerStrategy()->toAttack(); // this will prepare aggressive method toAttack()
        this->getPlayer()->getPlayerStrategy()->toDefend(); // this will prepare aggressive method toAttack
        this->getPlayer()->getPlayerStrategy()->issueOrder(); // this will issue orders as aggressive strategy

    }
}
vector<Territory*> Neutral::toAttack() {
    if (dynamic_cast<Neutral *>(this->getPlayer()->getPlayerStrategy()) != nullptr) {
        if (!this->getPlayer()->getTerritoriesToAttack().empty()) {
            this->getPlayer()->getTerritoriesToAttack().clear();
        }
    }
}
vector<Territory *> Neutral::toDefend() {
    if (dynamic_cast<Neutral *>(this->getPlayer()->getPlayerStrategy()) != nullptr) {
        if (!this->getPlayer()->getTerritoriesToDefend().empty()) {
            this->getPlayer()->getTerritoriesToDefend().clear();
        }
    }
}

/**
 * Cheater class implementation
 */
Cheater::Cheater(Player *player) : PlayerStrategy(player) {}
Cheater::Cheater(const Cheater &cheater) {
    this->setPlayer(cheater.getPlayer());
}
Cheater::~Cheater() {
    this->setPlayer(nullptr);
}
Cheater &Cheater::operator=(const Cheater &cheater) {
    this->setPlayer(cheater.getPlayer());
    return *this;
}
ostream &operator<<(ostream& os, const Cheater &cheater) {
    os << "Cheater player: " << cheater.getPlayer()->getPlayerName() << endl;
    return os;
}
void Cheater::issueOrder() {

}
vector<Territory*> Cheater::toAttack() {

}
vector<Territory*> Cheater::toDefect() {

}
