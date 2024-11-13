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
    int highestScore = 0;

    // **NOTE**: We only need to test the ASCII character codes since we are
    // only suppose to recieve initials as player identifiers.

    const SimpleVector<Player *> &participatingPlayers = gameSession.players();
    SimpleHashMap<char, PlayerResult, 128> *resultLookup = new SimpleHashMap<char, PlayerResult, 128>();

    // Some players may not even capture a scorable box. So, we need to loop through
    // each player that was flagged as participating so we can initialize their
    // data in our lookup.
    for (int index = 0; index < participatingPlayers.size(); index++)
    {
        const Player *player = participatingPlayers.get(index);
        char playerInitial = player->playerInitial();

        PlayerResult &playerResult = resultLookup->at(playerInitial);

        playerResult._playerInitial = playerInitial;
        playerResult._score = 0;
        playerResult._winKind = PlayerResult::WIN_KIND::loser;
    }

    SimpleVector<GameBoardSlot> *initialBoardSlots =
        gameBoard.computeScorableSlots(GameBoardSlot::SLOT_KIND::initial);

    for (int index = 0; index < initialBoardSlots->size(); index++)
    {
        GameBoardSlot &initialBoardSlot = initialBoardSlots->at(index);
        const PlayerTurn &playerTurn = initialBoardSlot.playerTurn();

        char playerInitial = playerTurn.playerInitial();
        PlayerResult &playerResult = resultLookup->at(playerInitial);

        playerResult._score += 1;
        if (playerResult._score > highestScore)
        {
            highestScore = playerResult._score;
        }
    }

    int winnerCount = 0;
    WIN_KIND winKind = WIN_KIND::nocontest;

    SimpleVector<PlayerResult> *playerResults = resultLookup->values();

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

        winKind = (winnerCount > 1) ? WIN_KIND::multiple : WIN_KIND::singular;
    }

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

    return new GameResult(playerResults, winKind, highestScore);
}

GameResult::GameResult(SimpleVector<PlayerResult> *playerResults, WIN_KIND winKind, int highestScore)
{
    this->_playerResults = playerResults;
    this->_highestScore = highestScore;
    this->_winKind = winKind;
}

GameResult::GameResult(const GameResult &playerResult)
{
    this->_playerResults = playerResult._playerResults;
    this->_highestScore = playerResult._highestScore;
    this->_winKind = playerResult._winKind;
}

GameResult::~GameResult()
{
    delete this->_playerResults;
}

bool GameResult::operator==(const GameResult &rightHandResult) const
{
    // Usually the convention in most OOP languages I have done equality checking
    // is done by default as nominal instances rather then structural values.
    //
    // So we will just compare pointers here for nominal instance checking.
    return this == &rightHandResult;
}

bool GameResult::operator!=(const GameResult &rightHandResult) const
{
    // See `GameResult::operator==` for reasoning.
    return this != &rightHandResult;
}

void GameResult::renderGameResult() const
{
    SimpleVector<PlayerResult> *playerResults = this->_playerResults;

    for (int index = 0; index < playerResults->size(); index++)
    {
        PlayerResult &playerResult = playerResults->at(index);

        char playerInitial = playerResult.playerInitial();
        int score = playerResult.score();
        PlayerResult::WIN_KIND winKind = playerResult.winKind();

        cout
            << "Player " << playerInitial
            << " has " << score << ((score == 1) ? " box" : " boxes");

        if (winKind == PlayerResult::WIN_KIND::winner)
        {
            switch (this->_winKind)
            {
            case WIN_KIND::singular:
                cout << " (win)";
                break;

            case WIN_KIND::multiple:
                cout << " (tie)";
                break;

            default:
                throw string("bad member 'GameResult._playerResults' in 'GameResult.renderGameResult()' (PlayerResult '") + to_string(playerInitial) + string("' cannot have winning state and game session be no contest or undefined win states)");
            }
        }
        else if (
            this->_winKind == WIN_KIND::nocontest && winKind == PlayerResult::WIN_KIND::loser)
        {
            cout << " (no contest)";
        }

        cout << ".";

        // We only want to newline when we are looping every result before the
        // last one. The calling code should determine if they need a trailing
        // new line on the output.
        if (index < (playerResults->size() - 1))
        {
            cout << endl;
        }
    }
}