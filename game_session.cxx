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
    // Determine the next player in the game based on the current turn index
    const SimpleVector<const Player *> *players = this->_players;
    int playerIndex = this->nextTurnIndex() % players->size();

    return *players->get(playerIndex);
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
    gameBoard.applyScorableCaptures();

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