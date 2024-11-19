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
//     * This file implements a data structure that contains data for
//       a gameboard grid slot from a Dots and Boxes game.
//
//---------------------------------------------------------------------

#include <string>

#include "game_board_slot.h"

#include "player_turn.h"

using namespace std;

GameBoardSlot::SLOT_KIND GameBoardSlot::determineSlotKind(int rowIndex, int columnIndex)
{
    if ((columnIndex % 2 == 0) && (rowIndex % 2 == 0))
    {
        // Even row and column indices indicate a dot
        return SLOT_KIND::dot;
    }
    else if ((columnIndex % 2 != 0) && (rowIndex % 2 != 0))
    {
        // Odd row and column indices indicate a scorable
        return SLOT_KIND::scorable;
    }

    return SLOT_KIND::spacer;
}

GameBoardSlot::GameBoardSlot()
{
    this->_columnIndex = -1;
    this->_rowIndex = -1;

    this->_displayCharacter = '\0';
    this->_slotKind = SLOT_KIND::undefined;
    // No player is associated initially.
    this->_playerTurn = nullptr;
}

GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;

    this->_displayCharacter = '\0';
    this->_slotKind = SLOT_KIND::undefined;
    this->_playerTurn = nullptr;
}

GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex, SLOT_KIND slotKind)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;

    // Update properties based on the slot kind.
    this->_applyUpdate(slotKind);
}

GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex, SLOT_KIND slotKind, const PlayerTurn &playerTurn)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;

    this->_applyUpdate(slotKind, playerTurn);
}

GameBoardSlot::GameBoardSlot(const GameBoardSlot &gameBoardSlot)
{
    this->_columnIndex = gameBoardSlot._columnIndex;
    this->_rowIndex = gameBoardSlot._rowIndex;

    this->_displayCharacter = gameBoardSlot._displayCharacter;
    this->_slotKind = gameBoardSlot._slotKind;

    this->_playerTurn = gameBoardSlot._playerTurn;
}

bool GameBoardSlot::operator==(const GameBoardSlot &rightHandSlot) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandSlot;
}

bool GameBoardSlot::operator!=(const GameBoardSlot &rightHandSlot) const
{
    // See `GameBoardSlot::operator==` for reasoning.
    return this != &rightHandSlot;
}

void GameBoardSlot::_applyUpdate(SLOT_KIND slotKind)
{
    switch (slotKind)
    {
    case SLOT_KIND::dot:
        this->_displayCharacter = '.';
        break;

    case SLOT_KIND::scorable:
    case SLOT_KIND::spacer:
        this->_displayCharacter = ' ';
        break;

    default:
        // Throw an error if the slot kind is invalid
        throw string("bad argument #0 to 'GameBoardSlot._applyUpdate(SLOT_KIND)' (cannot update 'GameBoardSlot' with 'SLOT_KIND' '") + to_string(static_cast<int>(slotKind)) + string("')");
    }

    // Updates slot kind and Clears any player association
    this->_slotKind = slotKind;
    this->_playerTurn = nullptr;
}

void GameBoardSlot::_applyUpdate(SLOT_KIND slotKind, const PlayerTurn &playerTurn)
{
    switch (slotKind)
    {
    case SLOT_KIND::initial:
        this->_displayCharacter = char(toupper(playerTurn.playerInitial()));
        break;

    case SLOT_KIND::line:
        this->_displayCharacter = char(tolower(playerTurn.playerInitial()));
        break;

    default:
        throw string("bad argument #0 to 'GameBoardSlot._applyUpdate(SLOT_KIND)' (cannot update 'GameBoardSlot' with 'SLOT_KIND' '") + to_string(static_cast<int>(slotKind)) + string("')");
    }

    this->_slotKind = slotKind;
    this->_playerTurn = &playerTurn;
}

bool GameBoardSlot::isLegalMove() const
{
    return this->_slotKind == SLOT_KIND::spacer && this->_playerTurn == nullptr;
}

bool GameBoardSlot::wasMovePerformed() const
{
    return this->_playerTurn != nullptr;
}