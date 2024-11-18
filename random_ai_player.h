#ifndef _RANDOM_AI_PLAYER_H_
#define _RANDOM_AI_PLAYER_H_

#include "player.h"
#include "player_move.h"

// `class RandomAIPlayer`
//
// Represents a player controller that strictly picks a random move to make
// from the available list of moves to make.
class RandomAIPlayer : public Player
{
public:
    using Player::Player;

    RandomAIPlayer(char playerInitial);

    // `PlayerMove RandomAIPlayer.computePlayerMove(const GameSession &gameSession, const GameBoard &gameBoard)`
    //
    // Returns a pointer to a new `PlayerMove` instance if the `RandomAIPlayer`
    // instance was able to compute a move to make.
    //
    // Otherwise, `nullptr` is returned.
    //
    // It computes the move by selecting a randomly available gameboard grid
    // slot that is open and is a legal move.
    virtual PlayerMove *computePlayerMove(
        const GameSession &gameSession, const GameBoard &gameBoard) const override;
};

#endif