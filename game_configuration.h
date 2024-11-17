#ifndef _GAME_CONFIGURATION_H_
#define _GAME_CONFIGURATION_H_

#include <iostream>

#include "simple_hash_map.h"

#include "player.h"

#include "game_session.h"

// `class GameConfiguration`
//
// Represents structured data containing the configuration of a Dots and Boxes
// game session.
class GameConfiguration
{
public:
    // `enum int GameConfiguration::PLAYER_KIND`
    //
    // Represents an enumeration of all possible win states a Dots and Boxes
    // game can finish as.
    enum class PLAYER_KIND
    {
        // `GameConfiguration::PLAYER_KIND::undefined`
        //
        // Represents a type of player that is unhandled.
        undefined,

        // `GameConfiguration::PLAYER_KIND::human`
        //
        // Represents a player that is controlled by a human.
        human,

        // `GameConfiguration::PLAYER_KIND::random`
        //
        // Represents an AI player that plays randomly with no strategy.
        random,

        // `GameConfiguration::PLAYER_KIND::strategic`
        //
        // Represents an AI player that players strategically with a minimal
        // heuristic strategy.
        strategic
    };

    static GameConfiguration *deserializeGameConfiguration(istream &inputStream);

private:
    // `PLAYER_KIND GameConfiguration::_determinePlayerKind(char *kindIdentifier)`
    //
    // Returns the matching `PLAYER_KIND` enum value in regards to the
    // serialized `kindIdentifier`.
    static PLAYER_KIND _determinePlayerKind(char *kindIdentifier);

    // `Player *GameConfiguration::_makePlayerKind(PLAYER_KIND playerKind, char playerInitial)`
    //
    // Returns a newly allocated `Player` implementing class instance in
    // regards to the `playerKind`.
    static Player *_makePlayerKind(PLAYER_KIND playerKind, char playerInitial);

private:
    // `int GameConfiguration._columns`
    //
    // Represents how many rows of dots there will be in the Dots and Boxes
    // gameboard grid.
    int _columns;

    // `int GameConfiguration._rows`
    //
    // Represents how many columns of dots there will be in the Dots and Boxes
    // gameboard grid.
    int _rows;

    // `SimpleHashMap<char, string, 16> *GameConfiguration._players`
    //
    // Represents players and their configured player kinds.
    SimpleHashMap<char, string, 16> *_players;

public:
    GameConfiguration();
    GameConfiguration(
        int rows, int columns, SimpleHashMap<char, string, 16> *players);

    GameConfiguration(const GameConfiguration &GameConfiguration);

    ~GameConfiguration();

    bool operator==(const GameConfiguration &rightHandResult) const;
    bool operator!=(const GameConfiguration &rightHandResult) const;

    int columns() const { return this->_columns; }
    const SimpleHashMap<char, string, 16> &players() const { return *this->_players; }
    int rows() const { return this->_rows; }
};

#endif