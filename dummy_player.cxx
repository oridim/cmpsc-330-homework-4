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
    // Constructor for DummyPlayer
    this->_playerInitial = playerInitial;
}

PlayerMove *DummyPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    // Since this is a dummy player, the method throws an exception to indicate that
    // it is not yet implemented or usable in its current form
    throw string("bad argument #0 to 'DummyPlayer.computePlayerMove(const GameSession &, const GameBoard &)' (not implemented)");
}