#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "player_turn.h"
#include "game_board.h"

// `class Player`
//
// Represents a common interface that different types of player controllers
// inherit from.
//
// This allows for `GameSession` to generically handle different types of
// player controllers without having to be explicitly typed for them.
class Player
{
private:
    // `char Player._playerInitial`
    //
    // Represents the initial that identifies the given player.
    char _playerInitial;

public:
    Player();
    Player(char playerInitial);

    Player(const Player &Player);

    bool operator==(const Player &rightHandPlayer) const;
    bool operator!=(const Player &rightHandPlayer) const;

    char playerInitial() const { return this->_playerInitial; }

    // `PlayerTurn.computePlayerTurn(const GameBoard &gameBoard)`
    //
    // Returns a `PlayerTurn` instance pointer if the player controller
    // was available to calculate an action it could take with the given
    // gameboard state.
    //
    // Otherwise, a `nullptr` is returned.
    virtual PlayerTurn *computePlayerTurn(const GameBoard &gameBoard) const;
};

#endif