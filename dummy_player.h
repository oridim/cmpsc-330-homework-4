#ifndef _DUMMY_PLAYER_H_
#define _DUMMY_PLAYER_H_

#include "player.h"
#include "player_move.h"

// `class DummyPlayer`
//
// Represents that is strictly used for testing and putting butts in seats.
class DummyPlayer : public Player
{
public:
    using Player::Player;

    DummyPlayer(char playerInitial);

    virtual PlayerMove *computePlayerMove(
        const GameSession &gameSession, const GameBoard &gameBoard) const override;
};

#endif