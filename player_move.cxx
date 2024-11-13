#include "player_move.h"

PlayerMove::PlayerMove()
{
    this->_columnIndex = -1;
    this->_rowIndex = -1;
}

PlayerMove::PlayerMove(int rowIndex, int columnIndex)
{
    this->_columnIndex = columnIndex;
    this->_rowIndex = rowIndex;
}

PlayerMove::PlayerMove(const PlayerMove &playerTurn)
{
    this->_columnIndex = playerTurn._columnIndex;
    this->_rowIndex = playerTurn._rowIndex;
}

bool PlayerMove::operator==(const PlayerMove &rightHandMove) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandMove;
}

bool PlayerMove::operator!=(const PlayerMove &rightHandMove) const
{
    // See `PlayerMove::operator==` for reasoning.
    return this != &rightHandMove;
}