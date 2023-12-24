#include "TradeArea.h"

// Trade a card from a player's hand to the trade area
Card* TradeArea::trade(Card* card) {
    return trade(card->getName());
}

// Trade cards from the trade area to a player's chains
void TradeArea::trade(Player* player) {
    string* buff = new string();
    int index = 0;
    for (Card* card : area) {
        bool erase = true;
        string pName = player->getName();
        cout << ("-> " + pName + " -> Do you want to chain the card: " + card->getName() + " (y/n)? ", buff);
        if (*buff == "y") {
            if (!player->cardMatch(card)) {
                cout << ("-> " + pName + " -> Do you want to create a new chain to match this card? (y/n): ", buff);
                if (*buff == "y") {
                    if (player->createChain(card, "") == nullptr) erase = false;
                    else cout << "(" << player->getName() << ") New " << card->getName() << " chain created." << endl;
                }
                else erase = false;
            }
            else cout << "(" << player->getName() << ") Card added to a chain." << endl;
            if (erase) {
                list<Card*>::iterator iter = area.begin();
                advance(iter, index);
                area.erase(iter);
                index--;
            }
        }
        index++;
    }
}

// Remove a card from the trade area based on the bean name
Card* TradeArea::trade(const string& beanName) {
    int index = 0;
    for (Card* card : area) {
        if (card->getName() == beanName) {
            Card* c = card;
            // remove the card in area:
            list<Card*>::iterator iter = area.begin();
            advance(iter, index);
            area.erase(iter);
            return card;
        }
        index++;
    }
    return nullptr;
}

// Get the number of cards in the trade area
int TradeArea::numCards() { return area.size(); }

// Discard all cards from the trade area to a discard pile
void TradeArea::discardAll(DiscardPile* discardPile) {
    for (auto& card : area) *discardPile += card;
    area.clear();
}

// Save the state of the trade area to an output stream
void TradeArea::save(ostream& os) {
    os << "trade= ";
    list<Card*>::iterator iter;
    for (iter = area.begin(); iter != area.end(); iter++)
        os << **iter << " ";
}

// Check if it is legal to add the card to the trade area
bool TradeArea::legal(Card* card) const {
    for (auto const& cardInArea : area)
        if (cardInArea->getName() == card->getName()) return true;
    return false;
}

// Print all cards in the trade area
void TradeArea::print(ostream& out) const {
    for (const auto& card : *this) {
        card->print(out);  // Assumes Card class has a print function
        out << " ";
    }
}

// Constructor to reconstruct the TradeArea from a file
TradeArea::TradeArea(istream& in, const CardFactory* factory) {
    int numCards;
    in >> numCards;

    for (int i = 0; i < numCards; ++i) {
        string cardType;
        in >> cardType;

        // Assuming CardFactory can create cards by type
        Card* card = factory->createCard(cardType);
        push_back(card);
        area.push_back(card);
    }
}

// Operator to add a card to the trade area
TradeArea& TradeArea::operator+=(Card* card) {
    push_back(card);
    area.push_back(card);
    return *this;
}

// Friend function to insert all Pile in the deck into an ostream
ostream& operator<<(ostream& out, const TradeArea& tradeArea) {
    tradeArea.print(out);  // Reuse the existing print function
    return out;
}
