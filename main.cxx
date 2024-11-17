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

#include <fstream>
#include <iostream>

#include "game_configuration.h"
#include "game_board.h"
#include "game_session.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream inputStream;
    char *fileName = argv[1];

    inputStream.open(fileName);
    if (inputStream.is_open())
    {
        // If the file provided by the end-user was not reachable, then we error
        // error out with a non-zero exit code.
        cerr
            << "error: file '" << fileName << "' was not available for reading"
            << endl;

        return 1;
    }

    GameConfiguration *gameConfiguration =
        GameConfiguration::deserializeGameConfiguration(inputStream);

    GameBoard *gameBoard = gameConfiguration->makeGameBoard();
    GameSession *gameSession = gameConfiguration->makeGameSession();

    delete gameSession;
    delete gameBoard;
    delete gameConfiguration;

    return 0;
}