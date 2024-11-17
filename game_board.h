#ifndef _GAME_BOARD_H_
#define _GAME_BOARD_H_

#include <iostream>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.h"

#include "player_turn.h"

// **NOTE**: `GameBoard._grid` could be made more memory efficient by implementing
// a custom `SimpleFixedVector<V>` where the size is fixed and operations more limited.
//
// As it stands now, `SimpleVector<SimpleVector<GameBoardSlot>>` is slightly wasteful
// do its dynamic growth nature.
//
// There is a plus side how ever! I do not need to have like a `GameBoard._gridSize`
// to track the size...

// `class GameBoard`
//
// Represents structured data containing the state about a Dots and Boxes
// gameboard grid.
class GameBoard
{
private:
    // `int GameBoard._capturesMade`
    //
    // Represents the amount of captures made on the Dots and Boxes gameboard
    // grid.
    int _capturesMade;

    // `int GameBoard._columns`
    //
    // Represents how many columns of dots there are in the Dots and Boxes
    // gameboard grid.
    int _columns;

    // `int GameBoard._rows`
    //
    // Represents how many rows of dots there are in the Dots and Boxes
    // gameboard grid.
    int _rows;

    // `SimpleVector<SimpleVector<GameBoardSlot *> *> GameBoard.*_grid`
    //
    // Represents a two-dimensional `SimpleVector` of gameboard grid slots.
    //
    // The `GameBoard` instance is only initialized with the amount of dots
    // in the gameboard grid with no space for player lines or scorable boxes.
    //
    // So, we need to expand the supplied grid size to provide space. That is
    // done by taking the M rows x N columns and then increasing them by
    // computing expanded M rows = `M + (M - 1)` and N columns = `N + (N - 1)`.
    //
    // ex. Thus 3x6 grid:
    //
    // ```
    // ......
    // ......
    // ......
    // ```
    //
    // Is expanded into this `(3 + (3 - 1))x(6 + (6 - 1))` = 5 x 11 grid:
    //
    // ```
    // . . . . . .
    //
    // . . . . . .
    //
    // . . . . . .
    // ```
    SimpleVector<SimpleVector<GameBoardSlot>> *_grid;

    const PlayerTurn *_determineCapturePriorityTurn(int rowIndex, int columnIndex);

public:
    GameBoard(int rows, int columns);

    ~GameBoard();

    bool operator==(const GameBoard &rightHandBoard) const;
    bool operator!=(const GameBoard &rightHandBoard) const;

    int capturesMade() const { return this->_capturesMade; }
    int columns() const { return this->_columns; }
    int rows() const { return this->_rows; }

    // `int GameBoard.columnPadding()`
    //
    // Returns how much column padding is needs to be applied to the MxN
    // gameboard grid to provide space for line spacers and scorable boxes.
    int columnPadding() const;

    // `int GameBoard.rowPadding()`
    //
    // Returns how much row padding is needs to be applied to the MxN
    // gameboard grid to provide space for line spacers and scorable boxes.
    int rowPadding() const;

    // `int GameBoard.expandedColumns()`
    //
    // Returns the column size of the gameboard grid expanded with the column
    // padding to provide space for line spacers and scorable boxes.
    int expandedColumns() const;

    // `int GameBoard.expandedRows()`
    //
    // Returns the row size of the gameboard grid expanded with the row
    // padding to provide space for line spacers and scorable boxes.
    int expandedRows() const;

    // `int GameBoard.remainingCaptures()`
    //
    // Returns the amount of available scorable gameboard grid still remaining
    // players can still capture.
    int remainingCaptures() const;

    // `int GameBoard.totalCaptures()`
    //
    // Returns the total amount of captures (including captured gameboard grid slots)
    // that the gameboard provides.
    int totalCaptures() const;

    // `int GameBoard.applyScorableCaptures()`
    //
    // Computes available `GameBoardSlot`'s instances in the gameboard grid
    // that have their `GameBoardSlot.kind` set to `GameBoardSlot::SLOT_KIND::scorable`.
    //
    // Then, each found `GameBoardSlot` is lopped has their horizontal and
    // vertical adjacent `GameBoardSlot` instances checked for being
    // `GameBoardSlot::SLOT_KIND::line`.
    //
    // If all four adjacent `GameBoardSlot` instances are scored lines, then
    // the slot with their `GameBoardSlot.turnIndex` being the highest has
    // their `GameBoardSlot.playerInitial` applied to the scorable box slot.
    //
    // Finally, the scorable box slot has its `GameBoardSlot.kind` updated
    // to `GameBoardSlot::SLOT_KIND::initial`.
    //
    // The amount of captures made is returned.
    int applyScorableCaptures();

    // `void GameBoard.applyTurn(const PlayerTurn &turn)`
    //
    // Applies the given `turn` to the gameboard grid if the `turn`'s
    // `PlayerTurn.columnIndex` and `PlayerTurn.rowIndex` are legal.
    //
    // Otherwise, an exception is thrown if not legal.
    void applyTurn(const PlayerTurn &playerTurn);

    // `SimpleVector<GameBoardSlot> *GameBoard.computeKindSlots(GameBoardSlot::SLOT_KIND kind)`
    //
    // Returns a new `SimpleVector` with all the available `GameBoardSlot`
    // instances in the gameboard grid that have their `GameBoardSlot._kind`
    // set to the supplied `kind`.
    SimpleVector<GameBoardSlot> *computeKindSlots(
        GameBoardSlot::SLOT_KIND slotKind) const;

    // `SimpleVector<GameBoardSlot> *GameBoard.computeLegalSlots()`
    //
    // Returns a new `SimpleVector` with all the available `GameBoardSlot`
    // instances in the gameboard grid that are legal moves with an optimized
    // algorithm.
    SimpleVector<GameBoardSlot> *computeLegalSlots() const;

    // `SimpleVector<GameBoardSlot> *GameBoard.computeScorableSlots()`
    //
    // Returns a new `SimpleVector` with all the available `GameBoardSlot`
    // instances in the gameboard grid that have their `GameBoardSlot._kind`
    // `GameBoardSlot::SLOT_KIND::initial` or `GameBoardSlot::SLOT_KIND::scorable`
    // with an optimized algorithm.
    SimpleVector<GameBoardSlot> *computeScorableSlots(
        GameBoardSlot::SLOT_KIND slotKind = GameBoardSlot::SLOT_KIND::scorable) const;

    // `GameBoardSlot *GameBoard.getSlot(int rowIndex, int columnIndex)`
    //
    // Returns the `GameBoardSlot` instance assigned to the queried row
    // and column in the gameboard grid.
    //
    // If the slot of out of bounds of the gameboard grid, an exception is
    // then thrown.
    const GameBoardSlot &getSlot(int rowIndex, int columnIndex) const;

    // `void GameBoard.serializeGameBoard(const ostream &outputStream)`
    //
    // Serializes the gameboard's state to the supplied `outputStream`.
    void serializeGameBoard(ostream &outputStream) const;
};

#endif