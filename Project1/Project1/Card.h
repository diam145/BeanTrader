#pragma once
#include <string>
#include <iostream>

using namespace std;

// Abstract base class for cards
class Card {
public:
    // Pure virtual functions to be implemented by derived classes

    // Returns the number of cards that can be bought with a given number of coins
    virtual int getCardsPerCoin(int coins) const = 0;

    // Returns the name of the card
    virtual string getName() const = 0;

    // Prints a visual representation of the card
    virtual void print(ostream& out) const = 0;

    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~Card() = default;
};

// Derived class for Blue card
class Blue : public Card {
public:
    // Implementation of the pure virtual function from the base class
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 4 : (coins == 2 ? 6 : (coins == 3 ? 8 : 10));
    }

    // Implementation of the pure virtual function from the base class
    string getName() const override {
        return "Blue";
    }

    // Implementation of the pure virtual function from the base class
    void print(ostream& out) const override {
        out << "B";
    }
};

// Derived class for Chili card
class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 3 : (coins == 2 ? 6 : (coins == 3 ? 8 : 9));
    }

    string getName() const override {
        return "Chili";
    }

    void print(ostream& out) const override {
        out << "C";
    }
};

// Derived class for Stink card
class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 3 : (coins == 2 ? 5 : (coins == 3 ? 7 : 8));
    }

    string getName() const override {
        return "Stink";
    }

    void print(ostream& out) const override {
        out << "S";
    }
};

// Derived class for Green card
class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 3 : (coins == 2 ? 5 : (coins == 3 ? 6 : 7));
    }

    string getName() const override {
        return "Green";
    }

    void print(ostream& out) const override {
        out << "G";
    }
};

// Derived class for Soy card
class Soy : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 2 : (coins == 2 ? 4 : (coins == 3 ? 6 : 7));
    }

    string getName() const override {
        return "Soy";
    }

    void print(ostream& out) const override {
        out << "Y";
    }
};

// Derived class for Black card
class Black : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 2 : (coins == 2 ? 4 : (coins == 3 ? 5 : 6));
    }

    string getName() const override {
        return "Black";
    }

    void print(ostream& out) const override {
        out << "K";
    }
};

// Derived class for Red card
class Red : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return coins == 1 ? 2 : (coins == 2 ? 3 : (coins == 3 ? 4 : 5));
    }

    string getName() const override {
        return "Red";
    }

    void print(ostream& out) const override {
        out << "R";
    }
};

// Derived class for Garden card
class Garden : public Card {
public:
    int getCardsPerCoin(int coins) const override {
        return 0;  // No coins for Garden cards
    }

    string getName() const override {
        return "Garden";
    }

    void print(ostream& out) const override {
        out << "A";  // Using "A" for Garden cards
    }
};

// Declare createCard function to instantiate a card based on its type
Card* createCard(const string& cardType);

// Declare operator<< as a friend function for printing cards
ostream& operator<<(std::ostream& os, const Card& card);
