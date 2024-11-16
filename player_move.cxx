#include "player_move.h"

// Default constructor for PlayerMove, initalizes row and column indices to -1
PlayerMove::PlayerMove()
{
    this->_columnIndex = -1;
    this->_rowIndex = -1;
}

// Constructor for PlayerMovie with specific row and column indices
PlayerMove::PlayerMove(int rowIndex, int columnIndex)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
}

// Copy constructor for PlayerMove, creates a copy of another PlayerMove object
PlayerMove::PlayerMove(const PlayerMove &playerTurn)
{
    this->_columnIndex = playerTurn._columnIndex;
    this->_rowIndex = playerTurn._rowIndex;
}

// Equality operator for comparing two PlayerMove objects
bool PlayerMove::operator==(const PlayerMove &rightHandMove) const
{
    
    return this == &rightHandMove;
}

// Inequality operator for comparing two PlayerMove objects
bool PlayerMove::operator!=(const PlayerMove &rightHandMove) const
{
    // Use the equality operator to determine if the objects are not equal. 
    return this != &rightHandMove;
}