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

#include "player_turn.h"

PlayerTurn::PlayerTurn()
{
    // Default constructor for PlayerTurn
    this->_columnIndex = -1;
    this->_turnIndex = -1;
    this->_rowIndex = -1;
    this->_playerInitial = '\0';
}

PlayerTurn::PlayerTurn(int turnIndex, int rowIndex, int columnIndex, char playerInitial)
{
    // Allows initialization for specific values for turn index, row index, column index
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
    this->_playerInitial = playerInitial;
    this->_turnIndex = turnIndex;
}

PlayerTurn::PlayerTurn(const PlayerMove &playerMove, int turnIndex, char playerInitial)
{
    // Constructor for PlayerTurn using a PlayerMove object
    this->_columnIndex = playerMove.columnIndex();
    this->_rowIndex = playerMove.rowIndex();
    this->_playerInitial = playerInitial;
    this->_turnIndex = turnIndex;
}

PlayerTurn::PlayerTurn(const PlayerTurn &playerTurn)
{
    // Copies constructor for PlayerTurn
    this->_columnIndex = playerTurn._columnIndex;
    this->_rowIndex = playerTurn._rowIndex;
    this->_playerInitial = playerTurn._playerInitial;
    this->_turnIndex = playerTurn._turnIndex;
}

bool PlayerTurn::operator==(const PlayerTurn &rightHandTurn) const
{
    // Equality operator to compare PlayerTurn object by instance (nominal instances)
    return this == &rightHandTurn;
}

bool PlayerTurn::operator!=(const PlayerTurn &rightHandTurn) const
{
    // Inequality operator, opposite of the equality operator.
    return this != &rightHandTurn;
}