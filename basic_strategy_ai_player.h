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

#ifndef _BASIC_STRATEGY_AI_PLAYER_H_
#define _BASIC_STRATEGY_AI_PLAYER_H_

#include "game_board_slot.h"
#include "game_board.h"

#include "player.h"
#include "player_move.h"

// `class BasicStrategyAIPlayer`
//
// Represents a player controller that performs basic heuristics
// to locate where to draw lines.
//
// **TODO**: add example illustrations
class BasicStrategyAIPlayer : public Player
{
private:
    // `int BasicStrategyAIPlayer::_computeSurroundingLineCount(const GameBoard &gameBoard, int rowIndex, int columnIndex, SimpleHashMap<int, SimpleVector<const GameBoardSlot *>, 99 * 99> &legalSlotsLookup)`
    //
    // Returns the number of lines surrounding a particular slot in the gameboard
    // grid.
    //
    // The lines are computed by iterating searching +-1 horizontally and
    // +-1 vertically from the supplied `rowIndex` and `columnIndex` respectively.
    static int _computeSurroundingLineCount(
        const GameBoard &gameBoard, int rowIndex, int columnIndex, SimpleHashMap<int, SimpleVector<const GameBoardSlot *>, 99 * 99> &legalSlotsLookup);

public:
    using Player::Player;

    BasicStrategyAIPlayer(char playerInitial);

    // `PlayerMove RandomAIPlayer.computePlayerMove(const GameSession &gameSession, const GameBoard &gameBoard)`
    //
    // Returns a pointer to a new `PlayerMove` instance if the `BasicStrategyAIPlayer`
    // instance was able to compute a move to make.
    //
    // Otherwise, `nullptr` is returned.
    //
    // It computes the move by utilizing a prioritization system to select a
    // scorable box to draw a line around.
    //
    // 1. If the highest line count around scorable boxes is 3, then a random
    //    box from that pool is selected.
    // 2. If the highest line count around scorable boxes is 1, then the random
    //    randomly pulled from the pools of 0 and 1 line surrounded scorable boxes.
    // 3. If the highest line count around scorable boxes is 0, then a random box
    //    is selected.
    // 4. If the highest line count around scorable boxes is 2, then a random
    //    box from that pool is selected.
    //
    // Once a scorable box is selected a random line is drawn on an available
    // space around it.
    virtual PlayerMove *computePlayerMove(
        const GameSession &gameSession, const GameBoard &gameBoard) const override;
};

#endif