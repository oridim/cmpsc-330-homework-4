#include "player_move.h"

#include "player_turn.h"

// Default constructor for PlayerTurn
PlayerTurn::PlayerTurn()
{
    this->_columnIndex = -1;
    this->_turnIndex = -1;
    this->_rowIndex = -1;
    this->_playerInitial = '\0';
}

// Allows initialization for specific values for turn index, row index, column index
PlayerTurn::PlayerTurn(int turnIndex, int rowIndex, int columnIndex, char playerInitial)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
    this->_playerInitial = playerInitial;
    this->_turnIndex = turnIndex;
}

// Constructor for PlayerTurn using a PlayerMove object
PlayerTurn::PlayerTurn(const PlayerMove &playerMove, int turnIndex, char playerInitial)
{
    this->_columnIndex = playerMove.columnIndex();
    this->_rowIndex = playerMove.rowIndex();
    this->_playerInitial = playerInitial;
    this->_turnIndex = turnIndex;
}

// Copies constructor for PlayerTurn
PlayerTurn::PlayerTurn(const PlayerTurn &playerTurn)
{
    this->_columnIndex = playerTurn._columnIndex;
    this->_rowIndex = playerTurn._rowIndex;
    this->_playerInitial = playerTurn._playerInitial;
    this->_turnIndex = playerTurn._turnIndex;
}

// Equality operator to compare PlayerTurn object by instance (nominal instances)
bool PlayerTurn::operator==(const PlayerTurn &rightHandTurn) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandTurn;
}
// Inequality operator, opposite of the equality operator.
bool PlayerTurn::operator!=(const PlayerTurn &rightHandTurn) const
{
    // See `PlayerTurn::operator==` for reasoning.
    return this != &rightHandTurn;
}