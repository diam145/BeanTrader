#include "Player.h"

Player::Player(const string& playerName) : name(playerName), numCoins(0) {
    this->max_chain = 2;
    hand = new Hand();
}

Player::Player(istream& instream, const CardFactory* factory) : numCoins(0) {
    instream >> name >> numCoins;
    this->max_chain = 2;
    this->hand = new Hand();

    Deck deck = factory->getFactory()->getDeck();

    string line;

    while (getline(instream, line)) {
        istringstream buff(line);
        auto delimiterPos = line.find("=");
        string key = line.substr(0, delimiterPos);
        string value = line.substr(delimiterPos + 1);

        if (key == "name") this->name = value;
        else if (key == "coin") numCoins = stoi(value);
        else if (key == "max") max_chain = stoi(value);
        else if (key == "chain1" || key == "chain2" || key == "chain3") {
            int num = (int)value.at(2) - '0';
            if (value.at(0) == 'R') {
                this->createChain(new Red(), typeid(Red).name());
                for (size_t i = 0; i < num; i++) *(chains.back()) += new Red();
            }
            // Similar blocks for other card types...
        }
        else if (key == "hand") hand = new Hand(buff, factory);
        char peeked = instream.peek();
        if (peeked == 'n') break;    // player1's data read completed
    }
}

Player::~Player() = default;

string Player::getName() const {
    return name;
}

bool Player::cardMatch(Card * card) {
    for (auto& chain : chains)
        if (chain->match(card)) return true;
    return false;
}

int Player::getHandSize() { return hand->size(); }

void Player::addCardToHand(Card * card) { *hand += card; }

int Player::getNumCoins() const {
    return numCoins;
}

int Player::getMaxNumChains() const {
    return chains.size();
}

int Player::getNumChains() const {
    int nonZeroChains = 0;
    for (const auto& chain : chains) {
        if (!chain->empty()) {
            nonZeroChains++;
        }
    }
    return nonZeroChains;
}

Chain_Base& Player::operator[](int i) {
    if (i >= 0 && i < chains.size()) {
        auto it = next(chains.begin(), i);
        return **it;
    }
    else {
        // Handle out-of-bounds index, possibly throw an exception
        // For simplicity, we are returning the first chain in case of an invalid index
        return *chains.front();
    }
}

void Player::buyThirdChain() {
    if (getNumCoins() >= 3 && getMaxNumChains() == 2) {
        Chain<Red>* chain = new Chain<Red>();
        chains.push_back(chain);
        numCoins -= 3;
    }
    else {
        // Handle insufficient coins or maximum chains reached, possibly throw an exception
    }
}

void Player::sellChain() {
    string* chain_num = new string("0");
    int count = 1;
    for (auto it = chains.begin(); it != chains.end(); ++it)
        cout << count++ << ": " << (*it) << "\n";

    while (!(stoi(*chain_num) > 0 && stoi(*chain_num) <= chains.size())) {
        readStringInput("Please enter a chain number to sell (1-" + to_string(chains.size()) + "): ", chain_num);
    }
    auto it = next(chains.begin(), stoi(*chain_num) - 1);
    char  chain_name = (*it)->getName();
    *this += (*it)->sell();  // add coins to player
    chains.erase(it);  // remove the chain just sold
    cout << "(" << this->name << ") " << chain_name << " Chain sold successfully and have "
        << numCoins << " coins now." << endl;

}

void Player::discardHand(DiscardPile* discardPile) {
    if (hand->size() == 0) {
        cout << this->name << " don't have any card in hand." << endl;
        return;
    }
    cout << *hand << endl;
    string* card_num = new string("0");
    while (stoi(*card_num) < 1 || stoi(*card_num) > (*hand).size())
        readStringInput("(" + this->name + ")Please enter a card number to discard (1-" + to_string(hand->size()) + "): ", card_num);
    Card* cBuff = (*hand)[stoi(*card_num) - 1];
    *discardPile += cBuff;
    cout << "(" << this->name << ") " << *cBuff << " popped from hand." << endl;
}

void Player::printHand(ostream& out, bool all) const {
    out << name << " " << numCoins << " coins\n";

    if (all) {
        for (const auto& chain : chains) {
            chain->print(out);
            out << endl;
        }
    }
    else {
        chains.front()->print(out);  // Print only the top card of the first chain
        out << endl;
    }
}

ostream& operator<<(ostream& os, const Player& player) {
    os << "Player: " << player.name << ", Coins: " << player.numCoins << ", Hand: ";
    for (const auto& card : *player.hand) {
        os << *card << " ";
    }
    return os;
}

Player& Player::operator+=(int coins) {
    numCoins += coins;
    return *this;
}


void Player::play() {
    if (hand->size() == 0) {
        cout << this->name << " don't have any card in hand." << endl;
        return;
    }
    Card* card = hand->play();  // play the topmost card from hand
    cout << endl << this->name << " played topmost card in hand: " << *card << endl;
    if (!this->cardMatch(card)) {
        string* buff = new string();
        switch (chains.size()) {
        case 3:
            cout << "Currently " << this->name << " have 3 chains, but no one matched this card." << endl;
            this->sellChain();
            this->createChain(card, "");    // add the mismatched card to a new chain
            cout << "(" << this->name << ") The mismatched card added to a new chain." << endl;
            break;
        case 2:
            if (numCoins >= 3) {
                // player has more than 3 coins
                cout << "(" << this->name << ") This card mismatched your chains." << endl;
                cout << ("(" + this->name + ") Do you want to create a new chain for this card or sell an existed chain? (y/n): ", buff);

                if (*buff == "y") {

                    this->buyThirdChain();
                    this->createChain(card, "");
                    cout << "(" << this->name << ") Third chain created with the card added to it." << endl;
                }
            }
            else {
                // player has less than 3 coins
                cout << this->name << " have less than 3 coins and all 2 chains mismatched, so you need to sell one chain." << endl;
                this->sellChain();
                this->createChain(card, "");
                cout << "(" << this->name << ") The mismatched card added to a new chain." << endl;
            }
            break;
        case 1:

            readStringInput("(" + this->name + ") This card mismatched, do you want to create a new chain for this card? (y/n): ", buff);
            if (*buff == "y") {
                this->createChain(card, "");
                cout << "(" << this->name << ") Second chain created with the card added to it." << endl;
            }
            else {

                cout << "(" << this->name << ") Don't want to create a new chain? OK!" << endl;
                this->sellChain();
                this->createChain(card, "");
                cout << "(" << this->name << ") The mismatched card added to a new chain." << endl;
            }
            break;
        default:

            this->createChain(card, "");
            cout << this->name << "'s first chain created with the card added to it." << endl;
            break;
        }
    }
    else cout << "(" << this->name << ") " << *card << " added to a chain." << endl;
}


Chain_Base* Player::createChain(Card* card, string t) {
    if (chains.size() + 1 > max_chain) {
        cout << this->name << "'s maximum number of chain reached!" << endl;
        return nullptr;
    }
    string type;
    if (t != "") type = t;                  
    else type = typeid(*card).name();       

    unique_ptr<Chain_Base> chain;

    if (type == typeid(Black).name()) {
        Chain<Black>* chain = new Chain<Black>();
        chains.push_back(chain);
    }
    else if (type == typeid(Blue).name()) {
        Chain<Blue>* chain = new Chain<Blue>();
        chains.push_back(chain);
    }
    else if (type == typeid(Chili).name()) {
        Chain<Chili>* chain = new Chain<Chili>();
        chains.push_back(chain);
    }
    else if (type == typeid(Garden).name()) {
        Chain<Garden>* chain = new Chain<Garden>();
        chains.push_back(chain);
    }
    else if (type == typeid(Green).name()) {
        Chain<Green>* chain = new Chain<Green>();
        chains.push_back(chain);
    }
    else if (type == typeid(Red).name()) {
        Chain<Red>* chain = new Chain<Red>();
        chains.push_back(chain);
    }
    else if (type == typeid(Soy).name()) {
        Chain<Soy>* chain = new Chain<Soy>();
        chains.push_back(chain);
    }
    else {
        Chain<Stink>* chain = new Chain<Stink>();
        chains.push_back(chain);
    }

    if (t.empty()) {
        *(chains.back()) += card;
    }

    return chains.back();
}


void Player::save(ostream& os) {
    int index = 1;
    os << "name=" << name << endl;
    os << "coins=" << numCoins << endl;
    hand->save(os);
    os << endl << "max=" << max_chain << endl;
    for (auto& chain : chains) {
        os << "chain" << index++ << "=";
        (*chain).save(os);
        os << endl;
    }
}