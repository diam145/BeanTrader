#include <iostream>
#include <fstream>
#include "Table.h"


// Function to display the main menu and get user choice
int mainMenu() {
    int choice;

    std::cout << "\n---------- Card Game ----------" << endl;
    std::cout << "1. New Game" << endl;
    std::cout << "2. Load Game" << endl;
    std::cout << "3. Exit" << endl;
    std::cout << "*******************************" << endl;

    std::cout << "Enter your choice (1-3): ";
    cin >> choice;

    return choice;
}

int main() {
    // Initialization
    filebuf file;
    ostream os(&file);
    ifstream savedDeck("deck.txt");
    ifstream savedTable("table.txt");

    static CardFactory* factory;
    static Deck deck;
    TradeArea* tradeArea = nullptr;
    DiscardPile* discardPile = nullptr;

    Table* table = nullptr;

    bool save = false;
    bool newGame = true;

    string* p1Name = new string();
    string* p2Name = new string();
    string* buff = new string(); // buffer to store the input of player

    // main menu
    int choice = mainMenu();
    if (choice == 1 || choice == 2) {
        goto main_loop;
    }
    else {
        exit(0);
    }

    // Main game loop
main_loop:
    while (newGame || (table && !table->isDeckEmpty())) {
        if (newGame) {
            if (savedDeck.good() && savedTable.good()) {
                std::cout << "\n------ Old Saves ------" << endl;
                readStringInput("Want to reload the game? (y/n): ", buff);
                if (*buff == "y") {
                    // Load and initialize table
                    factory = CardFactory::getFactory(savedDeck);
                    deck = factory->getDeck();
                    table = new Table(savedTable, factory);
                    savedDeck.close();
                    savedTable.close();

                    *p1Name = table->getPlayer(1)->getName(); // Use the address-of operator
                    *p2Name = table->getPlayer(2)->getName(); // Use the address-of operator
                }
            }
            if (*buff != "y") {
                // Create new table
                factory = CardFactory::getFactory();
                deck = factory->getDeck();
                readStringInput("Please enter the name of player1: ", p1Name);
                readStringInput("Please enter the name of player2: ", p2Name);
                table = new Table(*p1Name, *p2Name, factory);
            }
        }

        // Check for pause and save game
    saving:
        if (save) {
            ofstream saveTable("table.txt");
            ofstream saveDeck("deck.txt");
            table->save(saveTable);
            factory->save(saveDeck);
            saveTable.close();
            saveDeck.close();
            std::cout << "\n\n--- Game saved---\n\n" << endl;
            
            goto game_over;
        }

        if (tradeArea == nullptr || discardPile == nullptr) {
            tradeArea = table->getTradeArea();
            discardPile = table->getDiscardPile();
            newGame = false;
        }

        // For each player
        for (int playerIndex = 1; playerIndex <= 2; playerIndex++) {
            Player* currentPlayer = table->getPlayer(playerIndex);
            string pName = (currentPlayer->getName());
            Card* cDraw = deck.draw();

            // Display table
            std::cout << table;

            // Draw top card from Deck
            Card* drawnCard = table->getDeck().draw();
            currentPlayer->addCardToHand(drawnCard);
            std::cout << "\n----------- GAME START -----------\n" << endl;
            std::cout << "\n--- " << pName << " TURN ---\n" << endl;
            std::cout << "-> " << pName << " -> Drawing a card from deck: " << *drawnCard << endl;

            // Display table ??
            
            cout << table;

            // step 1:
            if (tradeArea->numCards() != 0) {
                // Add bean card from area?
                readStringInput("-> " + pName + " -> Get a card from the trade area? (y/n): ", buff);
                if (*buff == "y") {
                    // Add cards from trade area
                    string* card_name = new string();
                    vector<Card*> selectedCards;
                    while (*card_name != "q" && tradeArea->numCards() != 0) {
                        // while player want to get a card from trade area
                        Card* cBuff = nullptr;
                        std::cout << "-> " + pName + " -> Which card do you want to trade with?" << endl;
                        readStringInput("-> " + pName + " -> Enter the name of it (Soy/Blue) or enter 'q' to quit: ", card_name);
                        if (*card_name != "q") {
                            // if player entered a card name
                            Card* card = factory->createCard(*card_name);
                            cout << *card_name << endl;
                            cBuff = tradeArea->trade(card);
                            if (!cBuff) std::cout << "-> " + pName + " -> Invalid card." << endl;
                            else selectedCards.push_back(cBuff);
                        }
                    }
                    for (auto& card : selectedCards) {
                        // loop selected cards vector and add them to player's chains
                        if (currentPlayer->cardMatch(card))
                            std::cout << "-> " << pName << " -> " << *card << " added to your chain." << endl;
                        else {
                            std::cout << "-> " << pName << " -> " << *card << " No match in your chains" << endl;
                            readStringInput("-> " + pName + " -> Add a new chain ? (y/n): ", buff);
                            if (*buff == "y") {
                                if (currentPlayer->createChain(card, "") == nullptr)
                                    *discardPile += card; // discard the mismatched card if can't create new chain
                            }
                        }
                    }
                }
                tradeArea->discardAll(discardPile); // discards all cards in trade area
            }

            currentPlayer->play(); // play the topmost card

            if (currentPlayer->getHandSize() != 0) {
                std::cout << "\n-> " << pName << "->Hand: ";
                currentPlayer->printHand(cout, true);
                readStringInput("\n -> " + pName + " ->" + ") Play 1 more card? (y/n): ", buff);
                if (*buff == "y") currentPlayer->play();

                readStringInput("-> " + pName + " -> Discard 1 card from hand? (y/n): ", buff);
                if (*buff == "y") currentPlayer->discardHand(discardPile);
            }
            else
                std::cout << "\n-> " + pName + "-> Empty hand, skip /discarding one more card." << endl;

            std::cout << "\n!!! 3 Cards added to trade area !!!" << endl;
            for (int i = 0; i < 3; i++) *tradeArea += deck.draw(); // draw 3 cards and add to trade area
            while (!discardPile->isEmpty() && tradeArea->legal(discardPile->top())) {
                Card* cBuff = discardPile->pickUp();
                std::cout << "Card " << *cBuff << " popped from discard pile and added to trade area." << endl;
                *tradeArea += cBuff; // add the legal card to trade area
            }
            std::cout << "---------- Trade Area ----------\n" << *tradeArea << endl;
            if (tradeArea->numCards() != 0) tradeArea->trade(currentPlayer); // prompt player to make decision on each card in trade area
            // step 6:
            for (int i = 0; i < 2; i++) {
                Card* cDraw = deck.draw();
                currentPlayer->addCardToHand(cDraw); // draw card to hand
                std::cout << "-> " + pName + " -> Draws a card from deck: " << *cDraw << endl;
            }
        }

        // Prompt for saving the game
        readStringInput("\n***** Save game? *****\n(y/n): ", buff);
        if (*buff == "y") {
            save = true;
            goto saving;
        }
    }

    game_over:
    // Game over
    std::cout << "\n\n------- Deck is empty: game over -------\n" << endl;

    // Determine the winner
    const string& winnerName = (table->win(*p1Name) ? table->getPlayer(1)->getName() : table->getPlayer(2)->getName());

    std::cout << "The winner is " << winnerName << " ---" << endl;

    return 0;
}
