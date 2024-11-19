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

#include "player_result.h"

PlayerResult::PlayerResult()
{
    // Default constructor for PlayerResult, initializes the player's result with default values
    this->_playerInitial = '\0';
    this->_score = -1;
    this->_winKind = WIN_KIND::undefined;
}

PlayerResult::PlayerResult(char playerInitial, int score, WIN_KIND winKind)
{
    // Parameterized constructor for PlayerResult, initializes the player's result with specific values
    this->_playerInitial = playerInitial;
    this->_score = score;
    this->_winKind = winKind;
}

PlayerResult::PlayerResult(const PlayerResult &playerResult)
{
    // Copy constructor for PlayerResult, creates a copy of an exixting PlayerResult object
    this->_playerInitial = playerResult._playerInitial;
    this->_score = playerResult._score;
    this->_winKind = playerResult._winKind;
}

bool PlayerResult::operator==(const PlayerResult &rightHandResult) const
{
    // Compare the current object with the other object by checking if they are the same instance (pointer comparison)
    return this == &rightHandResult;
}

bool PlayerResult::operator!=(const PlayerResult &rightHandResult) const
{
    // Compare the current object with the other object by using the negation of the equality operator
    return this != &rightHandResult;
}