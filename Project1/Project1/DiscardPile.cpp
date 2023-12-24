#include "DiscardPile.h"

// DiscardPile class implementation

// Constructor to reconstruct the DiscardPile from a file
DiscardPile::DiscardPile(istream& in, const CardFactory* factory) : discardPile(), factory() {
    int numCards;
    in >> numCards;

    for (int i = 0; i < numCards; ++i) {
        string cardType;
        in >> cardType;

        // Assuming CardFactory can create cards by type
        Card* card = factory->createCard(cardType);
        push_back(card);
    }
}

// Operator to add a card to the discard pile
DiscardPile& DiscardPile::operator+=(Card* card) {
    push_back(card);
    return *this;
}

// Friend function to insert all cards in the discard pile into an ostream
ostream& operator<<(ostream& out, const DiscardPile& discardPile) {
    discardPile.print(out);  // Reuse the existing print function
    return out;
}

// Check if the discard pile is empty
bool DiscardPile::isEmpty() {
    return (discardPile.size() == 0) ? true : false;
}

// Pick up the top card from the discard pile
Card* DiscardPile::pickUp() {
    if (!isEmpty()) {
        Card* topCard = back();
        pop_back();
        discardPile.pop_back();
        return topCard;
    }
    else {
        return nullptr; // DiscardPile is empty
    }
}

// Get the top card from the discard pile without removing it
Card* DiscardPile::top() const {
    return (!empty()) ? back() : nullptr; // DiscardPile is empty
}

// Print the discard pile to an ostream
void DiscardPile::print(ostream& out) const {
    for (const auto& card : *this) {
        card->print(out); // Assumes Card class has a print function
        out << " ";
    }
}

// Save the discard pile to an ostream
void DiscardPile::save(ostream& os) {
    os << "discard= ";
    for (int i = 0; i < discardPile.size(); i++)
        os << *discardPile[i] << " ";
}
