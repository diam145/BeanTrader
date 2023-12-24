#ifndef PLAYER_H
#define PLAYER_H

#include <sstream>
#include <list>
#include "Card.h"
#include "CardFactory.h"
#include "Chain_Base.h"
#include <memory>
#include "Chain.h"
#include "Hand.h"
#include "ReadInput.h"
#include "DiscardPile.h"

using namespace std;

// Player class
class Player {
public:
    // Constructors
    Player(const string& name);
    Player(istream& instream, const CardFactory* factory);

    // Getter for player's name
    string getName() const;

    // Check if a card matches any in the player's hand
    bool cardMatch(Card* card);

    // Get the size of the player's hand
    int getHandSize();

    // Add a card to the player's hand
    void addCardToHand(Card* card);

    // Get the number of coins the player has
    int getNumCoins() const;

    // Get the maximum number of chains the player can have
    int getMaxNumChains() const;

    // Get the current number of chains the player has
    int getNumChains() const;

    // Buy a third chain for the player
    void buyThirdChain();

    // Sell a chain and earn coins
    void sellChain();

    // Discard the entire hand to the discard pile
    void discardHand(DiscardPile* discardPile);

    // Print the player's hand
    void printHand(ostream& out, bool all) const;

    // Destructor to clean up memory allocated for chains
    ~Player();

    // Play a turn for the player
    void play();

    // Create a new chain for a specific card type
    Chain_Base* createChain(Card* card, string t);

    // Save the player's state to an ostream
    void save(ostream& os);

    // Operators
    Player& operator+=(int coins);
    Chain_Base& operator[](int i);

    // Friend function to insert player information into an ostream
    friend ostream& operator<<(ostream& os, const Player& player);

private:
    Hand* hand;
    int max_chain;
    string name;
    int numCoins;
    vector<Chain_Base*> chains;
};

#endif
