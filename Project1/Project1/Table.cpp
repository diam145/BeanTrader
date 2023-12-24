#include "Table.h"

Table::Table(const string& player1Name, const string& player2Name, const CardFactory* factory) {
    // Initialize the table with player names and a card factory
    deck = factory->getFactory()->getDeck();
    player1 = new Player(player1Name);
    player2 = new Player(player2Name);
    discardPile = new DiscardPile();
    tradeArea = new TradeArea();
}

bool Table::win(string& winner) {
    // Determine the winner based on the win condition
    if (deck.empty()) {
        if (player1->getNumCoins() > player2->getNumCoins()) {
            winner = player1->getName();
        }
        else {
            winner = player2->getName();
        }
        return true;
    }
    return false;
}

void Table::printHand(bool all) const {
    // Print hands of both players
    player1->printHand(cout, all);
    player2->printHand(cout, all);
}

Player* Table::getPlayer(int i)
{
    // Return a pointer to the specified player (1 or 2)
    return (i == 1) ? player1 : player2;
}

TradeArea* Table::getTradeArea()
{
    // Return a pointer to the trade area
    return tradeArea;
}

DiscardPile* Table::getDiscardPile()
{
    // Return a pointer to the discard pile
    return discardPile;
}

void Table::save(ostream& ostream)
{
    // Save the state of the table to an output stream
    tradeArea->save(ostream);
    ostream << endl;
    discardPile->save(ostream);
    ostream << endl;
    player1->save(ostream);
    player2->save(ostream);
    ostream << endl;
}

ostream& operator<<(ostream& out, const Table& table) {
    // Output the state of the table to an ostream
    out << "Player 1:\n" << *table.player1 << "\n\n";
    out << "Player 2:\n" << *table.player2 << "\n\n";
    out << "Deck:\n" << table.deck << "\n\n";
    out << "Discard Pile:\n" << *table.discardPile << "\n\n";
    out << "Trade Area:\n" << *table.tradeArea << "\n\n";
    return out;
}

Table::Table(istream& in, const CardFactory* factory) {
    // Reconstruct the table from a file using an input stream
    tradeArea = new TradeArea(in, factory);
    discardPile = new DiscardPile(in, factory);
    player1 = new Player(in, factory);
    player2 = new Player(in, factory);
}
