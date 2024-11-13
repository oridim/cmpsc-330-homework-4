#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "game_board.h"

#include "player_move.h"

// **HACK**: We have a circular dependency here `GameSession` and `Player` both
// needing to know about each other.
//
// To get around this, we simply need to forward declare `GameSession` as a
// "dummy" class here.
//
// `player.cxx` can include the real `game_session.h` to get the proper
// shape of the class without errors.
//
// One of the benefits of seperating class definitions from class implmentations ^^.
class GameSession;

// `class Player`
//
// Represents a common abstract class interface that different types of player
// controllers inherit from.
//
// This allows for `GameSession` to generically handle different types of
// player controllers without having to be explicitly typed for them.
class Player
{
protected:
    // `char Player._playerInitial`
    //
    // Represents the initial that identifies the given player.
    char _playerInitial;

public:
    char playerInitial() const { return this->_playerInitial; }

    virtual ~Player() = 0;

    // `PlayerMove *Player.computePlayerMove(const GameSession &gameSession, const GameBoard &gameBoard)`
    //
    // Returns a `PlayerMove` instance pointer if the player controller
    // was available to calculate a move it could take with the given
    // game state.
    //
    // Otherwise, a `nullptr` is returned.
    virtual PlayerMove *computePlayerMove(
        const GameSession &gameSession, const GameBoard &gameBoard) const = 0;
};

Player::~Player() {}

#endif