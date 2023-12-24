#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include "Card.h"
#include "Chain_Base.h"
#include "CardFactory.h"

using namespace std;

// Template class for representing a Chain of cards of a specific type
template <typename T>
class Chain : public Chain_Base {
private:
    vector<T*> cards;  // Vector to store cards in the chain

public:
    // Default constructor
    Chain() = default;

    // Overloaded operator to add a card to the chain
    Chain& operator+=(Card* card) override {
        T* castedCard = dynamic_cast<T*>(card);
        if (castedCard) {
            cards.push_back(castedCard);
        }
        else {
            throw invalid_argument("IllegalType: Trying to add a card of a different type to the chain.");
        }
        return *this;
    }

    // Get the name of the card at the top of the chain
    const char getName() {
        return cards.empty() ? '\0' : cards.front()->getName();
    }

    // Get a pointer to the top card in the chain
    inline Card* top() {
        return cards.empty() ? nullptr : cards.back();
    };

    // Check if the chain is empty
    inline bool empty() const {
        return cards.empty();
    };

    // Calculate the number of coins the chain can be sold for
    int sell() const override {
        return cards.size() > 0 ? cards.front()->getCardsPerCoin(cards.size()) : 0;
    }

    // Print the chain to the output stream
    void print(ostream& out) const override {
        if (!cards.empty()) {
            out << cards.front()->getName() << " ";
            for (const auto& card : cards) {
                out << card->getName() << " ";
            }
            out << endl;
        }
    }

    // Constructor to reconstruct the chain from a file
    Chain(istream& in, const CardFactory* factory) {
        int numCards;
        in >> numCards;

        for (int i = 0; i < numCards; ++i) {
            string cardType;
            in >> cardType;

            Card* card = factory->createCard(cardType);
            *this += card;
        }
    }

    // Destructor to release memory occupied by cards
    ~Chain() override {
        for (auto card : cards) {
            delete card;
        }
    }
};

// Insertion operator (friend) to print Chain on ostream
template <typename T>
ostream& operator<<(ostream& out, const Chain<T>& chain) {
    chain.print(out);
    return out;
}

#endif
