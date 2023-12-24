#include "Hand.h"

// Operator to add a card to the hand
Hand& Hand::operator+=(Card* card) {
    this->push_back(card);
    return *this;
}

// Play a card from the hand
Card* Hand::play() {
    if (!this->empty()) {
        Card* topCard = this->back();
        this->pop_back();
        return topCard;
    }
    else {
        return nullptr; // Case where Hand is empty
    }
}

// Get the top card from the hand without removing it
Card* Hand::top() const {
    return this->empty() ? nullptr : this->back();
}

// Overloaded operator to access cards in the hand by index
Card* Hand::operator[](int index) {
    if (index >= 0 && index < this->size()) {
        Card* selectedCard = this->at(index);
        this->erase(this->begin() + index);
        return selectedCard;
    }
    else {
        return nullptr; // Invalid index
    }
}

// Print the hand to an ostream
void Hand::print(ostream& out) const {
    for (const auto& card : *this) {
        card->print(out);
        out << " ";
    }
}

// Constructor to reconstruct the hand from a file
Hand::Hand(istream& in, const CardFactory* factory) {
    int numCards;
    in >> numCards;

    for (int i = 0; i < numCards; ++i) {
        string cardType;
        in >> cardType;

        // Assuming CardFactory can create cards by type
        Card* card = factory->createCard(cardType);
        this->push_back(card);
    }
}

// Friend function to insert all cards in the hand into an ostream
ostream& operator<<(ostream& os, const Hand& hand) {
    for (const auto& card : hand) {
        os << *card << " "; // Assuming Card has operator<< defined
    }
    return os;
}

// Save the hand to an ostream
void Hand::save(ostream& os) {
    os << "hand= ";
    for (int i = 0; i < hand.size(); i++) {
        os << *hand.front() << " ";
        hand.pop();
    }
}
