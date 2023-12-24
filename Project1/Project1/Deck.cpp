#include "Deck.h"
#include "CardFactory.h"

// Constructor to reconstruct the deck from a file
Deck::Deck(istream& in, const CardFactory* factory) {
    int numCards;
    if (!(in >> numCards)) {
        throw runtime_error("Error reading the number of cards from the input stream.");
    }

    for (int i = 0; i < numCards; ++i) {
        string cardType;
        if (!(in >> cardType)) {
            throw runtime_error("Error reading card type from the input stream.");
        }

        // Assuming CardFactory can create cards by type (finally it does)
        Card* card = factory->createCard(cardType);
        if (card) {
            this->push_back(card);
        }
        else {
            throw runtime_error("Error creating a card using the CardFactory.");
        }
    }
}

bool Deck::isEmpty() const {
    return cards.empty();
}

// Function to draw the top card from the deck
Card* Deck::draw() {
    if (!this->empty()) {
        Card* topCard = this->back();
        this->pop_back();
        return topCard;
    }
    else {
        return nullptr; // Deck is empty
    }
}

// Friend function to insert all cards in the deck into an ostream
ostream& operator<<(ostream& out, const Deck& deck) {
    for (const auto& card : deck) {
        deck.printCard(out, card);
        out << " ";
    }
    return out;
}

// Private function to print a single card to an ostream
void Deck::printCard(ostream& out, const Card* card) const {
    card->print(out);  // Assumes Card class has a print function
}
