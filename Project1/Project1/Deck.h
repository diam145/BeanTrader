#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include "Card.h"

class CardFactory;      // Forward declaration (necessary to avoid circular dependency with Deck class)

// Deck class
class Deck : public vector<Card*> {
public:

    Deck() : vector<Card*>::vector(0) {};  // Default constructor

    // Const that takes an input stream and a CardFactory instance pointer
    Deck(istream& in, const CardFactory* factory);

    // Function to draw the top card from the deck
    Card* draw();

    // Friend function to insert all cards in the deck into an ostream
    friend ostream& operator<<(ostream& out, const Deck& deck);

    int numCards() { return static_cast<int>(this->size()); }  // Return the number of cards in the deck

    bool isEmpty() const;  // Check if the deck is empty

private:
    vector<Card*> cards;  // Vector to store cards in the deck
    // Private helper function to print a single card to an ostream
    void printCard(ostream& out, const Card* card) const;
};

#endif
