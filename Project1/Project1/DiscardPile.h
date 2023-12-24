#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <vector>
#include "Card.h"
#include "CardFactory.h"

using namespace std;

// DiscardPile class
class DiscardPile : public vector<Card*> {
private:
    vector<Card*> discardPile;  // Private vector to store discarded cards
    const CardFactory* factory;  // Pointer to the CardFactory for creating cards

public:
    // Default constructor
    DiscardPile() : discardPile(), factory() {};

    // Operator to add a card to the discard pile
    DiscardPile& operator+=(Card* card);

    // Friend function to insert all cards in the discard pile into an ostream
    friend ostream& operator<<(ostream& out, const DiscardPile& discardPile);

    // Check if the discard pile is empty
    bool isEmpty();

    // Pick up the top card from the discard pile
    Card* pickUp();

    // Get the top card from the discard pile without removing it
    Card* top() const;

    // Print the discard pile to an ostream
    void print(ostream& out) const;

    // Save the discard pile to an ostream
    void save(ostream& os);

    // Constructor to reconstruct the discard pile from a file
    DiscardPile(istream& in, const CardFactory* factory);
};

#endif
