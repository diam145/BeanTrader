#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <iostream>
#include <list>
#include "Card.h"
#include "CardFactory.h"
#include "Player.h"
#include "DiscardPile.h"

using namespace std;

// TradeArea class
class TradeArea : public list<Card*> {
private:
    list<Card*> area;

public:
    // Default constructor
    TradeArea() {};

    // Constructor to reconstruct the TradeArea from a file
    TradeArea(istream& in, const CardFactory* factory);

    // Trade a card from a player's hand to the trade area
    Card* trade(Card* card);

    // Trade a card from the trade area based on the bean name
    Card* trade(const string& beanName);

    // Trade cards from the trade area to a player's chains
    void trade(Player*);

    // Discard all cards from the trade area to a discard pile
    void discardAll(DiscardPile*);

    // Check if it is legal to add the card to the trade area
    bool legal(Card* card) const;

    // Get the number of cards in the trade area
    int numCards();

    // Save the state of the trade area to an output stream
    void save(ostream& os);

    // Print all cards in the trade area
    void print(ostream& out) const;

    // Operator to add a card to the trade area
    TradeArea& operator+=(Card* card);

    // Friend function to insert all Pile in the deck into an ostream
    friend ostream& operator<<(ostream& out, const TradeArea& tradeArea);

};

#endif
