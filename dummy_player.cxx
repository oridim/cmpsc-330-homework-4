#include <random>
#include <string>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board.h"

#include "game_session.h"

#include "player.h"
#include "player_move.h"

#include "dummy_player.h"

DummyPlayer::DummyPlayer(char playerInitial)
{
    this->_playerInitial = playerInitial;
}

PlayerMove *DummyPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    throw string("bad argument #0 to 'DummyPlayer.computePlayerMove(const GameSession &, const GameBoard &)' (not implemented)");
}