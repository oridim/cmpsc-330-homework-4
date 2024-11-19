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

#ifndef _GAME_SESSION_H_
#define _GAME_SESSION_H_

#include "simple_vector.h"

#include "game_board.h"

#include "player.h"
#include "player_turn.h"

// `class GameSession`
//
// Represents a game session of a Dots and Boxes game. It handles the keeping of
// turn orders and prompting of players to make their turn.
class GameSession
{
private:
    // `const Player &GameSession._determineNextPlayer()`
    //
    // Returns the next player in the turn order queue.
    const Player &_determineNextPlayer() const;

    // `void GameSession._shiftTurnOrder()`
    //
    // Pops the player in the front of the turn order queue
    // and pushes them into the back.
    void _shiftTurnOrder();

protected:
    // `SimpleVector<const Player *> GameSession._players`
    //
    // Represents the players who are participating in the Dots and Boxes game.
    //
    // **HACK**: We are using pointers here. Thus, we are negating the automagic
    // memory management provided by `SimpleVector`.
    //
    // However! This allows us to use subclass method overrides properly.
    //
    // BUT! There is another downside. We cannot implement copy constructors for
    // `GameSession`.
    //
    // It would just make new instances of `Player` instead of the subclass.
    SimpleVector<const Player *> *_players;

    // `SimpleVector<const PlayerTurn *> GameSession._turns`
    //
    // Represents the a vector of all the turns taken so far.
    SimpleVector<const PlayerTurn *> *_turns;

public:
    GameSession();
    GameSession(SimpleVector<const Player *> *players);
    GameSession(SimpleVector<const Player *> *players, const SimpleVector<PlayerTurn> turns);

    ~GameSession();

    bool operator==(const GameSession &rightHandSession) const;
    bool operator!=(const GameSession &rightHandSession) const;

    const SimpleVector<const Player *> &players() const { return *this->_players; }
    const SimpleVector<const PlayerTurn *> &turns() const { return *this->_turns; };

    // `PlayerTurn *GameSession.computeNextPlayerTurn(const GameBoard &gameBoard)`
    //
    // Returns a pointer to a `PlayerTurn` instance if the next player was
    // able to compute a valid move and it was applied
    //
    // Otherwise, `nullptr` is returned.
    PlayerTurn *applyNextPlayerTurn(GameBoard &gameBoard);

    // `PlayerTurn *GameSession.computeNextPlayerTurn(const GameBoard &gameBoard)`
    //
    // Returns a pointer to a `PlayerTurn` instance if the next player was
    // able to compute a valid move.
    //
    // Otherwise, `nullptr` is returned.
    PlayerTurn *computeNextPlayerTurn(const GameBoard &gameBoard) const;

    // `int GameSession.nextTurnIndex()`
    //
    // Represents the index of the next turn to be yet performed.
    int nextTurnIndex() const;
};

#endif