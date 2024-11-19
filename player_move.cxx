//---------------------------------------------------------------------
//
// Name: Ozge Selin Ak + Dimitri Orion Nearchos
// Email: osa5177@psu.edu + don5092@psu.edu
// Class: CMPSC 330
// Section: 001
//
// Assignment: Homework 4
// Due Date: November 19th, 2024
//
// Description:
//
//     * TODO
//
// Acknowledgments:
//
//     * TODO
//
//---------------------------------------------------------------------

#include "player_move.h"

PlayerMove::PlayerMove()
{
    // Default constructor for PlayerMove, initalizes row and column indices to -1
    this->_columnIndex = -1;
    this->_rowIndex = -1;
}

PlayerMove::PlayerMove(int rowIndex, int columnIndex)
{
    // Constructor for PlayerMovie with specific row and column indices
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
}

PlayerMove::PlayerMove(const PlayerMove &playerTurn)
{
    // Copy constructor for PlayerMove, creates a copy of another PlayerMove object
    this->_columnIndex = playerTurn._columnIndex;
    this->_rowIndex = playerTurn._rowIndex;
}

bool PlayerMove::operator==(const PlayerMove &rightHandMove) const
{
    // Equality operator for comparing two PlayerMove objects
    return this == &rightHandMove;
}

bool PlayerMove::operator!=(const PlayerMove &rightHandMove) const
{
    // Use the equality operator to determine if the objects are not equal.
    return this != &rightHandMove;
}