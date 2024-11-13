#include <random>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board.h"

#include "game_session.h"

#include "player.h"
#include "player_move.h"

#include "random_ai_player.h"

PlayerMove *RandomAIPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    SimpleVector<GameBoardSlot> *legalSlots = gameBoard.computeLegalSlots();
    if (legalSlots->size() == 0)
    {
        return nullptr;
    }

    int index = rand() % legalSlots->size();
    GameBoardSlot &gameBoardSlot = legalSlots->at(index);

    int columnIndex = gameBoardSlot.columnIndex();
    int rowIndex = gameBoardSlot.rowIndex();
    int turnIndex = gameSession.turnIndex() + 1;

    PlayerMove *playerTurn = new PlayerMove(rowIndex, columnIndex);

    delete legalSlots;
    return playerTurn;
}