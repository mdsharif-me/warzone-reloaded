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
vector<Territory*> PlayerStrategy::getTerritoriesToDefend() {
    return this->player->getTerritoriesToDefend();
}
vector<Territory*> PlayerStrategy::getTerritoriesToAttack() {
    return this->player->getTerritoriesToAttack();
}

/**
 * Implementation of Human class
 */
Human::Human(Player *player) : PlayerStrategy(player) {}
Human::Human(const Human &h) : PlayerStrategy(h) {}
Human::~Human() {}
void Human::issueOrder(Deck* deck, vector<Player*> players_list) {
    cout << "Territories to Defend in priority. " << endl;
    cout << "Please deploy Army to each territory:" << endl;
    int tempArmy;
    do{
        tempArmy = this->getPlayer()->getReinforcementPool(); //Getting player
        if(tempArmy==0) {
            cout << "No more armies to deploy!";
            break;
        }
        cout << "Currently inside Human Player" << endl;
        cout << "Be sure to deploy all your armies to be able to issue other orders" << endl;
        for(Territory* territory: this->getPlayer()->getTerritoriesToDefend()) {
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
    } while (tempArmy!=0);
    //this->getPlayer()->setReinforcementPool(0); // We do not need to do this, because execute() in deploy class does it for us.
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
            for (int i = 0; i < this->getPlayer()->getTerritoriesToDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->getTerritoriesToDefend()[i]->getTerritoryName() << endl;
            }
            int sourceIndex;
            cin >> sourceIndex;
            vector<Territory *> adjacentTerritories;
            if (sourceIndex < this->getPlayer()->getTerritoriesToDefend().size() && sourceIndex >= 0) {
                adjacentTerritories = this->getPlayer()->getTerritoriesToDefend()[sourceIndex]->getAdjTerritories();
                cout << "Select the adjacent territories number to which the army should be moved to." << endl;
                for (int i = 0; i < adjacentTerritories.size(); i++) {
                    cout << i << ": " << adjacentTerritories[i]->getTerritoryName() << endl;
                }
                int targetIndex;
                cin >> targetIndex;
                if (targetIndex < adjacentTerritories.size() && targetIndex >= 0) {
                    cout << "Enter number of armies (" << this->getPlayer()->getTerritoriesToDefend()[sourceIndex]->getArmyCount() << "):" << endl;
                    int armynum;
                    cin >> armynum;
                    if (armynum >= 0) {
                        //Advance does not require a card.
                        auto *advance = new Advance(this->getPlayer(), this->getPlayer()->getTerritoriesToDefend()[sourceIndex],
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
            for (int i = 0; i < this->getPlayer()->getTerritoriesToAttack().size(); i++) {
                cout << i << ": " << this->getPlayer()->getTerritoriesToAttack()[i]->getTerritoryName() << endl;
            }
            int indexToBomb;
            cin >> indexToBomb;
            if (indexToBomb < this->getPlayer()->getTerritoriesToAttack().size() && indexToBomb >= 0) {
                string bomb = "Bomb";
                int index = this->getPlayer()->getPlayerHand()->findCard(bomb);
                // playing the card from hand
                if(index != -1)
                    // the order is issued by the play method in card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    this->getPlayer()->getTerritoriesToAttack()[indexToBomb]);
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
            for (int i = 0; i < this->getPlayer()->getTerritoriesToDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->getTerritoriesToDefend()[i]->getTerritoryName() << endl;
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
            if (indexToAirliftFrom < this->getPlayer()->getTerritoriesToDefend().size() && indexToAirliftFrom >= 0 &&
                indexToAirliftTo < this->getPlayer()->getTerritoriesToDefend().size() && indexToAirliftTo >= 0 && armyNo >= 0) {
                string airlift = "Airlift";
                int index = this->getPlayer()->getPlayerHand()->findCard(airlift);
                // playing the card from hand
                if(index != -1)
                    // the order is issued in the play method on card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    this->getPlayer()->getTerritoriesToDefend()[indexToAirliftFrom],
                                                                                    this->getPlayer()->getTerritoriesToDefend()[indexToAirliftTo],
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
            for (int i = 0; i < this->getPlayer()->getTerritoriesToDefend().size(); i++) {
                cout << i << ": " << this->getPlayer()->getTerritoriesToDefend()[i]->getTerritoryName() << endl;
            }
            int indexToBlockade;
            cin >> indexToBlockade;
            if (indexToBlockade < this->getPlayer()->getTerritoriesToDefend().size() && indexToBlockade >= 0) {
                if (this->getPlayer()->getTerritoriesToDefend()[indexToBlockade]->getOwner() == nullptr) {
                    cout << "This territory is already Blockaded" << endl;
                }
                else {
                    string blockade = "blockade";
                    int index = this->getPlayer()->getPlayerHand()->findCard(blockade);
                    // playing the card from hand
                    if (index != -1)
                        // order is issued in play method of class card
                        this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                        this->getPlayer()->getTerritoriesToDefend()[indexToBlockade]);
                        //auto *blockade = new Blockade(this, this->toDefend()[indexToBlockade]);
                        //orderList->add(blockade);
                    else
                        cout << "You do not have any Blockade cards!" << endl;
                }
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
                string diplomacy = "Diplomacy";
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
void Human::toAttack() {
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
void Human::toDefend() {
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
Aggressive::Aggressive(Player *player) : PlayerStrategy(player) {
    this->setPlayer(player);
}
Aggressive::Aggressive(const Aggressive &aggressive) {
    this->setPlayer(aggressive.getPlayer());
}
void Aggressive::issueOrder(Deck* deck, vector<Player*> players_list) {
    int numberOfArmies;
    int territoryToMoveToIndex;
    vector<Territory *> sortedTerritoriesFromStrongestToWeakest = this->getPlayer()->getTerritoriesToDefend();
    vector<Territory *> adjacentTerritories;
    // Deployment Ordering
    int reinforcementArmies = this->getPlayer()->getReinforcementPool();
    int armiesToDeploy = 0;
    for (Territory *territory: sortedTerritoriesFromStrongestToWeakest) {
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
        auto *deploy = new Deploy(this->getPlayer(), getTerritoriesToDefend()[0], armiesToDeploy);
        this->getPlayer()->getOrderList()->add(deploy);
    }
    cout << this->getPlayer()->getPlayerName() << " completed deployment. now other orders can be issued." << endl;

    // Other orders
    // Add available orders
    vector<std::string> availableOrders;
    availableOrders.push_back("Advance");
    if (this->getPlayer()->getPlayerHand()->getHandCards().size() != 0) {
        for (Card *card: this->getPlayer()->getPlayerHand()->getHandCards()) {
            if (card != nullptr) {
                availableOrders.push_back(card->getType());
            }
        }
    }

    availableOrders.push_back("end");

    cout << "Available Orders: ";
    for (const string& order: availableOrders) {
        cout << order << ", ";
    }
    cout << endl;

    bool advancedOrderIssued = false;
    string orderString;
    while (true) {
        int orderInt = rand() % availableOrders.size();
        orderString = availableOrders[orderInt];
        if (orderString == "end" && !advancedOrderIssued) {
            orderString = "Advance";
        }
        vector<Territory*> enemyTerritories = this->getPlayer()->getTerritoriesToAttack();


        if (orderString == "end") {
            cout << "Your turn has now ended." << endl;
            break;
        }
        else if (orderString == "Advance") {
            vector<Territory*> startTerritoryUnfriendlyTerritories;
            // Move armies from the strongest territories to the weakest
            bool skipAdvanceOrder = false;
            for (Territory *startTerritory: sortedTerritoriesFromStrongestToWeakest) {
                if (startTerritory->getAdjTerritories().empty()) {
                    cout << "no more territories to advance to" << endl;
                }
                adjacentTerritories = startTerritory->getAdjTerritories();
                for(Territory* temp: adjacentTerritories) {
                    if (temp->isEnemy(this->getPlayer())) {
                        startTerritoryUnfriendlyTerritories.push_back(temp);
                    }
                }
                int attempts = 0;
                do {
                    if (attempts == 100) {
                        skipAdvanceOrder = true;
                        break;
                    }
                    if (startTerritoryUnfriendlyTerritories.empty()) {
                        skipAdvanceOrder = true;
                    } else {
                        territoryToMoveToIndex = rand() % startTerritoryUnfriendlyTerritories.size();
                    }

                    if (skipAdvanceOrder) {
                        break;
                    } else {
                        if (startTerritoryUnfriendlyTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() !=
                            this->getPlayer()->getPlayerName()) {
                            break;
                        }
                    }
                    ++attempts;
                } while (true);



                do {
                    if (skipAdvanceOrder) {
                        break;
                    }
                    if (isStartOfGame()) {
                        numberOfArmies = 0;
                        break;
                    } else {
                        numberOfArmies = rand() % startTerritory->getArmyCount() + 1;
                        if (numberOfArmies >= 0 && numberOfArmies <= startTerritory->getArmyCount()) {
                            break;
                        }
                    }
                } while (true);

                if (!skipAdvanceOrder) {
                    auto *advance = new Advance(this->getPlayer(),
                                                startTerritory,
                                                startTerritoryUnfriendlyTerritories[territoryToMoveToIndex], numberOfArmies);
                    this->getPlayer()->getOrderList()->add(advance);
                    cout << this->getPlayer()->getPlayerName() << ": issued an Advance Order" << endl;
                    cout << this->getPlayer()->getPlayerName() << ": will move " << numberOfArmies << " armies "
                    << "from " << startTerritory->getTerritoryName() << " to " << startTerritoryUnfriendlyTerritories[territoryToMoveToIndex]->getTerritoryName() << endl;
                }
                startTerritoryUnfriendlyTerritories.clear();
            }
            advancedOrderIssued = true;
        }
        else if (orderString == "Bomb") {
            int territoryBombToIndex = rand() % enemyTerritories.size();
            Territory* targetTerritory = enemyTerritories[territoryBombToIndex];
            string bomb = "Bomb";
            int index = this->getPlayer()->getPlayerHand()->findCard(bomb);
            // playing the card from hand
            if(index != -1)
                // the order is issued by the play method in card class
                this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                targetTerritory);
            cout << this->getPlayer()->getPlayerName() << ": issued a Bomb Order" << endl;
            cout << this->getPlayer()->getPlayerName() << ": " << targetTerritory->getTerritoryName()
            << " belonging to " << targetTerritory->getOwner()->getPlayerName() << " will be bombed" << endl;
        }
        else if (orderString == "Airlift") {
            bool skipAirliftOrder = false;
            Territory *strongestTerritory = sortedTerritoriesFromStrongestToWeakest[0];
            adjacentTerritories = strongestTerritory->getAdjTerritories();
            vector<Territory* > friendlyNeighbourTerritories;
            for(Territory* temp: adjacentTerritories) {
                if (temp->isAllied(this->getPlayer())) {
                    friendlyNeighbourTerritories.push_back(temp);
                }
            }

            do {
                if (friendlyNeighbourTerritories.empty()) {
                    skipAirliftOrder = true;
                    break;
                } else {
                    territoryToMoveToIndex = rand() % friendlyNeighbourTerritories.size();
                    if (friendlyNeighbourTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() ==
                        this->getPlayer()->getPlayerName()) {
                        break;
                    }
                }

            } while (true);

            do {
                if (skipAirliftOrder) {
                    break;
                }
                if (isStartOfGame()) {
                    numberOfArmies = 0;
                    break;
                }
                if (friendlyNeighbourTerritories.empty())
                numberOfArmies = rand() % friendlyNeighbourTerritories[territoryToMoveToIndex]->getArmyCount() + 1;
                if (numberOfArmies >= 0) {
                    break;
                }
            } while (true);

            if (!skipAirliftOrder) {
                string airlift = "Airlift";
                int index = this->getPlayer()->getPlayerHand()->findCard(airlift);
                // playing the card from hand

                if(index != -1) {
                    if (strongestTerritory->getArmyCount() - numberOfArmies < 0 ) {
                        numberOfArmies =strongestTerritory->getArmyCount();
                    }
                    // the order is issued in the play method on card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    strongestTerritory,
                                                                                    friendlyNeighbourTerritories[territoryToMoveToIndex],
                                                                                    numberOfArmies);
                    cout << this->getPlayer()->getPlayerName() << ": issued an Airlift Order: " << numberOfArmies
                         << " troops will be airlifted to "
                         << friendlyNeighbourTerritories[territoryToMoveToIndex]->getTerritoryName() << endl;
                }
            }
        }
        else if (orderString == "Blockade") {
            Territory *targetTerritory;
            vector<Territory *> territoriesToBlockade = this->getTerritoriesToDefend();
            int toBlockadeIndex;
            do {
                toBlockadeIndex = rand() % territoriesToBlockade.size();
                if (toBlockadeIndex > -1 && toBlockadeIndex <= territoriesToBlockade.size()) {
                    break;
                }
            } while (true);

            targetTerritory = territoriesToBlockade[toBlockadeIndex];

            if (targetTerritory->getOwner() == nullptr) {
                cout << "This territory is already Blockaded" << endl;
            } else {
                /* auto *blockade = new Blockade(this->getPlayer(), targetTerritory);
                 this->getPlayer()->getOrderList()->add(blockade);*/
                string blockade = "Blockade";
                int index = this->getPlayer()->getPlayerHand()->findCard(blockade);
                if(index != -1)
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    targetTerritory);
                cout << this->getPlayer()->getPlayerName() << ": issued a Blockade Order against " << targetTerritory->getTerritoryName() << endl;
            }
        }
        else if (orderString == "Negotiate") {
            Player* player;
            do {
                int playerInt = rand() % players_list.size();
                player= players_list[playerInt];
            } while (this->getPlayer()->getPlayerName() == player->getPlayerName());
            string diplomacy = "Diplomacy";
            int index = this->getPlayer()->getPlayerHand()->findCard(diplomacy);
            if(index != -1)
                this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                player);
            cout << this->getPlayer()->getPlayerName() << ": issued a Negotiate Order against " << player->getPlayerName() << endl;
        }
    }
}
void Aggressive::toAttack() {
    // ToAttack has order  of territories from weakest to strongest
    vector<Territory*> enemyTerritories = this->getPlayer()->get_neighbour_territories(this->getPlayer());
    // TODO: is it needed?
    /*if(isStartOfGame()){
        int number = this->getPlayer()->getReinforcementPool() / enemyTerritories.size();
        int counter = 0;
        for (int i = 0; i < enemyTerritories.size(); i++) {
            this->getPlayer()->getTerritories()[i]->setArmyCount(number);
            this->getPlayer()->setReinforcementPool(this->getPlayer()->getReinforcementPool() - number);
        }
        int remainder = this->getPlayer()->getReinforcementPool() % this->getPlayer()->getTerritories().size();
        if (remainder != 0) {
            int currentArmyCount = this->getPlayer()->getTerritories()[0]->getArmyCount();
            this->getPlayer()->getTerritories()[0]->setArmyCount(currentArmyCount + remainder);
        }
    }*/
    this->getPlayer()->setTerritoriesToAttack(enemyTerritories);

}
void Aggressive::toDefend() {
    //TODO:
    // ToDefend has order  of territories from weakest to strongest
    vector<Territory*> allTerritories = this->getPlayer()->getTerritories();
    int reinforcementPool = this->getPlayer()->getReinforcementPool();
    if(isStartOfGame()){
        int number = reinforcementPool / allTerritories.size();
        for (int i = 0; i < allTerritories.size(); i++) {
            Deploy *deploy = new Deploy(this->getPlayer(), allTerritories[i], number);
            this->getPlayer()->getOrderList()->add(deploy);
            reinforcementPool -= number;
        }
        int remainder = this->getPlayer()->getReinforcementPool() % allTerritories.size();
        if (remainder != 0) {
            Deploy *deploy = new Deploy(this->getPlayer(), allTerritories[0], remainder);
            this->getPlayer()->getOrderList()->add(deploy);
        }
    }

    vector<Territory*> sortedTerritoriesFromStrongestToWeakest = allTerritories;
    // sort from weakest to strongest territory based on number of armies
    std::sort(sortedTerritoriesFromStrongestToWeakest.begin(), sortedTerritoriesFromStrongestToWeakest.end(),
              [](Territory* lhs, Territory* rhs) {
                  return lhs->getArmyCount() > rhs->getArmyCount();
              });
    // Setting Territories to Defend
    this->getPlayer()->setTerritoriesToDefend(sortedTerritoriesFromStrongestToWeakest);
}

/**
 * Benevolent class implementation
 */
Benevolent::Benevolent(Player *player) : PlayerStrategy(player) {
    this->setPlayer(player);
}
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
void Benevolent::issueOrder(Deck* deck, vector<Player*> players_list) {
    int numberOfArmies;
    int territoryToMoveToIndex;
    vector<Territory* > sortedTerritoriesFromWeakestToStrongest = this->getPlayer()->getTerritoriesToDefend();;
    vector<Territory *> sortedTerritoriesFromStrongestToWeakest ;
    vector<Territory *> adjacentTerritories;
    // Deployment Ordering
    int reinforcementArmies = this->getPlayer()->getReinforcementPool();
    int armiesToDeploy = 0;
    for (Territory *territory: sortedTerritoriesFromWeakestToStrongest) {

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
        auto *deploy = new Deploy(this->getPlayer(), getTerritoriesToDefend()[0], armiesToDeploy);
        this->getPlayer()->getOrderList()->add(deploy);
    }
    cout << this->getPlayer()->getPlayerName() << " completed deployment. now other orders can be issued." << endl;

    // Other orders
    // Add available orders
    vector<std::string> availableOrders;
    availableOrders.emplace_back("Advance");
    if (!this->getPlayer()->getPlayerHand()->getHandCards().empty()) {
        for (Card *card: this->getPlayer()->getPlayerHand()->getHandCards()) {
            if (card != nullptr) {
                availableOrders.emplace_back(card->getType());
            }
        }
    }
    availableOrders.emplace_back("end");

    cout << "Available Orders: ";
    for (string &order: availableOrders) {
        cout << order << ", ";
    }
    cout << endl;

    while (true) {
        int orderInt = rand() % availableOrders.size();
        string orderString = availableOrders[orderInt];
        sortedTerritoriesFromStrongestToWeakest = this->getPlayer()->getTerritoriesToDefend();
        std::sort(sortedTerritoriesFromStrongestToWeakest.begin(), sortedTerritoriesFromStrongestToWeakest.end(),
                  [](Territory *lhs, Territory *rhs) {
                      return lhs->getArmyCount() > rhs->getArmyCount();
                  });
        if (orderString == "end") {
            cout << this->getPlayer()->getPlayerName() << " turn has now ended." << endl;
            break;
        }
        else if (orderString == "Advance") {
            // Move armies from the strongest territories to the weakest
            bool skipAdvanceOrder = false;
            vector<Territory*> friendlyTerritories;
            for (Territory *startTerritory: sortedTerritoriesFromStrongestToWeakest) {
                adjacentTerritories = startTerritory->getAdjTerritories();
                for(Territory* territory: adjacentTerritories) {
                    if (territory->isAllied(this->getPlayer())) {
                        friendlyTerritories.push_back(territory);
                    }
                }
                int attempts = 0;
                do {
                    if (attempts == 10) {
                        skipAdvanceOrder = true;
                        break;
                    }
                    if (friendlyTerritories.empty()) {
                        skipAdvanceOrder = true;
                    } else {
                        territoryToMoveToIndex = rand() % friendlyTerritories.size();
                    }

                    if (skipAdvanceOrder) {
                        break;
                    } else {
                        if (friendlyTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() == this->getPlayer()->getPlayerName()) {
                            break;
                        }
                    }

                    ++attempts;
                } while (true);

                do {
                    if (skipAdvanceOrder) {
                        break;
                    }
                    if (isStartOfGame()) {
                        numberOfArmies = 0;
                        break;
                    }
                    numberOfArmies = rand() % startTerritory->getArmyCount() + 1;
                    if (numberOfArmies >= 0 && numberOfArmies <= startTerritory->getArmyCount()) {
                        break;
                    }
                } while (true);

                if (!skipAdvanceOrder) {
                    auto *advance = new Advance(this->getPlayer(),
                                                startTerritory,
                                                friendlyTerritories[territoryToMoveToIndex], numberOfArmies);
                    this->getPlayer()->getOrderList()->add(advance);
                    cout << this->getPlayer()->getPlayerName() << ": issued an Advance Order" << endl;
                    cout << this->getPlayer()->getPlayerName() << ": will move " << numberOfArmies << " armies "
                         << "from " << startTerritory->getTerritoryName() << " to " << friendlyTerritories[territoryToMoveToIndex]->getTerritoryName() << endl;
                }
                friendlyTerritories.clear();
            }
        }
        else if (orderString == "Bomb") {
            cout << "Benevolent Player Strategy: cannot bomb enemy territory" << endl;
        }
        else if (orderString == "Airlift") {
            bool skipAirliftOrder = false;
            Territory *strongestTerritory = sortedTerritoriesFromStrongestToWeakest[0];
            adjacentTerritories = strongestTerritory->getAdjTerritories();
            vector<Territory*> friendlyNeighbourTerritories;
            for(Territory* temp: adjacentTerritories) {
                if (temp->isAllied(this->getPlayer())) {
                    friendlyNeighbourTerritories.push_back(temp);
                }
            }

            do {
                if (friendlyNeighbourTerritories.empty()) {
                    skipAirliftOrder = true;
                    break;
                } else {
                    territoryToMoveToIndex = rand() % friendlyNeighbourTerritories.size();
                    if (friendlyNeighbourTerritories[territoryToMoveToIndex]->getOwner()->getPlayerName() ==
                        this->getPlayer()->getPlayerName()) {
                        break;
                    }
                }
            } while (true);

            do {
                if (skipAirliftOrder) {
                    break;
                } else {
                    numberOfArmies = rand() % friendlyNeighbourTerritories[territoryToMoveToIndex]->getArmyCount();
                    if (numberOfArmies >= 0) {
                        break;
                    }
                }
            } while (true);

            if (!skipAirliftOrder) {
                string airlift = "Airlift";
                int index = this->getPlayer()->getPlayerHand()->findCard(airlift);
                // playing the card from hand
                if(index != -1) {
                    if (strongestTerritory->getArmyCount() - numberOfArmies < 0 ) {
                        numberOfArmies =strongestTerritory->getArmyCount();
                    }
                    // the order is issued in the play method on card class
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    strongestTerritory,
                                                                                    friendlyNeighbourTerritories[territoryToMoveToIndex],
                                                                                    numberOfArmies);
                    cout << this->getPlayer()->getPlayerName() << ": issued an Airlift Order. Troops will be moved to "
                         << friendlyNeighbourTerritories[territoryToMoveToIndex] << endl;
                }
            }
        }
        else if (orderString == "Blockade") {
            Territory *targetTerritory;
            vector<Territory *> territoriesToBlockade = this->getTerritoriesToDefend();
            if (!territoriesToBlockade.empty()) {
                int toBlockadeIndex = rand() % territoriesToBlockade.size();
                if (toBlockadeIndex >= 0 && toBlockadeIndex <= territoriesToBlockade.size()) {
                    targetTerritory = territoriesToBlockade[toBlockadeIndex];
                }
                if (targetTerritory != nullptr) {
                    if (targetTerritory->getOwner() == nullptr) {
                        cout << "This territory is already Blockaded" << endl;
                    } else {
                        string blockade = "Blockade";
                        int index = this->getPlayer()->getPlayerHand()->findCard(blockade);
                        if(index != -1)
                            this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                            targetTerritory);
                        cout << this->getPlayer()->getPlayerName() << ": issued a Blockade Order against " << targetTerritory->getTerritoryName() << endl;
                    }
                }
            }
        }
        else if (orderString == "Negotiate") {
            Player* player;
            do {
                if (!players_list.empty()) {
                    int playerInt = rand() % players_list.size();
                    player= players_list[playerInt];
                } else {
                    break;
                }
            } while (this->getPlayer()->getPlayerName() == player->getPlayerName());

            if (!players_list.empty()) {
                string diplomacy = "Diplomacy";
                int index = this->getPlayer()->getPlayerHand()->findCard(diplomacy);
                if(index != -1)
                    this->getPlayer()->getPlayerHand()->getHandCards()[index]->play(this->getPlayer(), deck,
                                                                                    player);
                cout << this->getPlayer()->getPlayerName() << ": issued a Negotiate Order against " << player->getPlayerName() << endl;
            } else {
                cout << "No player to negotiate to" << endl;
            }
        }
    }
}
void Benevolent::toAttack() {
    this->getPlayer()->getTerritoriesToAttack().clear();
}
void Benevolent::toDefend() {
    // ToDefend has order  of territories from weakest to strongest
    vector<Territory*> allTerritories = this->getPlayer()->getTerritories();
    int reinforcementPool = this->getPlayer()->getReinforcementPool();
    if(isStartOfGame()){
        int number = reinforcementPool / allTerritories.size();
        for (int i = 0; i < allTerritories.size(); i++) {
            Deploy *deploy = new Deploy(this->getPlayer(), allTerritories[i], number);
            this->getPlayer()->getOrderList()->add(deploy);
            reinforcementPool -= number;
        }
        int remainder = this->getPlayer()->getReinforcementPool() % allTerritories.size();
        if (remainder != 0) {
            Deploy *deploy = new Deploy(this->getPlayer(), allTerritories[0], remainder);
            this->getPlayer()->getOrderList()->add(deploy);
        }
    }

    vector<Territory*> sortedTerritoriesFromWeakestToStrongest = allTerritories;
    // sort from weakest to strongest territory based on number of armies
    std::sort(sortedTerritoriesFromWeakestToStrongest.begin(), sortedTerritoriesFromWeakestToStrongest.end(),
              [](Territory* lhs, Territory* rhs) {
                  return lhs->getArmyCount() < rhs->getArmyCount();
              });
    // Setting Territories to Defend
    this->getPlayer()->setTerritoriesToDefend(sortedTerritoriesFromWeakestToStrongest);
}

/**
 * Neutral class implementation
 * @param player
 */

Neutral::Neutral(Player *player) : PlayerStrategy(player) {}
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
void Neutral::issueOrder(Deck* deck, vector<Player*> players_list) {
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
        this->getPlayer()->getPlayerStrategy()->issueOrder(deck, players_list); // this will issue orders as aggressive strategy

    }
}
void Neutral::toAttack() {
    if (dynamic_cast<Neutral *>(this->getPlayer()->getPlayerStrategy()) != nullptr) {
        if (!this->getPlayer()->getTerritoriesToAttack().empty()) {
            this->getPlayer()->getTerritoriesToAttack().clear();
        }
    }
}
void Neutral::toDefend() {
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
void Cheater::issueOrder(Deck* deck, vector<Player*> players_list) {
    Territory* territory = this->getPlayer()->getTerritoriesToAttack().front();
    Player* enemyPlayer = territory->getOwner();
    enemyPlayer->removeTerritory(territory);
    enemyPlayer->setPlayerWasAttacked(true);
    this->getPlayer()->addTerritory(territory);
    this->getPlayer()->setNewTerritoryConquered(true);
    cout << this->getPlayer()->getPlayerName() << " has acquired new territory: " << territory->getTerritoryName() << endl;
}
void Cheater::toAttack() {
    vector<Territory*> enemyTerritories = this->getPlayer()->get_neighbour_territories(this->getPlayer());
    vector<Territory*> unfriendlyTerritories;
    for(Territory* temp: enemyTerritories) {
        if (temp->isEnemy(this->getPlayer())) {
            unfriendlyTerritories.push_back(temp);
        }
    }

    this->getPlayer()->setTerritoriesToAttack(unfriendlyTerritories);
}
void Cheater::toDefend() {
    vector<Territory*> defendTerritories = this->getPlayer()->getTerritories();
    this->getPlayer()->setTerritoriesToDefend(defendTerritories);
}
