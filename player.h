#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "game_board.h"

#include "player_turn.h"

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
// Represents a common interface that different types of player controllers
// inherit from.
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
    virtual PlayerTurn *computePlayerTurn(const GameSession &gameSession, const GameBoard &gameBoard) const;
};

#endif