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
//     * This file provides the type definitions of an AI Dots and Boxes
//       player who lines to place on the gameboard grid at random.
//
//---------------------------------------------------------------------

#ifndef _RANDOM_AI_PLAYER_H_
#define _RANDOM_AI_PLAYER_H_

#include "player.h"
#include "player_move.h"

// `class RandomAIPlayer`
//
// Represents a player controller that strictly picks a random move to make
// from the available list of moves to make.
class RandomAIPlayer : public Player
{
public:
    using Player::Player;

    RandomAIPlayer(char playerInitial);

    // `PlayerMove RandomAIPlayer.computePlayerMove(const GameSession &gameSession, const GameBoard &gameBoard)`
    //
    // Returns a pointer to a new `PlayerMove` instance if the `RandomAIPlayer`
    // instance was able to compute a move to make.
    //
    // Otherwise, `nullptr` is returned.
    //
    // It computes the move by selecting a randomly available gameboard grid
    // slot that is open and is a legal move.
    virtual PlayerMove *computePlayerMove(
        const GameSession &gameSession, const GameBoard &gameBoard) const override;
};

#endif