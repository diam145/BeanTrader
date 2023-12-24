#include "CardFactory.h"
#include "Deck.h"  

// Initialize the singleton instance to nullptr
CardFactory* CardFactory::factoryInstance{ nullptr };

// Default constructor for CardFactory
CardFactory::CardFactory() {
    // Initialize the deck with cards based on the required numbers
    for (int i = 0; i < 10; ++i) {
        deck.push_back(new Black());
        deck.push_back(new Blue());
        deck.push_back(new Chili());
        deck.push_back(new Green());
        deck.push_back(new Garden());
        deck.push_back(new Red());
        deck.push_back(new Soy());
        deck.push_back(new Stink());
    }

    // Shuffle the deck for randomness
    random_device random;
    mt19937 g(random());
    shuffle(deck.begin(), deck.end(), g);
}

// Constructor for CardFactory to reconstruct the saved game state
CardFactory::CardFactory(istream& is) {
    deck = Deck(is, this);
    string line, type;
    getline(is, line);
    istringstream buff(line);
    while (buff >> type) {
        // Create cards based on the saved types and add them to the deck
        if (type == "b") deck.push_back(new Black()); 
        else if (type == "B") deck.push_back(new Blue());
        else if (type == "C") deck.push_back(new Chili());
        else if (type == "G") deck.push_back(new Green());
        else if (type == "g") deck.push_back(new Garden());
        else if (type == "S") deck.push_back(new Stink());
        else if (type == "s") deck.push_back(new Soy());
        else if (type == "R") deck.push_back(new Red());
        type.clear();
    }
}

// Get the singleton instance of CardFactory, create if not existing
CardFactory* CardFactory::getFactory() {
    if (factoryInstance == nullptr) {
        factoryInstance = new CardFactory();
    }
    return factoryInstance;
}

// Get the singleton instance of CardFactory with custom initialization from istream
CardFactory* CardFactory::getFactory(istream& istream) {
    if (factoryInstance == nullptr) factoryInstance = new CardFactory(istream);
    return factoryInstance;
}

// Get a constant reference to the deck managed by CardFactory
const Deck& CardFactory::getDeck() const {
    return deck;
}

// Create a card of the specified type
Card* CardFactory::createCard(const string& cardType) const {
    // Check the cardType and return an instance of the corresponding card class
    if (cardType == "Blue") {
        return new Blue();
    }
    else if (cardType == "Black") {
        return new Black();
    }
    else if (cardType == "Chili") {
        return new Chili();
    }
    else if (cardType == "Green") {
        return new Green();
    }
    else if (cardType == "Garden") {
        return new Garden();
    }
    else if (cardType == "Red") {
        return new Red();
    }
    else if (cardType == "Soy") {
        return new Soy();
    }
    else if (cardType == "Stink") {
        return new Stink();
    }

    return nullptr;  // Return nullptr if the cardType is not recognized
}

// Save the state of CardFactory to an ostream
void CardFactory::save(ostream& ostream) {
    for (Card* card : deck) ostream << *card << " ";
}

// Destructor for CardFactory
CardFactory::~CardFactory() {}
