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
//     * This program receives end-user configuration input for players
//       to play a Dots and Boxes game. It then deserializes and processes
//       that input to setup a game session. The defined players then play
//       an entire game with the end results outputted to the terminal.
//
//---------------------------------------------------------------------

#include <iostream>
#include <random>

#include "game_configuration.h"
#include "game_board.h"
#include "game_data.h"
#include "game_session.h"
#include "game_result.h"
#include "player_turn.h"

using namespace std;

int main()
{
    // We are seeding the number generator with the current clock time.
    srand(time(nullptr));

    GameConfiguration *gameConfiguration =
        GameConfiguration::deserializeGameConfiguration(cin);

    GameBoard *gameBoard = gameConfiguration->makeGameBoard();
    GameSession *gameSession = gameConfiguration->makeGameSession();

    while (gameBoard->remainingCaptures() > 0)
    {
        PlayerTurn *playerTurn = gameSession->applyNextPlayerTurn(*gameBoard);
        if (playerTurn == nullptr)
        {
            // **HACK**: This should never be a possible return given we are checking
            // for the remaining captures.
            //
            // But just in case...
            break;
        }

        gameBoard->serializeGameBoard(cout);
        cout << endl
             << endl;
    }

    GameResult *gameResult =
        GameResult::computeGameResult(*gameSession, *gameBoard);

    GameData gameData = GameData(*gameSession, *gameBoard);

    gameData.serializeGameData(cout);
    cout << endl
         << "END" << endl // **QUESTION:** Do we need this here?
         << endl;

    gameBoard->serializeGameBoard(cout);
    cout << endl
         << endl;

    gameResult->serializeGameResult(cout);
    cout << endl;

    delete gameResult;
    delete gameSession;
    delete gameBoard;
    delete gameConfiguration;

    return 0;
}