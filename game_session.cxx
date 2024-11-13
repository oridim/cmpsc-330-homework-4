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
    this->_players = new SimpleVector<Player *>();
    this->_turnIndex = -1;
}

GameSession::GameSession(const SimpleVector<Player *> *players, int turnIndex)
{
    this->_players = players;
    this->_turnIndex = turnIndex;
}

GameSession::~GameSession()
{
    // Because we have a vector of pointers, we need to manually handle the
    // cleanup of the allocation.
    for (int index =0; index < this->_players->size(); index++) {
        delete this->_players->get(index);
    }

    delete this->_players;
}

bool GameSession::operator==(const GameSession &rightHandSession) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandSession;
}

bool GameSession::operator!=(const GameSession &rightHandSession) const
{
    // See `GameSession::operator==` for reasoning.
    return this != &rightHandSession;
}

const Player &GameSession::_determineNextPlayer() const
{
    const SimpleVector<Player *> *players = this->_players;
    int playerIndex = this->_turnIndex % players->size();

    return *players->get(playerIndex);
}

PlayerTurn *GameSession::applyNextPlayerTurn(GameBoard &gameBoard)
{
    PlayerTurn *playerTurn = this->computeNextPlayerTurn(gameBoard);

    if (playerTurn == nullptr)
    {
        return nullptr;
    }

    gameBoard.applyTurn(*playerTurn);
    gameBoard.applyScorableCaptures();

    this->_turnIndex += 1;
    return playerTurn;
}

PlayerTurn *GameSession::computeNextPlayerTurn(const GameBoard &gameBoard) const
{
    const Player &player = this->_determineNextPlayer();

    PlayerMove *playerMove = player.computePlayerMove(*this, gameBoard);

    if (playerMove == nullptr)
    {
        return nullptr;
    }

    PlayerTurn *playerTurn = new PlayerTurn(
        *playerMove, this->_turnIndex, player.playerInitial());

    delete playerMove;
    return playerTurn;
}