#include <iostream>
#include <string>

#include "simple_hash_map.h"

#include "player.h"
#include "basic_strategy_ai_player.h"
#include "random_ai_player.h"

#include "game_configuration.h"

GameConfiguration::PLAYER_KIND GameConfiguration::_determinePlayerKind(char *kindIdentifier)
{
    if (strcmp(kindIdentifier, "Random"))
    {
        return PLAYER_KIND::random;
    }
    else if (strcmp(kindIdentifier, "Strategic"))
    {
        return PLAYER_KIND::strategic;
    }

    throw string("bad argument #0 to 'GameConfiguration::_determinePlayerKind(char *)' (player identifier '") + string(kindIdentifier) + string("' is not supported)");
}

Player *GameConfiguration::_makePlayerKind(PLAYER_KIND playerKind, char playerInitial)
{
    switch (playerKind)
    {
    case PLAYER_KIND::random:
        return new RandomAIPlayer(playerInitial);

    case PLAYER_KIND::strategic:
        return new BasicStrategyAIPlayer(playerInitial);
    }

    throw string("bad argument #0 to 'GameConfiguration::_makePlayerKind(PLAYER_KIND, char)' (player kind ") + to_string(static_cast<int>(playerKind)) + string(" is not supported)");
}

GameConfiguration *GameConfiguration::deserializeGameConfiguration(istream &inputStream)
{
    // **HACK:** Since the hashmap implementation does not dynamically grow we
    // have to make it allocate a fixed size. Obviously this is inefficient.
    //
    // Dr. Na said that we should not expect any more than two players supplied
    // as input to our code. But just in case... I would not expect more than
    // 16 players...
    //
    // BECAUSE THAT WOULD JUST BE CRAY CRAY!
    int columns;
    int rows;
    SimpleHashMap<char, string, 16> *players = new SimpleHashMap<char, string, 16>();

    inputStream >> rows >> columns;

    string playerInitial;
    string kindIdentifier;

    while (inputStream >> playerInitial)
    {
        if (playerInitial == "END")
        {
            break;
        }

        inputStream >> kindIdentifier;

        players->at(toupper(playerInitial.at(0))) = kindIdentifier;
    }

    return new GameConfiguration(rows, columns, players);
}

GameConfiguration::GameConfiguration(int rows, int columns, SimpleHashMap<char, string, 16> *players)
{
    this->_columns = columns;
    this->_rows = rows;

    this->_players = players;
}

GameConfiguration::GameConfiguration(const GameConfiguration &gameConfiguration)
{
    this->_columns = gameConfiguration._columns;
    this->_rows = gameConfiguration._rows;

    this->_players = new SimpleHashMap<char, string, 16>(gameConfiguration._players);
}

GameConfiguration::~GameConfiguration()
{
    delete this->_players;
}

bool GameConfiguration::operator==(const GameConfiguration &rightHandConfiguration) const
{
    return this == &rightHandConfiguration;
}

bool GameConfiguration::operator!=(const GameConfiguration &rightHandConfiguration) const
{
    // See `GameConfiguration::operator==` for reasoning.
    return this != &rightHandConfiguration;
}
