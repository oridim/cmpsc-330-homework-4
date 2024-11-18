#include <iostream>
#include <string>

#include "simple_vector.h"

#include "game_board.h"

#include "player_turn.h"

#include "game_data.h"

// Function to read game data from input stream and create new GameData object.
GameData *GameData::deserializeGameData(istream &inputStream)
{
    // Variables to store the number of columns and rows in the game board.
    // Creation of a new SimpleVector to store the sequence of player turns. 
    int columns;
    int rows;
    SimpleVector<PlayerTurn> *turns = new SimpleVector<PlayerTurn>();

    inputStream >> rows >> columns;

    int columnIndex;
    int rowIndex;

    // Variable to store the player's initial (character) and turn counter.
    string playerInitial;
    int turnIndex = 0;

    // Loop to read player turns from the input stram until "END" is encountered. 
    while (inputStream >> playerInitial)
    {
        if (playerInitial == "END")
        {
            break;
        }

        // Read the row and column indices for the current turn.
        inputStream >> rowIndex >> columnIndex;

        // Create new PlayerTurn object for the current turn
        PlayerTurn *playerTurn = new PlayerTurn(turnIndex, rowIndex, columnIndex, toupper(playerInitial.at(0)));

        // Add PlayerTurn object to the vector of turns
        // Increment the turn index
        turns->push_back(*playerTurn);
        turnIndex += 1;
    }

    return new GameData(rows, columns, turns);
}

// Constructor for the GameData class
GameData::GameData(int rows, int columns, SimpleVector<PlayerTurn> *turns)
{
    this->_columns = columns;
    this->_rows = rows;
    this->_turns = turns;
}

// Destructor for the GameData class
GameData::~GameData()
{
    delete this->_turns;
}

// Equality operator for GameData objects
bool GameData::operator==(const GameData &rightHandData) const
{

    // Compare pointers for nominal instance checking
    // This checks if the two GameData objects are the same instance.
    return this == &rightHandData;
}

// Inequality operator for GameData
bool GameData::operator!=(const GameData &rightHandData) const
{
    // See `GameData::operator==` for reasoning.
    return this != &rightHandData;
}

// Function to create a GameBoard object from the stored game data
GameBoard *GameData::makeGameBoard()
{
    GameBoard *gameBoard = new GameBoard(this->_rows, this->_columns);

    // Apply each player turn from the stored turns verctor to the Gameboard.
    for (int index = 0; index < this->_turns->size(); index++)
    {
        const PlayerTurn &turn = this->_turns->at(index);

        gameBoard->applyTurn(turn);
    }

    return gameBoard;
}

void GameData::serializeGameData(ostream &outputStream) const
{
    outputStream
        << this->_rows << " " << this->_columns << endl;

    SimpleVector<PlayerTurn> *turns = this->_turns;

    for (int index = 0; index < turns->size(); index++)
    {
        PlayerTurn &playerTurn = turns->at(index);

        cout << playerTurn.playerInitial() << " "
             << playerTurn.rowIndex() << " " << playerTurn.columnIndex();

        // We only want to newline when we are looping every turn before the
        // last one. The calling code should determine if they need a trailing
        // new line on the output.
        if (index < (turns->size() - 1))
        {
            outputStream << endl;
        }
    }
}