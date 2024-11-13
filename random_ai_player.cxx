#include <random>

#include "simple_vector.h"

#include "player_turn.h"
#include "game_board_slot.h"
#include "game_board.h"

#include "player.h"
#include "random_ai_player.h"

PlayerTurn *RandomAIPlayer::computePlayerTurn(
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

    PlayerTurn *playerTurn = new PlayerTurn(turnIndex, rowIndex, columnIndex, this->_playerInitial);

    delete legalSlots;
    return playerTurn;
}