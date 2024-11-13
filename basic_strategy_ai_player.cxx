#include <random>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board.h"
#include "game_board_slot.h"

#include "game_session.h"

#include "player.h"
#include "player_move.h"

#include "basic_strategy_ai_player.h"

int BasicStrategyAIPlayer::_computeSurroundingLineCount(
    const GameBoard &gameBoard, int rowIndex, int columnIndex, SimpleHashMap<int, SimpleVector<const GameBoardSlot *>, 99 * 99> &legalSlotsLookup)
{
    int lineCount = 0;

    for (int deltaRowIndex = -1; deltaRowIndex <= 1; deltaRowIndex += 2)
    {
        const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex + deltaRowIndex, columnIndex);

        if (deltaBoardSlot.isLegalMove())
        {
            // We are approximating a unique identifier for the `GameBoardSlot`
            // so we can look its legal moves up later.
            int boardSlotID = columnIndex + ',' + rowIndex;
            SimpleVector<const GameBoardSlot *> &legalSlots = legalSlotsLookup.at(boardSlotID);

            legalSlots.push_back(&deltaBoardSlot);
        }
        else if (deltaBoardSlot.slotKind() == GameBoardSlot::SLOT_KIND::line)
        {
            lineCount += 1;
        }
    }

    for (int deltaColumnIndex = -1; deltaColumnIndex <= 1; deltaColumnIndex += 2)
    {
        const GameBoardSlot &deltaBoardSlot = gameBoard.getSlot(rowIndex, columnIndex + deltaColumnIndex);

        if (deltaBoardSlot.isLegalMove())
        {
            int boardSlotID = columnIndex + ',' + rowIndex;
            SimpleVector<const GameBoardSlot *> &legalSlots = legalSlotsLookup.at(boardSlotID);

            legalSlots.push_back(&deltaBoardSlot);
        }
        else if (deltaBoardSlot.slotKind() == GameBoardSlot::SLOT_KIND::line)
        {
            lineCount += 1;
        }
    }

    return lineCount;
}

PlayerMove *BasicStrategyAIPlayer::computePlayerMove(
    const GameSession &gameSession, const GameBoard &gameBoard) const
{
    SimpleVector<GameBoardSlot> *scorableSlots = gameBoard.computeScorableSlots();
    if (scorableSlots->size() == 0)
    {
        return nullptr;
    }

    int highestLineCount = 0;

    // **HACK**: Preallocating a 99x99 hash table is, uh, stupidly inefficient to
    // say the least. But, that is the max grid size given to us by Dr. Na.
    //
    // And... I am currently too lazy to make `SimpleHashMap` have an internal
    // elements allocation that can grow in size.
    //
    // Need to remake it using a bucket system.
    SimpleHashMap<int, SimpleVector<GameBoardSlot *>, 3> lineCountLookup;
    SimpleHashMap<int, SimpleVector<const GameBoardSlot *>, 99 * 99> legalSlotsLookup;

    for (int index = 0; index < scorableSlots->size(); index++)
    {
        GameBoardSlot &gameBoardSlot = scorableSlots->at(index);

        int rowIndex = gameBoardSlot.rowIndex();
        int columnIndex = gameBoardSlot.columnIndex();

        int surroundingLineCount = _computeSurroundingLineCount(
            gameBoard, rowIndex, columnIndex, legalSlotsLookup);

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
    case 3:
    case 0:
        // If the highest line count IS scorable boxes surrounded by 3 or no
        // lines, then prioritize scoring from a 3 surrounding.
        //
        // Likewise, if nothing available has any lines surrounding it,
        // default to picking from that pool of boxes.
        scorableBoardSlots = &lineCountLookup.at(highestLineCount);
        break;

    case 1:
    {
        // If the highest line count IS scorable boxes surrounded by 1 line,
        // then randomly select from the 1 line or no line pool of boxes.
        int index = rand() % 2;

        scorableBoardSlots = &lineCountLookup.at(index);
        if (scorableBoardSlots->size() == 0)
        {
            // Since there are no moves available we need to switch from the
            // pool of 0 lines -> 1 lines surrounded boxes or 1 -> 0 lines
            // surrounded boxes.
            scorableBoardSlots = &lineCountLookup.at(1 - index);
        }

        break;
    }

    case 2:
    {
        // If the highest line count IS scorable boxes surrounded by 2
        // lines, then we want to prioritize 1, no, and 2 lines in that order.
        //
        // Also we do not want a random choice here since we want the `BasicStrategyAIPlayer`
        // to try to get ahead of the `RandomAIPlayer`.
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
    int scorableIndex = rand() % scorableBoardSlots->size();
    GameBoardSlot *scorableBoardSlot = scorableBoardSlots->at(scorableIndex);

    int boardSlotID = scorableBoardSlot->columnIndex() + ',' + scorableBoardSlot->rowIndex();
    SimpleVector<const GameBoardSlot *> &legalBoardSlots = legalSlotsLookup.at(boardSlotID);

    // Yay, poor choices again! Woo!
    int legalIndex = rand() % legalBoardSlots.size();
    const GameBoardSlot *legalBoardSlot = legalBoardSlots.at(legalIndex);

    int columnIndex = legalBoardSlot->columnIndex();
    int rowIndex = legalBoardSlot->rowIndex();
    int turnIndex = gameSession.turnIndex() + 1;

    PlayerMove *playerMove = new PlayerMove(rowIndex, columnIndex);

    delete scorableSlots;
    return playerMove;
}