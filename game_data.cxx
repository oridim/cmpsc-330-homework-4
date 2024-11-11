#include <iostream>
#include <string>

#include "simple_vector.h"
#include "player_turn.h"
#include "game_board.h"

#include "game_data.h"

GameData *GameData::readGameData(istream &inputStream)
{
    int columns;
    int rows;
    SimpleVector<PlayerTurn> *turns = new SimpleVector<PlayerTurn>();

    inputStream >> columns >> rows;

    int columnIndex;
    int rowIndex;

    string playerInitial;
    int turnIndex = 0;

    while (inputStream >> playerInitial)
    {
        if (playerInitial == "END")
        {
            break;
        }

        inputStream >> rowIndex >> columnIndex;

        PlayerTurn *playerTurn = new PlayerTurn(turnIndex, rowIndex, columnIndex, toupper(playerInitial.at(0)));

        turns->push_back(*playerTurn);
        turnIndex += 1;
    }

    return new GameData(columns, rows, turns);
}

GameData::GameData(int rows, int columns, SimpleVector<PlayerTurn> *turns)
{
    this->_columns = columns;
    this->_rows = rows;
    this->_turns = turns;
}

GameData::~GameData()
{
    delete this->_turns;
}

bool GameData::operator==(const GameData &rightHandData) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandData;
}

bool GameData::operator!=(const GameData &rightHandData) const
{
    // See `GameData::operator==` for reasoning.
    return this != &rightHandData;
}

GameBoard *GameData::makeGameBoard()
{
    GameBoard *gameBoard = new GameBoard(this->_rows, this->_columns);

    for (int index = 0; index < this->_turns->size(); index++)
    {
        const PlayerTurn &turn = this->_turns->at(index);

        gameBoard->applyTurn(turn);
    }

    return gameBoard;
}