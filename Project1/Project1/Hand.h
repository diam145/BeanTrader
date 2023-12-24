#ifndef HAND_H
#define HAND_H

#include <list>
#include <queue>
#include <vector>
#include "Card.h"
#include "CardFactory.h"

using namespace std;

// Hand class
class Hand : public vector<Card*> {
private:
    queue<Card*, list<Card*>> hand;   // list with queue adapter 

public:
    // Default constructor
    Hand() {};

    // Operator to add a card to the hand
    Hand& operator+=(Card* card);

    // Play a card from the hand
    Card* play();

    // Get the top card from the hand without removing it
    Card* top() const;

    // Overloaded operator to access cards in the hand by index
    Card* operator[](int index);

    // Print the hand to an ostream
    void print(ostream& out) const;

    // Constructor to reconstruct the hand from a file
    Hand(istream& in, const CardFactory* factory);

    // Save the hand to an ostream
    void save(ostream& os);

    // Friend function to insert all cards in the hand into an ostream
    friend ostream& operator<<(ostream& os, const Hand& hand);
};

#endif
