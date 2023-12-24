#ifndef CHAIN_BASE_H
#define CHAIN_BASE_H

#include "Card.h"
#include <iostream>
#include <vector>

using namespace std;

// Chain_Base class
class Chain_Base {
protected:
    std::string name;      // Name of the chain
    std::string type;      // Type of cards in the chain
    std::vector<Card*> chain;  // Vector to store cards in the chain

public:
    char getName() const;  // Get the first character of the chain name
    bool match(Card* c);   // Match a card and add it to the chain if it matches
    void save(std::ostream& os) const;  // Save the chain to an output stream
    virtual Chain_Base& operator+=(Card* card) = 0;  // Overloaded operator to add a card to the chain
    virtual int sell() const = 0;  // Calculate the number of coins the chain can be sold for
    virtual void print(std::ostream& out) const = 0;  // Print the chain to the output stream
    virtual bool empty() const = 0;  // Check if the chain is empty
    virtual Card* top() const;  // Get a pointer to the top card in the chain
    virtual ~Chain_Base() = default;  // Virtual destructor for base class
};

inline char Chain_Base::getName() const {
    return name.empty() ? '\0' : name[0];  // Return the first character of the chain name or '\0' if empty
}

inline bool Chain_Base::match(Card* card) {
    if (type == typeid(*card).name()) {  // Check if the type of the card matches the chain type
        chain.push_back(card);  // Add the card to the chain
        return true;
    }
    return false;
}

inline void Chain_Base::save(std::ostream& os) const {
    if (!chain.empty()) {
        os << *chain[0] << " " << chain.size();  // Save the first card and the size of the chain
    }
}

inline bool Chain_Base::empty() const {
    return chain.empty();  // Check if the chain is empty
}

inline Card* Chain_Base::top() const {
    return empty() ? nullptr : chain.back();  // Return the top card or nullptr if the chain is empty
}

#endif
