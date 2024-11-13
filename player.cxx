#include <string>

#include "player_turn.h"
#include "game_board.h"
#include "game_session.h"

#include "player.h"

Player::Player()
{
    this->_playerInitial = '\0';
}

Player::Player(char playerInitial)
{
    this->_playerInitial = playerInitial;
}

Player::Player(const Player &Player)
{
    this->_playerInitial = Player._playerInitial;
}

bool Player::operator==(const Player &rightHandPlayer) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandPlayer;
}

bool Player::operator!=(const Player &rightHandPlayer) const
{
    // See `Player::operator==` for reasoning.
    return this != &rightHandPlayer;
}

PlayerTurn *Player::computePlayerTurn(const GameSession &gameSession, const GameBoard &gameBoard) const
{
    throw string("bad dispatch to 'Player.computePlayerTurn(const GameBoard &)' (not implemented)");
}