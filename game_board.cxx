
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
    // Initialize the rows and columns of the game board. 
    // These values must be set before computing derived properties
    this->_columns = columns;
    this->_rows = rows;

    int expandedRows = this->expandedRows();
    int expandedColumns = this->expandedColumns();

    // Create a grid (2D vector) of GameBoard slot objects with the dimensions.
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows =
        new SimpleVector<SimpleVector<GameBoardSlot>>(expandedRows);

    // Initialize wach row of the grid.
    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        SimpleVector<GameBoardSlot> *gridColumns =
            new SimpleVector<GameBoardSlot>(expandedColumns);

        // Initialize each column of the grid and determine the type of slot.
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
    // Deallocate the memory for the grid to avoid memory leaks
    delete this->_grid;
}

bool GameBoard::operator==(const GameBoard &rightHandBoard) const
{
    // Check for equality of two GameBoard instances. The comparison is nominal,
    // meaning it only checks if the two objects are the same instance in the memory.
    return this == &rightHandBoard;
}

bool GameBoard::operator!=(const GameBoard &rightHandBoard) const
{
    // See `GameBoard::operator==` for reasoning.
    return this != &rightHandBoard;
}

int GameBoard::columnPadding() const
{
    // Compute the padding between columns for expanded dimensions.
    return max(this->_columns - 1, 0);
}

int GameBoard::rowPadding() const
{
    // Compute the padding between rows for expanded dimensions.
    return max(this->_rows - 1, 0);
}

int GameBoard::expandedColumns() const
{
    // Calculate the total number of columns including padding.
    return this->_columns + this->columnPadding();
}

int GameBoard::expandedRows() const
{
    // Calculate the total number of rows including padding.
    return this->_rows + this->rowPadding();
}

int GameBoard::remainingCaptures() const
{
    return this->totalCaptures() - this->_capturesMade;
}

int GameBoard::totalCaptures() const
{
    int expandedColumns = this->columnPadding();
    int expandedRows = this->rowPadding();

    return expandedColumns * expandedRows;
}

const PlayerTurn *GameBoard::_determineCapturePriorityTurn(int rowIndex, int columnIndex)
{
    // Determine the PlayerTurn with the highest priority for a potential capture.
    const PlayerTurn *priorityTurn = nullptr;
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;

    // Check the rows above and below the current position for valid line slots. 
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

    // Check the columns left and right of the current position for the valid line slots. 
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

int GameBoard::applyScorableCaptures()
{
    // This method iterates through all scorable slots on the game board and applies captures
    // if a specific player has priority based on game rules. 

    int capturesMade = 0;

    // Retrieve the grid and compute all scorable slots.
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *scorableSlots = this->computeScorableSlots();

    // Loop through each scorable slot.
    for (int index = 0; index < scorableSlots->size(); index++)
    {
        GameBoardSlot &scorableBoardSlot = scorableSlots->at(index);

        int columnIndex = scorableBoardSlot.columnIndex();
        int rowIndex = scorableBoardSlot.rowIndex();

        // Determine the priority player turn for capturing this slot
        const PlayerTurn *priorityTurn = this->_determineCapturePriorityTurn(
            rowIndex, columnIndex);

        // If no priority player turn exists, then skip to the next slot.
        if (priorityTurn == nullptr)
        {
            continue;
        }

        // Access the slot in the grid and apply the update to mark it captured.
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);
        GameBoardSlot &oldGameBoardSlot = gridColumns.at(columnIndex);

        oldGameBoardSlot._applyUpdate(
            GameBoardSlot::SLOT_KIND::initial, *priorityTurn);

        capturesMade += 1;
    }

    this->_capturesMade += capturesMade;

    delete scorableSlots;
    return capturesMade;
}

void GameBoard::applyTurn(const PlayerTurn &playerTurn)
{
    // This method applies a player's move to the gameboard.

    // Retrieve the indices of the player's moves.
    int columnIndex = playerTurn.columnIndex();
    int rowIndex = playerTurn.rowIndex();

    // Access the grid and retrieve the corresponding slot for the move.
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

    // Check if slot it a legal move, if not throw an exception
    GameBoardSlot &oldBoardSlot = gridColumns.at(columnIndex);

    if (!oldBoardSlot.isLegalMove())
    {
        throw string("bad argument #0 to 'GameBoard.applyTurn(const PlayerTurn &)' (gameboard grid slot at [") + to_string(rowIndex) + string(", ") + to_string(columnIndex) + string("] is not a legal move)");
    }

    // Apply the move, marking the slot as a line belonging to the player.
    oldBoardSlot._applyUpdate(GameBoardSlot::SLOT_KIND::line, playerTurn);
}

SimpleVector<GameBoardSlot> *GameBoard::computeKindSlots(
    GameBoardSlot::SLOT_KIND slotKind) const
{
    // This method retrieves all slots of a specific kind from the game board.

    // Allocate memory for storing the matching slots. 
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *kindSlots = new SimpleVector<GameBoardSlot>();

    // Iterate through the entire gird to find slots mathcing the specified kind.
    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 0; columnIndex < gridColumns.size(); columnIndex++)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);
            if (gameBoardSlot.slotKind() == slotKind)
            {
                // Add the matching slot to the list.
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

    // Check slots in rows with even indices, starting at column 1, incrementing by 2.
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

    // Check slots in rows with odd indices, starting at column 0, incrementing by 2.
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

    // Allocate memory to store scorable slots.
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> *scorableSlots = new SimpleVector<GameBoardSlot>();

    // Scorable slots are located at odd-indexed rows and columns (1,1), (3,3)...
    // Incrementing by two reduces unnecessary checks.
    for (int rowIndex = 1; rowIndex < gridRows->size(); rowIndex += 2)
    {
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 1; columnIndex < gridColumns.size(); columnIndex += 2)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            // Check if the current slot matches the desired slot kind.
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
    // This method retrieves a slot from the game board grid based on row and column indices.

    // Access the grid rows and retrieve the specific column in the given row.
    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;
    SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

    return gridColumns.at(columnIndex);
}

void GameBoard::serializeGameBoard(ostream &outputStream) const
{
    //This method serialize the entire game board, including row and column legends
    //
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
            outputStream << columnUberLegend;
        }
        else
        {
            outputStream << ((columnIndex == 0) ? "   " : " ");
        }
    }

    outputStream << endl;

    // Print secondary column legend in a sequence of 0 to 9.
    for (int columnIndex = 0; columnIndex <= this->expandedColumns(); columnIndex++)
    {
        if (columnIndex == 0)
        {
            // Leave a blank space for row alignment.
            outputStream << "   ";
            continue;
        }

        int columnLegend = (columnIndex - 1) % 10;

        outputStream << columnLegend;
    }

    outputStream << endl;

    // Similar to the column legend, the rows have a prefixing legend in the same
    // format.
    //
    // Then rows and columns are sequentially looped to retreive and print each
    // gameboard piece's display character.

    SimpleVector<SimpleVector<GameBoardSlot>> *gridRows = this->_grid;

    for (int rowIndex = 0; rowIndex < gridRows->size(); rowIndex++)
    {
        // Print row legends, similar to column legends, but for rows.
        int rowLegend = rowIndex % 10;
        int rowUberLegend = rowIndex / 10;

        if (rowLegend == 0)
        {
            outputStream << rowUberLegend << rowLegend << " ";
        }
        else
        {
            outputStream << " " << rowLegend << " ";
        }

        // Serialize the contents of the current row.
        SimpleVector<GameBoardSlot> &gridColumns = gridRows->at(rowIndex);

        for (int columnIndex = 0; columnIndex < gridColumns.size(); columnIndex++)
        {
            GameBoardSlot &gameBoardSlot = gridColumns.at(columnIndex);

            // Print the display character of each slot
            outputStream << gameBoardSlot.displayCharacter();
        }

        // We only want to newline when we are looping every row before the
        // last one. The calling code should determine if they need a trailing
        // new line on the output.
        if (rowIndex < (gridRows->size() - 1))
        {
            outputStream << endl;
        }
    }
}