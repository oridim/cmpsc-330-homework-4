#ifndef _RANDOM_AI_PLAYER_H_
#define _RANDOM_AI_PLAYER_H_

#include "player.h"
#include "player_turn.h"

// `class RandomAIPlayer`
//
// Represents a player controller that strictly picks a random move to make
// from the available list of moves to make.
class RandomAIPlayer : public Player
{
public:
    using Player::Player;

    PlayerTurn *computePlayerTurn(
        const GameSession &gameSession, const GameBoard &gameBoard) const;
};

#endif