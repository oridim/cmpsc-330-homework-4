#ifndef _PLAYER_TURN_H_
#define _PLAYER_TURN_H_

#include "player_move.h"

// `class PlayerTurn`
//
// Represents structured data containing a turn completed by a player.
class PlayerTurn : public PlayerMove
{
    using PlayerMove::PlayerMove;

private:
    // `char PlayerTurn._playerInitial`
    //
    // Represents the initial of the player who placed the move onto the Dots and Boxes
    // gameboard grid.
    char _playerInitial;

    // `int PlayerTurn._turnIndex`
    //
    // Represents the indexing number in the order in which turn actions were
    // performed on the Dots and Boxes gameboard grid.
    //
    // The indexing is determined by the owning container type.
    // (ex. `GameData` / `GameManager`)
    int _turnIndex;

public:
    PlayerTurn();
    PlayerTurn(int turnIndex, int row, int column, char playerInitial);

    PlayerTurn(const PlayerTurn &playerTurn);

    bool operator==(const PlayerTurn &rightHandTurn) const;
    bool operator!=(const PlayerTurn &rightHandTurn) const;

    char playerInitial() const { return this->_playerInitial; }
    int turnIndex() const { return this->_turnIndex; }
};

#endif