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
//     * This file provides type definitions for a data structure that
//       contains data about a move a player is about to make.
//
//---------------------------------------------------------------------

#ifndef _PLAYER_MOVE_H_
#define _PLAYER_MOVE_H_

// `class PlayerMove`
//
// Represents structured data containing a move computed by a player.
class PlayerMove
{
protected:
    // `int PlayerMove._columnIndex`
    //
    // Represents what column in the Dots and Boxes gameboard grid that this move
    // was performed.
    int _columnIndex;

    // `int PlayerMove._rowIndex`
    //
    // Represents what row in the Dots and Boxes gameboard grid that this move was
    // performed.
    int _rowIndex;

public:
    PlayerMove();
    PlayerMove(int row, int column);

    PlayerMove(const PlayerMove &playerMove);

    bool operator==(const PlayerMove &rightHandMove) const;
    bool operator!=(const PlayerMove &rightHandMove) const;

    int columnIndex() const { return this->_columnIndex; }
    int rowIndex() const { return this->_rowIndex; }
};

#endif