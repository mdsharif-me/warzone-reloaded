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
void Human::issueOrder() {

}
vector<Territory*> Human::toAttack() {

}
vector<Territory*> Human::toDefend() {

}

/**
 * Implementation of Human class
 */
void Aggressive::issueOrder() {

}

vector<Territory*> Aggressive::toAttack() {

}

vector<Territory*> Aggressive::toDefend() {

}

Aggressive::Aggressive(Player *player) : PlayerStrategy(player) {

}



/**
 * Benevolent class implementation
 */
Benevolent::Benevolent(Player *player) : PlayerStrategy(player) {

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

Cheater::Cheater(Player *player) : PlayerStrategy(player) {

}

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

