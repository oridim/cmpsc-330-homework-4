#include "player_result.h"

// Default constructor for PlayerResult, initializes the player's result with default values
PlayerResult::PlayerResult() {
    this->_playerInitial = '\0';
    this->_score = -1;
    this->_winKind = WIN_KIND::undefined;
}

// Parameterized constructor for PlayerResult, initializes the player's result with specific values
PlayerResult::PlayerResult(char playerInitial, int score, WIN_KIND winKind)
{
    this->_playerInitial = playerInitial;
    this->_score = score;
    this->_winKind = winKind;
}

// Copy constructor for PlayerResult, creates a copy of an exixting PlayerResult object
PlayerResult::PlayerResult(const PlayerResult &playerResult)
{
    this->_playerInitial = playerResult._playerInitial;
    this->_score = playerResult._score;
    this->_winKind = playerResult._winKind;
}

// Equality operator (==) for comparing two PlayerResult objects
bool PlayerResult::operator==(const PlayerResult &rightHandResult) const
{
    // Compare the current object with the other object by checking if they are the same instance (pointer comparison)
    return this == &rightHandResult;
}

// Inequality operator (!=) for comparing two PlayerResult objects
bool PlayerResult::operator!=(const PlayerResult &rightHandResult) const
{
     // Compare the current object with the other object by using the negation of the equality operator
    return this != &rightHandResult;
}