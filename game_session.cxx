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

#include "simple_vector.h"

#include "game_board.h"

#include "player.h"
#include "basic_strategy_ai_player.h"
#include "random_ai_player.h"
#include "player_move.h"
#include "player_turn.h"

#include "game_session.h"

GameSession::GameSession()
{
    // Default constructor for GameSession
    this->_players = new SimpleVector<const Player *>();
    this->_turns = new SimpleVector<const PlayerTurn *>();
}

GameSession::GameSession(SimpleVector<const Player *> *players)
{
    // Constructor with player vector, initializes the game session with a list of players
    this->_players = players;
    this->_turns = new SimpleVector<const PlayerTurn *>();
}

GameSession::GameSession(SimpleVector<const Player *> *players, const SimpleVector<PlayerTurn> turns)
{
    // Constructor with player vector and player turns, copies the turns into the session
    this->_players = players;
    this->_turns = new SimpleVector<const PlayerTurn *>(turns.size());

    // Clone the player turns from the provided vector to the session
    for (int index = 0; index < turns.size(); index++)
    {
        const PlayerTurn &oldPlayerTurn = turns.get(index);
        PlayerTurn *newPlayerTurn = new PlayerTurn(oldPlayerTurn);

        this->_turns->at(index) = newPlayerTurn;
    }
}

GameSession::~GameSession()
{
    // Destructor for GameSession, cleans up dynamically allocated memory.
    // Clean up the memory allocated for player pointers
    for (int index = 0; index < this->_players->size(); index++)
    {
        delete this->_players->get(index);
    }

    // Clean up the memory allocated for player turn pointers
    for (int index = 0; index < this->_turns->size(); index++)
    {
        delete this->_turns->at(index);
    }

    // Delete the vectors
    delete this->_players;
    delete this->_turns;
}

bool GameSession::operator==(const GameSession &rightHandSession) const
{
    // Compare the current instance with the right-hand side using pointer comparison
    // This checks for nominal equality

    return this == &rightHandSession;
}

bool GameSession::operator!=(const GameSession &rightHandSession) const
{
    // Inequality operator for comparing two GameSession objects.
    return this != &rightHandSession;
}

const Player &GameSession::_determineNextPlayer() const
{
    // Determine the next player in the game based on the first entry of the vector
    return *this->_players->at(0);
}

void GameSession::_shiftTurnOrder()
{
    SimpleVector<const Player *> *players = this->_players;
    const Player *frontPlayer = players->at(0);

    for (int index = 0; index < (players->size() - 1); index++)
    {
        players->at(index) = players->at(index + 1);
    }

    players->at(players->size() - 1) = frontPlayer;
}

PlayerTurn *GameSession::applyNextPlayerTurn(GameBoard &gameBoard)
{
    // Applies the next player turn to the game board
    PlayerTurn *playerTurn = this->computeNextPlayerTurn(gameBoard);

    if (playerTurn == nullptr)
    {
        return nullptr;
    }

    // Apply the player's turn to the game board
    gameBoard.applyTurn(*playerTurn);
    // Apply any scorable captures that may have occured as a result of the turn
    int capturesMade = gameBoard.applyScorableCaptures();

    // If captures were not made by player we need to shift them to the back
    // of the turn order.
    if (capturesMade == 0)
    {
        _shiftTurnOrder();
    }

    this->_turns->push_back(playerTurn);

    return playerTurn;
}

PlayerTurn *GameSession::computeNextPlayerTurn(const GameBoard &gameBoard) const
{
    // Computes the next player turn based on the current state of the game board
    // Get the next player in the game
    const Player &player = this->_determineNextPlayer();
    PlayerMove *playerMove = player.computePlayerMove(*this, gameBoard);

    // If there is no valid move, returm nullptr
    if (playerMove == nullptr)
    {
        return nullptr;
    }

    // Create a new player turn based on the computed move
    PlayerTurn *playerTurn = new PlayerTurn(
        *playerMove, this->nextTurnIndex(), player.playerInitial());

    delete playerMove;
    return playerTurn;
}

int GameSession::nextTurnIndex() const
{
    return this->_turns->size();
}