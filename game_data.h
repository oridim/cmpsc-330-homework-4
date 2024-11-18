#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include <iostream>

#include "simple_vector.h"
#include "player_turn.h"
#include "game_board.h"
#include "game_session.h"

using namespace std;

// `class GameData`
//
// Represents structured data containing data from a recorded game of
// Dots and Boxes that was parsed from structured end-user input.
class GameData
{
private:
    // `int GameData._columns`
    //
    // Represents how many columns of dots there were in the Dots and Boxes
    // gameboard grid.
    int _columns;

    // `int GameData._rows`
    //
    // Represents how many rows of dots there were in the Dots and Boxes
    // gameboard grid.
    int _rows;

    // `SimpleVector<PlayerTurn *> *GameData._turns`
    //
    // Represents a vector of turn actions that was performed during the
    // Dots and Boxes game by the recorded players.
    SimpleVector<PlayerTurn> *_turns;

public:
    // `GameData *GameData::deserializeGameData(istream &inputStream)`
    //
    // Returns the pointer to a new `GameData` instance that was configured
    // from the supplied `inputStream`.
    static GameData *deserializeGameData(istream &inputStream);

public:
    GameData(int rows, int columns, SimpleVector<PlayerTurn> *turns);
    GameData(const GameSession &gameSession, const GameBoard &gameBoard);

    ~GameData();

    bool operator==(const GameData &rightHandData) const;
    bool operator!=(const GameData &rightHandData) const;

    int columns() { return this->_columns; };
    int rows() { return this->_rows; };
    const SimpleVector<PlayerTurn> &turns() const { return *this->_turns; };

    // `GameBoard *GameData.makeGameBoard()`
    //
    // Returns a new `GameBoard` instance that had `GameData`'s loaded settings
    // and turns applied to it.
    GameBoard *makeGameBoard();

    // `void GameResult.serializeGameBoard(ostream &outputStream)`
    //
    // Serializes the game data to the supplied `outputStream`.
    void serializeGameData(ostream &outputStream) const;
};

#endif