
#include <algorithm>
#include <iostream>
#include <string>

#include "simple_hash_map.h"
#include "simple_vector.h"

#include "game_board_slot.h"

#include "player_result.h"
#include "player_turn.h"

#include "game_board.h"

using namespace std;

GameBoard::GameBoard(int rows, int columns)
{
    // **IMPORTANT**: We need to assign these values before we call computed
    // data getters! Otherwise they will calculate garbage values!
    this->_columns = columns;
    this->_rows = rows;

    int expandedRows = this->expandedRows();
    int expandedColumns = this->expandedColumns();

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows =
        new SimpleVector<SimpleVector<GameBoardSlot>>(expandedRows);

    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        SimpleVector<GameBoardSlot> *gridColumns =
            new SimpleVector<GameBoardSlot>(expandedColumns);

        for (int columnIndex = 0; columnIndex < gridColumns->size(); columnIndex++)
        {
            GameBoardSlot::SLOT_KIND slotKind = GameBoardSlot::determineSlotKind(rowIndex, columnIndex);
            GameBoardSlot *gameBoardSlot =
                new GameBoardSlot(rowIndex, columnIndex, slotKind);

            gridColumns->at(columnIndex) = *gameBoardSlot;
        }

        gridRows->at(rowIndex) = *gridColumns;
    }

    this->_grid = gridRows;
}

GameBoard::~GameBoard()
{
    delete this->_grid;
}

bool GameBoard::operator==(const GameBoard &rightHandBoard) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandBoard;
}

bool GameBoard::operator!=(const GameBoard &rightHandBoard) const
{
    // See `GameBoard::operator==` for reasoning.
    return this != &rightHandBoard;
}

int GameBoard::columnPadding() const
{
    return max(this->_columns - 1, 0);
}

int GameBoard::rowPadding() const
{
    return max(this->_rows - 1, 0);
}

int GameBoard::expandedColumns() const
{
    return this->_columns + this->columnPadding();
}

int GameBoard::expandedRows() const
{
    return this->_rows + this->rowPadding();
}

const PlayerTurn *GameBoard::_determineCapturePriorityTurn(int rowIndex, int columnIndex)
{
    const PlayerTurn *priorityTurn = nullptr;
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;

    for (int deltaRowIndex = -1; deltaRowIndex <= 1; deltaRowIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex + deltaRowIndex);
        GameBoardSlot &deltaBoardSlot = gridColumns.at(columnIndex);

        if (deltaBoardSlot.slotKind() != GameBoardSlot::SLOT_KIND::line)
        {
            return nullptr;
        }

        const PlayerTurn &deltaTurn = deltaBoardSlot.playerTurn();

        if (priorityTurn == nullptr || deltaTurn.turnIndex() > priorityTurn->turnIndex())
        {
            priorityTurn = &deltaTurn;
        }
    }

    for (int deltaColumnIndex = -1; deltaColumnIndex <= 1; deltaColumnIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);
        GameBoardSlot &deltaBoardSlot = gridColumns.at(columnIndex + deltaColumnIndex);

        if (deltaBoardSlot.slotKind() != GameBoardSlot::SLOT_KIND::line)
        {
            return nullptr;
        }

        const PlayerTurn &deltaTurn = deltaBoardSlot.playerTurn();

        if (priorityTurn == nullptr || deltaTurn.turnIndex() > priorityTurn->turnIndex())
        {
            priorityTurn = &deltaTurn;
        }
    }

    return priorityTurn;
}

void GameBoard::applyScorableCaptures()
{
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *scorableSlots = this->computeScorableSlots();

    for (int index = 0; index < scorableSlots->size(); index++)
    {
        GameBoardSlot &scorableBoardSlot = scorableSlots->at(index);

        int columnIndex = scorableBoardSlot.columnIndex();
        int rowIndex = scorableBoardSlot.rowIndex();

        const PlayerTurn *priorityTurn = this->_determineCapturePriorityTurn(
            rowIndex, columnIndex);

        if (priorityTurn == nullptr)
        {
            continue;
        }

        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);
        GameBoardSlot &oldGameBoardSlot = gridColumns.at(columnIndex);

        oldGameBoardSlot._applyUpdate(
            GameBoardSlot::SLOT_KIND::initial, *priorityTurn);
    }

    delete scorableSlots;
}

void GameBoard::applyTurn(const PlayerTurn &playerTurn)
{
    int columnIndex = playerTurn.columnIndex();
    int rowIndex = playerTurn.rowIndex();

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

    GameBoardSlot &oldBoardSlot = gridColumns.at(columnIndex);

    if (!oldBoardSlot.isLegalMove())
    {
        throw string("bad argument #0 to 'GameBoard.applyTurn(const PlayerTurn &)' (gameboard grid slot at [") + to_string(rowIndex) + string(", ") + to_string(columnIndex) + string("] is not a legal move)");
    }

    oldBoardSlot._applyUpdate(GameBoardSlot::SLOT_KIND::line, playerTurn);
}

SimpleVector<GameBoardSlot> *GameBoard::computeKindSlots(
    GameBoardSlot::SLOT_KIND slotKind) const
{
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *kindSlots = new SimpleVector<GameBoardSlot>();

    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 0; columnIndex < gridColumns.size(); columnIndex++)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);
            if (gameBoardSlot.slotKind() == slotKind)
            {
                kindSlots->push_back(gameBoardSlot);
            }
        }
    }

    return kindSlots;
}

SimpleVector<GameBoardSlot> *GameBoard::computeLegalSlots() const
{
    // Since player line spacer gameboard slots are always mismatched parities of
    // (x, y) coordinates, we can set up loops to start at (0, 1) and (1, 0)
    // respectively.
    //
    // From there, we can just increment each loop (+2, +2) each to retain that
    // mismatched parities property. This reduces time complexity since it allows
    // us to loop through all potential legal slots without looping all gameboard
    // slots.

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *legalSlots = new SimpleVector<GameBoardSlot>();

    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 1; columnIndex < gridColumns.size(); columnIndex += 2)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            if (gameBoardSlot.isLegalMove())
            {
                legalSlots->push_back(gameBoardSlot);
            }
        }
    }

    for (int rowIndex = 1; rowIndex < gridRows->size(); rowIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 0; columnIndex < gridColumns.size(); columnIndex += 2)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            if (gameBoardSlot.isLegalMove())
            {
                legalSlots->push_back(gameBoardSlot);
            }
        }
    }

    return legalSlots;
}

SimpleVector<GameBoardSlot> *GameBoard::computeScorableSlots(
    GameBoardSlot::SLOT_KIND slotKind) const
{
    // Since scorable box gameboard slots start at (1, 1) and and incremented in
    // +-(2, 2), we can just setup the below loops to breezily skip through the
    // gameboard grid.
    //
    // This also reduces overhead since we don't have to iterate through EVERY
    // gameboard slot. Meaning, not only is there shorter time complexity, but
    // we do not have to check every gameboard slot if they are of
    // `GameBoardSlot::SLOT_KIND::initial` or `GameBoardSlot::SLOT_KIND::scorable` kind.

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *scorableSlots = new SimpleVector<GameBoardSlot>();

    for (int rowIndex = 1; rowIndex < gridRows->size(); rowIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 1; columnIndex < gridColumns.size(); columnIndex += 2)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            if (gameBoardSlot.slotKind() == slotKind)
            {
                scorableSlots->push_back(gameBoardSlot);
            }
        }
    }

    return scorableSlots;
}

const GameBoardSlot &GameBoard::getSlot(int rowIndex, int columnIndex) const
{
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

    return gridColumns.at(columnIndex);
}

void GameBoard::renderGameBoard() const
{
    // We create a prefixing line that contains a legend along the top of columns of
    // the gameboard grid.
    //
    // The first legend is printed for every 10 columns in the gameboard grid.
    //
    // The second legend is printed in sequences of `0...9` for every 10 columns.

    for (int columnIndex = 0; columnIndex <= this->expandedColumns(); columnIndex++)
    {
        int columnLegend = (columnIndex - 1) % 10;
        int columnUberLegend = columnIndex / 10;

        if (columnLegend == 0)
        {
            cout << columnUberLegend;
        }
        else
        {
            cout << ((columnIndex == 0) ? "   " : " ");
        }
    }

    cout << endl;

    for (int columnIndex = 0; columnIndex <= this->expandedColumns(); columnIndex++)
    {
        if (columnIndex == 0)
        {
            cout << "   ";
            continue;
        }

        int columnLegend = (columnIndex - 1) % 10;

        cout << columnLegend;
    }

    cout << endl;

    // Similar to the column legend, the rows have a prefixing legend in the same
    // format.
    //
    // Then rows and columns are sequentially looped to retreive and print each
    // gameboard piece's display character.

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;

    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        int rowLegend = rowIndex % 10;
        int rowUberLegend = rowIndex / 10;

        if (rowLegend == 0)
        {
            cout << rowUberLegend << rowLegend << " ";
        }
        else
        {
            cout << " " << rowLegend << " ";
        }

        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 0; columnIndex < gridColumns.size(); columnIndex++)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            cout << gameBoardSlot.displayCharacter();
        }

        // We only want to newline when we are looping every row before the
        // last one. The calling code should determine if they need a trailing
        // new line on the output.
        if (rowIndex < (gridRows->size() - 1))
        {
            cout << endl;
        }
    }
}