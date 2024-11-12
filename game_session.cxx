#include "simple_vector.h"

#include "player.h"

#include "game_session.h"

GameSession::GameSession()
{
    this->_players = new SimpleVector<Player>();
    this->_turnIndex = -1;
}

GameSession::GameSession(const SimpleVector<Player> *players)
{
    this->_players = players;
    this->_turnIndex = 0;
}

GameSession::GameSession(const GameSession &gameSession)
{
    this->_players = new SimpleVector<Player>(*gameSession._players);
    this->_turnIndex = gameSession._turnIndex;
}

GameSession::~GameSession()
{
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
    const SimpleVector<Player> *players = this->_players;
    int playerIndex = this->_turnIndex % players->size();

    return players->get(playerIndex);
}