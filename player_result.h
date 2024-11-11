#ifndef _PLAYER_RESULT_H_
#define _PLAYER_RESULT_H_

// `class PlayerResult`
//
// Represents structured data containing the winner data of a Dots and Boxes
// game player.
class PlayerResult
{
    friend class GameResult;

public:
    // `enum int PlayerResult::WIN_KIND`
    //
    // Represents an enumeration of all possible win states a Dots and Boxes
    // game player can end as once a game is finished.
    enum class WIN_KIND
    {
        // `PlayerResult::WIN_KIND::undefined`
        //
        // Represents that the player has an undefined win state.
        undefined,

        // `PlayerResult::WIN_KIND::loser`
        //
        // Represents that the player lost the game.
        loser,

        // `PlayerResult::WIN_KIND::winner`
        //
        // Represents that the player won or tied the game.
        winner
    };

private:
    // `char PlayerResult._playerInitial`
    //
    // Represents the initial used by the player as their identifier.
    char _playerInitial;

    // `int PlayerResult._score`
    //
    // Represents the score of the player.
    int _score;

    // `PlayerResult::WIN_KIND GameResult._winKind`
    //
    // Represents the winning state of the player.
    //
    // **SEE**: `WIND_KIND` for more details.
    WIN_KIND _winKind;

public:
    PlayerResult();
    PlayerResult(
        char playerInitial, int score, WIN_KIND winKind = WIN_KIND::undefined);

    PlayerResult(const PlayerResult &playerResult);

    bool operator==(const PlayerResult &rightHandResult) const;
    bool operator!=(const PlayerResult &rightHandResult) const;

    char playerInitial() const { return this->_playerInitial; }
    int score() const { return this->_score; }
    WIN_KIND winKind() const { return this->_winKind; }
};

#endif