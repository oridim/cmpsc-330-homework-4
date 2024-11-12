#include <random>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "player_turn.h"
#include "game_board.h"
#include "game_board_slot.h"

#include "player.h"
#include "basic_strategy_ai_player.h"

// TODO: Refactor `BasicStrategyAIPlayer.computePlayerTurn` to use cache
// the legal on the first loop so we do not have to loop again and properly
// randomize our picks.

int BasicStrategyAIPlayer::_computeSurroundingLineCount(const GameBoard &gameBoard, int rowIndex, int columnIndex)
{
    int lineCount = 0;

    for (int deltaRowIndex = -1; deltaRowIndex <= 1; deltaRowIndex += 2)
    {
        const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex + deltaRowIndex, columnIndex);

        if (deltaBoardSlot.slotKind() == GameBoardSlot::SLOT_KIND::line)
        {
            lineCount += 1;
        }
    }

    for (int deltaColumnIndex = -1; deltaColumnIndex <= 1; deltaColumnIndex += 2)
    {
        const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex, columnIndex + deltaColumnIndex);

        if (deltaBoardSlot.slotKind() == GameBoardSlot::SLOT_KIND::line)
        {
            lineCount += 1;
        }
    }

    return lineCount;
}

const GameBoardSlot &BasicStrategyAIPlayer::_determineLegalSlot(const GameBoard &gameBoard, int rowIndex, int columnIndex)
{
    // HACK: Yeah... duplicate code, crappy code, meh code...
    //
    // But until the refactor comes, we some what want to randomize our pick.

    // We using the parity of our randomly generated number to determine if we
    // search vertically or horizontally first in a 50-50% chance split.
    if ((rand() % 2) == 0)
    {
        for (int deltaRowIndex = -1; deltaRowIndex <= 1; deltaRowIndex += 2)
        {
            const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex + deltaRowIndex, columnIndex);

            if (deltaBoardSlot.isLegalMove())
            {
                return deltaBoardSlot;
            }
        }

        for (int deltaColumnIndex = -1; deltaColumnIndex <= 1; deltaColumnIndex += 2)
        {
            const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex, columnIndex + deltaColumnIndex);

            if (deltaBoardSlot.isLegalMove())
            {
                return deltaBoardSlot;
            }
        }
    }
    else
    {
        for (int deltaColumnIndex = -1; deltaColumnIndex <= 1; deltaColumnIndex += 2)
        {
            const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex, columnIndex + deltaColumnIndex);

            if (deltaBoardSlot.isLegalMove())
            {
                return deltaBoardSlot;
            }
        }

        for (int deltaRowIndex = -1; deltaRowIndex <= 1; deltaRowIndex += 2)
        {
            const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex + deltaRowIndex, columnIndex);

            if (deltaBoardSlot.isLegalMove())
            {
                return deltaBoardSlot;
            }
        }
    }

    // **NOTE**: We do not have a base case return here. But, since
    // `_determineSlotPick` was called, that means at least ONE
    // surrounding grid slot was available... should... anyway...
}

PlayerTurn *BasicStrategyAIPlayer::computePlayerTurn(const GameBoard &gameBoard) const
{
    SimpleVector<GameBoardSlot> *scorableSlots = gameBoard.computeScorableSlots();
    if (scorableSlots->size() == 0)
    {
        return nullptr;
    }

    int highestLineCount = 0;
    SimpleHashMap<int, SimpleVector<GameBoardSlot *>, 3> lineCountLookup;

    for (int index = 0; index < scorableSlots->size(); index++)
    {
        GameBoardSlot &gameBoardSlot = scorableSlots->at(index);

        int rowIndex = gameBoardSlot.rowIndex();
        int columnIndex = gameBoardSlot.columnIndex();

        int surroundingLineCount = _computeSurroundingLineCount(
            gameBoard, rowIndex, columnIndex);

        SimpleVector<GameBoardSlot *> &lineCountCache = lineCountLookup.at(surroundingLineCount);

        lineCountCache.push_back(&gameBoardSlot);

        if (surroundingLineCount > highestLineCount)
        {
            highestLineCount = surroundingLineCount;
        }
    }

    SimpleVector<GameBoardSlot *> *scorableBoardSlots;

    switch (highestLineCount)
    {
    case 0:
    case 1:
    case 3:
    {
        // If the highest line count IS scorable boxes surrounded by 3, 1, or no
        // lines, then we just pick one of those.
        scorableBoardSlots = &lineCountLookup.at(highestLineCount);
        break;
    }

    case 2:
    {
        // If the highest line count IS scorable boxes surrounded by 2
        // lines, then we want to priority 1, no, and 2 lines in that order.
        scorableBoardSlots = &lineCountLookup.at(1);
        if (scorableBoardSlots->size() == 0)
        {
            scorableBoardSlots = &lineCountLookup.at(0);

            if (scorableBoardSlots->size() == 0)
            {
                scorableBoardSlots = &lineCountLookup.at(2);
            }
        }

        break;
    }
    }

    // Humans think randomly! So, let's emulate potential poor life choices!
    int index = rand() % scorableBoardSlots->size();
    GameBoardSlot *scorableBoardSlot = scorableBoardSlots->at(index);

    const GameBoardSlot &legalBoardSlot = _determineLegalSlot(
        gameBoard, scorableBoardSlot->rowIndex(), scorableBoardSlot->columnIndex());

    int columnIndex = legalBoardSlot.columnIndex();
    int rowIndex = legalBoardSlot.rowIndex();
    int turnIndex = gameBoard.turnIndex() + 1;

    PlayerTurn *playerTurn = new PlayerTurn(turnIndex, rowIndex, columnIndex, this->_playerInitial);

    delete scorableSlots;

    return playerTurn;
}