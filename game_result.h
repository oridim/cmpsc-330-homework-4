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
//     * TODO
//
// Acknowledgments:
//
//     * TODO
//
//---------------------------------------------------------------------

#ifndef _GAME_RESULT_H_
#define _GAME_RESULT_H_

#include <iostream>

#include "simple_vector.h"

#include "player_result.h"
#include "game_board.h"
#include "game_session.h"

// `class GameResult`
//
// Represents structured data containing the player results data of a
// Dots and Boxes game session.
class GameResult
{
public:
    // `enum int GameResult::WIN_KIND`
    //
    // Represents an enumeration of all possible win states a Dots and Boxes
    // game can finish as.
    enum class WIN_KIND
    {
        // `GameResult::WIN_KIND::undefined`
        //
        // Represents that the game has an undefined win state.
        undefined,

        // `GameResult::WIN_KIND::nocontest`
        //
        // Represents that the game had no scoring winners.
        nocontest,

        // `GameResult::WIN_KIND::singular`
        //
        // Represents that the game has a singular winner.
        singular,

        // `GameResult::WIN_KIND::multiple`
        //
        // Represents that the game is has multiple winners.
        multiple
    };

    static GameResult *computeGameResult(
        const GameSession &gameSession, const GameBoard &gameBoard);

private:
    // `char GameResult._highestScore`
    //
    // Represents the initial used by the player as their identifier.
    int _highestScore;

    // `GameResult::WIN_KIND GameResult._winKind`
    //
    // Represents the winning state of the player.
    //
    // **SEE**: `WIND_KIND` for more details.
    WIN_KIND _winKind;

    // `SimpleVector<PlayerResult> *GameResult._playerResults`
    //
    // Represents results for each individual player.
    SimpleVector<PlayerResult> *_playerResults;

public:
    GameResult(
        SimpleVector<PlayerResult> *playerResults, WIN_KIND winKind, int highestScore);

    GameResult(const GameResult &gameResult);

    ~GameResult();

    bool operator==(const GameResult &rightHandResult) const;
    bool operator!=(const GameResult &rightHandResult) const;

    int highestScore() const { return this->_highestScore; }
    const SimpleVector<PlayerResult> &playerResults() const { return *this->_playerResults; }
    WIN_KIND winKind() const { return this->_winKind; }

    // `void GameResult.serializeGameBoard(ostream &outputStream)`
    //
    // Serializes the game result to the supplied `outputStream`.
    void serializeGameResult(ostream &outputStream) const;
};

#endif