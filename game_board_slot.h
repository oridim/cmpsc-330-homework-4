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
//       contains data for a gameboard grid slot from a Dots and Boxes game.
//
//---------------------------------------------------------------------

#ifndef _GAME_BOARD_SLOT_H_
#define _GAME_BOARD_SLOT_H_

#include "player_turn.h"

// `class GameBoardSlot`
//
// Represents structured data that contains information about a specific gameboard
// slot in the Dots and Boxes grid.
class GameBoardSlot
{
    friend class GameBoard;

public:
    // `enum int GameBoardSlot::SLOT_KIND`
    //
    // Represents an enumeration of the various kinds of gameboard slots there can
    // be in a Dots and Boxes game.
    enum class SLOT_KIND
    {
        // `GameBoardSlot::SLOT_KIND::undefined`
        //
        // Represents that the gameboard slot is currently an undefined kind.
        undefined,

        // `GameBoardSlot::SLOT_KIND::dot`
        //
        // Represents that the gameboard slot is an unplayable boundary of the
        // gameboard grid.
        //
        // **NOTE**: This is the default kind due to being the first kind.
        dot,

        // `GameBoardSlot::SLOT_KIND::scorable`
        //
        // Represents that the gameboard slot is an uncaptured box that players
        // can claim if they are the final player to surround the box with a line.
        scorable,

        // `GameBoardSlot::SLOT_KIND::spacer`
        //
        // Represents that the gameboard slot is where players can draw a line to
        // start the process of capturing a box on all four sides.
        spacer,

        // `GameBoardSlot::SLOT_KIND::initial`
        //
        // Represents is a scorable game piece that has been captured and initialed by
        // the final player to draw a line(s) around the box.
        initial,

        // `GameBoardSlot::SLOT_KIND::line`
        //
        // Represents a spacer game piece that has had a line drawn through it by
        // a player.
        line,
    };

    // `GameBoardSlot::SLOT_KIND GameBoardSlot::determineSlotKind(int rowIndex, int columnIndex)`
    //
    // Returns the `GameBoardSlot::SLOT_KIND` based on grid slot semantics after
    // a MxN grid of dots has been expanded to (M+(M-1))x(N+(N-1)) to include
    // space for boundary dots, line spacers, and scorable boxes.
    //
    // The following semantics are observed when returning a `GameBoardSlot::SLOT_KIND`:
    //
    //     - `GameBoardSlot::SLOT_KIND::dot` - If both `row` and `column` are even.
    //     - `GameBoardSlot::SLOT_KIND::scorable` - If both `row` and `column` are odd.
    //     - `GameBoardSlot::SLOT_KIND::spacer` - If both `row` and `column` are
    //       mismatched parities.
    static SLOT_KIND determineSlotKind(int rowIndex, int columnIndex);

private:
    // `int GameBoardSlot._columnIndex`
    //
    // Represents what column in the Dots and Boxes gameboard grid that this
    // gameboard slot is located at.
    int _columnIndex;

    // `char GameBoardSlot._displayCharacter`
    //
    // Represents the character used to render the gameboard slot when the
    // Dots and Boxes gameboard grid is serialized.
    char _displayCharacter;

    // `int GameBoardSlot._rowIndex`
    //
    // Represents what row in the Dots and Boxes gameboard grid that this
    // gameboard slot is located at.
    int _rowIndex;

    // `GameBoardSlot::SLOT_KIND GameBoardSlot._slotKind`
    //
    // Represents the kind of gameboard slot this instance of `GameBoardSlot` is.
    //
    // **SEE**: `GameBoardSlot::SLOT_KIND` for more details.
    SLOT_KIND _slotKind;

    // `PlayerTurn *GameBoardSlot._playerTurn`
    //
    // Represents the `PlayerTurn` turn move performed on this gameboard
    // slot, if any was defined, otherwise `nullptr`.
    const PlayerTurn *_playerTurn;

    void _applyUpdate(SLOT_KIND kind);
    void _applyUpdate(SLOT_KIND kind, const PlayerTurn &playerTurn);

public:
    GameBoardSlot();
    GameBoardSlot(int rowIndex, int columnIndex);
    GameBoardSlot(int rowIndex, int columnIndex, SLOT_KIND kind);
    GameBoardSlot(
        int rowIndex, int columnIndex, SLOT_KIND slotKind, const PlayerTurn &playerTurn);

    GameBoardSlot(const GameBoardSlot &gameBoardSlot);

    bool operator==(const GameBoardSlot &rightHandSlot) const;
    bool operator!=(const GameBoardSlot &rightHandSlot) const;

    int columnIndex() const { return this->_columnIndex; }
    char displayCharacter() const { return this->_displayCharacter; }
    int rowIndex() const { return this->_rowIndex; }
    const PlayerTurn &playerTurn() const { return *this->_playerTurn; }
    SLOT_KIND slotKind() const { return this->_slotKind; }

    // `bool GameBoardSlot.isLegalMove()`
    //
    // Returns `true` if the gameboard grid slot is available as a legal move
    // to players.
    //
    // Generally this function just checks if `GameBoardSlot.kind` is equal
    // to `GameBoardSlot::SLOT_KIND::spacer`.
    bool isLegalMove() const;

    // `bool GameBoardSlot.wasMovePerformed()`
    //
    // Returns `true` is this `GameBoardSlot` instance was initialized
    // with a `PlayerTurn` was performed on it
    bool wasMovePerformed() const;
};

#endif