#include <iostream>
#include <string>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.h"
#include "game_board.h"
#include "game_session.h"

#include "player_result.h"
#include "player_turn.h"

#include "game_result.h"

GameResult *GameResult::computeGameResult(
    const GameSession &gameSession, const GameBoard &gameBoard)
{
    // Static method to compute the game result based on the current game session and board state.
    int highestScore = 0;

    // **NOTE**: We only need to test the ASCII character codes since we are
    // only suppose to recieve initials as player identifiers.

    const SimpleVector<const Player *> &participatingPlayers = gameSession.players();
    SimpleHashMap<char, PlayerResult, 128> *resultLookup = new SimpleHashMap<char, PlayerResult, 128>();

    // Some players may not even capture a scorable box. So, we need to loop through
    // each player that was flagged as participating so we can initialize their
    // data in our lookup.
    for (int index = 0; index < participatingPlayers.size(); index++)
    {
        const Player *player = participatingPlayers.get(index);
        char playerInitial = player->playerInitial();

        PlayerResult &playerResult = resultLookup->at(playerInitial);

        // Set default values for the player.
        playerResult._playerInitial = playerInitial;
        playerResult._score = 0;
        playerResult._winKind = PlayerResult::WIN_KIND::loser;
    }

    // Retrieve scorable slots from the game board where initials indicate captured boxes.
    SimpleVector<GameBoardSlot> *initialBoardSlots =
        gameBoard.computeScorableSlots(GameBoardSlot::SLOT_KIND::initial);

    // Update scores for players based on captured slots.
    for (int index = 0; index < initialBoardSlots->size(); index++)
    {
        GameBoardSlot &initialBoardSlot = initialBoardSlots->at(index);
        const PlayerTurn &playerTurn = initialBoardSlot.playerTurn();

        char playerInitial = playerTurn.playerInitial();
        PlayerResult &playerResult = resultLookup->at(playerInitial);

        // Increment the player's score and update the highest score if needed
        playerResult._score += 1;
        if (playerResult._score > highestScore)
        {
            highestScore = playerResult._score;
        }
    }

    int winnerCount = 0;
    WIN_KIND winKind = WIN_KIND::nocontest;

    // Collect results from the lookup map
    SimpleVector<PlayerResult> *playerResults = resultLookup->values();

    // Determine winners and their count if the highest score is greater than zero.
    if (highestScore > 0)
    {
        for (int index = 0; index < playerResults->size(); index++)
        {
            PlayerResult &playerResult = playerResults->at(index);

            if (playerResult._score == highestScore)
            {
                playerResult._winKind = PlayerResult::WIN_KIND::winner;
                winnerCount += 1;
            }
        }

        // Determine if the win is singular or a tie based on the number of winners.
        winKind = (winnerCount > 1) ? WIN_KIND::multiple : WIN_KIND::singular;
    }

    // Sort results alphabetically by player initials.
    playerResults->sort([](const PlayerResult &a, const PlayerResult &b)
    {
        char aPlayerInitial = a.playerInitial();
        char bPlayerInitial = b.playerInitial();

        if (aPlayerInitial > bPlayerInitial) {
            return 1;
        }

        return 0;
    });

    delete resultLookup;

    // Create and return a new GameResult instance with computed results.
    return new GameResult(playerResults, winKind, highestScore);
}

GameResult::GameResult(SimpleVector<PlayerResult> *playerResults, WIN_KIND winKind, int highestScore)
{
    // Constructor to initialize a GameResult object.
    this->_playerResults = playerResults;
    this->_highestScore = highestScore;
    this->_winKind = winKind;
}

GameResult::GameResult(const GameResult &playerResult)
{
    // Copy Constructor for game result
    this->_playerResults = playerResult._playerResults;
    this->_highestScore = playerResult._highestScore;
    this->_winKind = playerResult._winKind;
}

GameResult::~GameResult()
{
    // Destructor to clean up resources.
    delete this->_playerResults;
}

bool GameResult::operator==(const GameResult &rightHandResult) const
{
    // Equality operator to compare GameResult objects by instance (nominal comparison).
    return this == &rightHandResult;
}

bool GameResult::operator!=(const GameResult &rightHandResult) const
{
    // See `GameResult::operator==` for reasoning.
    return this != &rightHandResult;
}

void GameResult::serializeGameResult(ostream &outputStream) const
{
    // Method to serialize the game result and print it to the console
    SimpleVector<PlayerResult> *playerResults = this->_playerResults;

    for (int index = 0; index < playerResults->size(); index++)
    {
        PlayerResult &playerResult = playerResults->at(index);

        char playerInitial = playerResult.playerInitial();
        int score = playerResult.score();
        PlayerResult::WIN_KIND winKind = playerResult.winKind();

        // Display the player's score and statue
        outputStream
            << "Player " << playerInitial
            << " has " << score << ((score == 1) ? " box" : " boxes");

        // Display the win status for the player
        if (winKind == PlayerResult::WIN_KIND::winner)
        {
            switch (this->_winKind)
            {
            case WIN_KIND::singular:
                outputStream << " (win)";
                break;

            case WIN_KIND::multiple:
                outputStream << " (tie)";
                break;

            default:
                throw string("bad member 'GameResult._playerResults' in 'GameResult.serializeGameResult()' (PlayerResult '") + to_string(playerInitial) + string("' cannot have winning state and game session be no contest or undefined win states)");
            }
        }
        else if (
            this->_winKind == WIN_KIND::nocontest && winKind == PlayerResult::WIN_KIND::loser)
        {
            outputStream << " (no contest)";
        }

        outputStream << ".";

        // We only want to newline when we are looping every result before the
        // last one. The calling code should determine if they need a trailing
        // new line on the output.
        if (index < (playerResults->size() - 1))
        {
            outputStream << endl;
        }
    }
}