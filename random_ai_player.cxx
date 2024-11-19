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
//     * This file implements an AI Dots and Boxes player who lines to place
//       on the gameboard grid at random.
//
//---------------------------------------------------------------------

#include <random>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board.h"

#include "game_session.h"

#include "player.h"
#include "player_move.h"

#include "random_ai_player.h"

RandomAIPlayer::RandomAIPlayer(char playerInitial)
{
    // Initializes the player with the given player initial.
    // 'playerInitial': A character representing the player's identifier.
    this->_playerInitial = playerInitial;
}

PlayerMove *RandomAIPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    if (gameBoard.remainingCaptures() == 0)
    {
        // Returns a 'PlayerMove' object representing the randomly chosen move, or 'nullptr' if no legal moves are available.
        return nullptr;
    }

    SimpleVector<GameBoardSlot> *legalSlots = gameBoard.computeLegalSlots();

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