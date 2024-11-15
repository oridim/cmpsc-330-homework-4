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

// Default constructor for GameBoardSlot.
// Initialozes the slot with invalid indices and undefined prooperties.
GameBoardSlot::GameBoardSlot()
{
    this->_columnIndex = -1;
    this->_rowIndex = -1;

    this->_displayCharacter = '\0';
    this->_slotKind = SLOT_KIND::undefined;
    // No player is associated initially.
    this->_playerTurn = nullptr;
}

// Constructor initializing a GameBoardSlot with row and column inidices.
// Leaves other properties undefined.
GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;

    this->_displayCharacter = '\0';
    this->_slotKind = SLOT_KIND::undefined;
    this->_playerTurn = nullptr;
}

// Constructor initialzing a GameBoardSlot with row, column, and slot kind. 
// Applies the slot kind to define the display character and other properties.
GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex, SLOT_KIND slotKind)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
    
    // Update properties based on the slot kind.
    this->_applyUpdate(slotKind);
}

// Constructor initializing a GameBoardSlot with row, column, slot kind, and a player turn.
// Updates the slot kind and associates it with the specified player turn.
GameBoardSlot::GameBoardSlot(int rowIndex, int columnIndex, SLOT_KIND slotKind, const PlayerTurn &playerTurn)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;

    this->_applyUpdate(slotKind, playerTurn);
}

// Copy constructor for GameBoardSlot
// Copies all properties from an existing slot to the new one. 
GameBoardSlot::GameBoardSlot(const GameBoardSlot &gameBoardSlot)
{
    this->_columnIndex = gameBoardSlot._columnIndex;
    this->_rowIndex = gameBoardSlot._rowIndex;

    this->_displayCharacter = gameBoardSlot._displayCharacter;
    this->_slotKind = gameBoardSlot._slotKind;

    this->_playerTurn = gameBoardSlot._playerTurn;
}

// Equalty operator to compare two  GameBoardSlot instances.
// Compares instances normally by checking if they are the same object
bool GameBoardSlot::operator==(const GameBoardSlot &rightHandSlot) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandSlot;
}
// Inequality operator to compare two GameBoardSlot instances.
// Returns true if the objects are not the same.
bool GameBoardSlot::operator!=(const GameBoardSlot &rightHandSlot) const
{
    // See `GameBoardSlot::operator==` for reasoning.
    return this != &rightHandSlot;
}

// Private method to update a GameBoardSlot with a given slot kind.
// Sets the display character and clears the associated player turn.
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

// Private method to update a GameBoardSlot with a given slot kind and player turn.
// Sets the display character based on the player and associates the player turn.
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

// Checks if the slot is a legal move
// A legal move must be a spacer and not already associated with a player.
bool GameBoardSlot::isLegalMove() const
{
    return this->_slotKind == SLOT_KIND::spacer && this->_playerTurn == nullptr;
}

// Checks if a move has been performed on this slot.
// A move is considered performed if a player turn is associated with the slot.
bool GameBoardSlot::wasMovePerformed() const
{
    return this->_playerTurn != nullptr;
}