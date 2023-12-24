#include "Card.h"

// Implementation of the createCard function
Card* createCard(const string& cardType) {
    // Check the card type and instantiate the corresponding card class
    if (cardType == "Blue") {
        return new Blue();
    }
    else if (cardType == "Chili") {
        return new Chili();
    }
    else if (cardType == "Stink") {
        return new Stink();
    }
    else if (cardType == "Green") {
        return new Green();
    }
    else if (cardType == "Soy") {
        return new Soy();
    }
    else if (cardType == "Black") {
        return new Black();
    }
    else if (cardType == "Red") {
        return new Red();
    }
    else if (cardType == "Garden") {
        return new Garden();
    }
    else {
        return new Black();
    }
    
    
    // If the cardType is not recognized, return nullptr or throw an exception
    return nullptr;  // Alternatively, we can throw an exception for an unknown card type
}

// Implementation of the global stream insertion operator for cards
ostream& operator<<(ostream& out, const Card& card) {
    card.print(out);
    return out;
}
