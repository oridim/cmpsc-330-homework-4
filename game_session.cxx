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
    this->_players = new SimpleVector<const Player *>();
    this->_turns = new SimpleVector<const PlayerTurn *>();
}

GameSession::GameSession(const SimpleVector<const Player *> *players)
{
    this->_players = players;
    this->_turns = new SimpleVector<const PlayerTurn *>();
}

GameSession::GameSession(const SimpleVector<const Player *> *players, const SimpleVector<PlayerTurn> turns)
{
    this->_players = players;
    this->_turns = new SimpleVector<const PlayerTurn *>(turns.size());

    // `GameSession` takes ownership of its own vector of player turns. So,
    // we need to clone the source vector provided.
    for (int index = 0; index < turns.size(); index++)
    {
        const PlayerTurn &oldPlayerTurn = turns.get(index);
        PlayerTurn *newPlayerTurn = new PlayerTurn(oldPlayerTurn);

        this->_turns->at(index) = newPlayerTurn;
    }
}

GameSession::~GameSession()
{
    // Because we have vectors of pointers, we need to manually handle the
    // cleanup of the allocation.
    for (int index = 0; index < this->_players->size(); index++)
    {
        delete this->_players->get(index);
    }

    for (int index = 0; index < this->_turns->size(); index++)
    {
        delete this->_turns->at(index);
    }

    delete this->_players;
    delete this->_turns;
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
    const SimpleVector<const Player *> *players = this->_players;
    int playerIndex = this->nextTurnIndex() % players->size();

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

    this->_turns->push_back(playerTurn);

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
        *playerMove, this->nextTurnIndex(), player.playerInitial());

    delete playerMove;
    return playerTurn;
}

int GameSession::nextTurnIndex() const
{
    return this->_turns->size();
}