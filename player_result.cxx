#include "player_result.h"

PlayerResult::PlayerResult() {
    this->_playerInitial = '\0';
    this->_score = -1;
    this->_winKind = WIN_KIND::undefined;
}

PlayerResult::PlayerResult(char playerInitial, int score, WIN_KIND winKind)
{
    this->_playerInitial = playerInitial;
    this->_score = score;
    this->_winKind = winKind;
}

PlayerResult::PlayerResult(const PlayerResult &playerResult)
{
    this->_playerInitial = playerResult._playerInitial;
    this->_score = playerResult._score;
    this->_winKind = playerResult._winKind;
}

bool PlayerResult::operator==(const PlayerResult &rightHandResult) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandResult;
}

bool PlayerResult::operator!=(const PlayerResult &rightHandResult) const
{
    // See `GameResult::operator==` for reasoning.
    return this != &rightHandResult;
}