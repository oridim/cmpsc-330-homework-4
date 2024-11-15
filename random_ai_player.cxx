#include <random>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board.h"

#include "game_session.h"

#include "player.h"
#include "player_move.h"

#include "random_ai_player.h"

// Constructor for RandomAIPlayer.
// Initializes the player with the given player initial.
// 'playerInitial': A character representing the player's identifier.
RandomAIPlayer::RandomAIPlayer(char playerInitial)
{
    this->_playerInitial = playerInitial;
}

// Computes the next move for the AI player using random selection.
// Returns a 'PlayerMove' object representing the randomly chosen move, or 'nullptr' if no legal moves are available.
PlayerMove *RandomAIPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    // Compute all legal slots
    SimpleVector<GameBoardSlot> *legalSlots = gameBoard.computeLegalSlots();
    if (legalSlots->size() == 0)
    {
        return nullptr;
    }
    // Select a random legal slot index within the range of available slots.
    int index = rand() % legalSlots->size();
    GameBoardSlot &gameBoardSlot = legalSlots->at(index);

    int columnIndex = gameBoardSlot.columnIndex();
    int rowIndex = gameBoardSlot.rowIndex();
    // Create a new 'PlayerMove' object with the selected slot's row and column indices.
    PlayerMove *playerTurn = new PlayerMove(rowIndex, columnIndex);

    delete legalSlots;
    return playerTurn;
}