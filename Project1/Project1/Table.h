#ifndef TABLE_H
#define TABLE_H

#include "Card.h"
#include "CardFactory.h"
#include "Player.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Deck.h"

using namespace std;

// Table class represents the state of the game
class Table {
private:
    Player* player1;        // Player 1 object
    Player* player2;        // Player 2 object
    Deck deck;              // Deck of cards
    DiscardPile* discardPile;   // Discard pile for used cards
    TradeArea* tradeArea;   // Trade area for face-up cards

public:
    // Constructor to initialize the table with player names and a card factory
    Table(const string& player1Name, const string& player2Name, const CardFactory* factory);

    // Check if there is a winner and update the winner's name
    bool win(string& winner);

    // Print the hands of players and the cards in the trade area
    void printHand(bool all) const;

    // Get a reference to the deck
    Deck getDeck() { return deck; };

    // Get a pointer to a player by index (1 or 2)
    Player* getPlayer(int);

    // Get a pointer to the trade area
    TradeArea* getTradeArea();

    // Get a pointer to the discard pile
    DiscardPile* getDiscardPile();

    // Save the current state of the table to an output stream
    void save(ostream&);

    // Check if the deck is empty
    bool isDeckEmpty() const {
        return deck.isEmpty();
    }

    // Friend function to output the table state to an ostream
    friend ostream& operator<<(ostream& out, const Table& table);

    // Constructor to reconstruct the table from a file
    Table(istream& in, const CardFactory* factory);
};

#endif
