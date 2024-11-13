#ifndef _GAME_SESSION_H_
#define _GAME_SESSION_H_

#include "simple_vector.h"

#include "game_board.h"

#include "player.h"
#include "player_turn.h"

// TODO: `GameSession` does not track turns player take in a vector or anything of
// that nature.
//
// If we need undos in the future or want to serialize this data, we should fix
// that.

// `class GameSession`
//
// Represents a game session of a Dots and Boxes game. It handles the keeping of
// turn orders and prompting of players to make their turn.
class GameSession
{
private:
    const Player &_determineNextPlayer() const;

protected:
    // `SimpleVector<Player *> GameSession._players`
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
    const SimpleVector<Player *> *_players;

    // `int GameSession._turnIndex`
    //
    // Represents the index of the current turn to be yet performed.
    int _turnIndex;

public:
    GameSession();
    GameSession(const SimpleVector<Player *> *players, int turnIndex = 0);

    ~GameSession();

    bool operator==(const GameSession &rightHandSession) const;
    bool operator!=(const GameSession &rightHandSession) const;

    const SimpleVector<Player *> &players() const { return *this->_players; }
    int turnIndex() const { return this->_turnIndex; }

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
};

#endif