#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include "Deck.h" 
#include <algorithm>
#include <random>
#include <sstream>
#include "Card.h"

class Deck;  // Forward declaration of Deck

class CardFactory {
private:
    static CardFactory* factoryInstance;  // Singleton instance of CardFactory
    Deck deck;  // Deck instance managed by CardFactory

    // Private constructors to enforce singleton pattern
    CardFactory();
    CardFactory(istream& is);

public:
    // Get the singleton instance of CardFactory
    static CardFactory* getFactory();

    // Get the singleton instance of CardFactory with custom initialization from istream
    static CardFactory* getFactory(istream&);

    // Save the state of CardFactory to an ostream
    void save(ostream&);

    // Get a constant reference to the deck managed by CardFactory
    const Deck& getDeck() const;

    // Create a card of the specified type
    Card* createCard(const string& cardType) const;

    // Destructor to clean up resources
    ~CardFactory();
};

// Declare factoryInstance as extern
extern CardFactory* factoryInstance;

#endif
