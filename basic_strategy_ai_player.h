#ifndef _BASIC_STRATEGY_AI_PLAYER_H_
#define _BASIC_STRATEGY_AI_PLAYER_H_

#include "game_board_slot.h"
#include "game_board.h"

#include "player.h"
#include "player_turn.h"

// `class BasicStrategyAIPlayer`
//
// Represents a player controller that performs basic heuristics
// to locate where to draw lines.
//
// TODO: add example illustrations
class BasicStrategyAIPlayer : public Player
{
private:
    static int _computeSurroundingLineCount(
        const GameBoard &gameBoard, int rowIndex, int columnIndex, SimpleHashMap<int, SimpleVector<const GameBoardSlot *>, 99 * 99> &legalSlotsLookup);

public:
    using Player::Player;

    PlayerTurn *computePlayerTurn(
        const GameSession &gameSession, const GameBoard &gameBoard) const;
};

#endif