#ifndef _GAME_SESSION_H_
#define _GAME_SESSION_H_

#include "simple_vector.h"

#include "player.h"
#include "game_board.h"

// `class GameSession`
//
// Represents a game session of a Dots and Boxes game. It handles the keeping of
// turn orders and prompting of players to make their turn.
class GameSession
{
private:
    const Player &_determineNextPlayer() const;

protected:
    // `SimpleVector<Player> GameSession._players`
    //
    // Represents the players who are participating in the Dots and Boxes game.
    const SimpleVector<Player> *_players;

    // `int GameSession._turnIndex`
    //
    // Represents the index of the current turn to be yet performed.
    int _turnIndex;

public:
    GameSession();
    GameSession(const SimpleVector<Player> *players, int turnIndex = 0);

    GameSession(const GameSession &gameSession);

    ~GameSession();

    bool operator==(const GameSession &rightHandSession) const;
    bool operator!=(const GameSession &rightHandSession) const;

    const SimpleVector<Player> &players() const { return *this->_players; }
    int turnIndex() const { return this->_turnIndex; }
};

#endif