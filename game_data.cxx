#include <iostream>
#include <string>

#include "simple_vector.h"

#include "game_board.h"

#include "player_turn.h"

#include "game_data.h"

GameData *GameData::deserializeGameData(istream &inputStream)
{
    // Function to read game data from input stream and create new GameData object.

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

GameData::GameData(int rows, int columns, SimpleVector<PlayerTurn> *turns)
{
// Constructor for the GameData class
    this->_columns = columns;
    this->_rows = rows;

    this->_turns = turns;
}

GameData::GameData(const GameSession &gameSession, const GameBoard &gameBoard)
{
    this->_columns = gameBoard.columns();
    this->_rows = gameBoard.rows();

    const SimpleVector<const PlayerTurn *> &sessionTurns = gameSession.turns();
    SimpleVector<PlayerTurn> *dataTurns = new SimpleVector<PlayerTurn>(sessionTurns.size());
    for (int index = 0; index < sessionTurns.size(); index++)
    {
        dataTurns->at(index) = PlayerTurn(*sessionTurns.get(index));
    }
    this->_turns = dataTurns;
}

GameData::~GameData()
{
    // Destructor for the GameData class
    delete this->_turns;
}


bool GameData::operator==(const GameData &rightHandData) const
{

    // Compare pointers for nominal instance checking
    // This checks if the two GameData objects are the same instance.
    return this == &rightHandData;
}


bool GameData::operator!=(const GameData &rightHandData) const
{
    // Inequality operator for GameData
    // See `GameData::operator==` for reasoning.
    return this != &rightHandData;
}


GameBoard *GameData::makeGameBoard()
{
    // Function to create a GameBoard object from the stored game data
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