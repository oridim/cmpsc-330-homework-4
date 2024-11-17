#include <iostream>
#include <string>

#include "simple_hash_map.h"

#include "player.h"
#include "basic_strategy_ai_player.h"
#include "random_ai_player.h"

#include "game_configuration.h"

// Determine the type of player based on the kind identifier
GameConfiguration::PLAYER_KIND GameConfiguration::_determinePlayerKind(char *kindIdentifier)
{
    // Compares the string kindIdentifier with "Random" and "Strategic".
    if (strcmp(kindIdentifier, "Random"))
    {
        return PLAYER_KIND::random;
    }
    else if (strcmp(kindIdentifier, "Strategic"))
    {
        return PLAYER_KIND::strategic;
    }

    // Throws an error if the identifier is not recognized
    throw string("bad argument #0 to 'GameConfiguration::_determinePlayerKind(char *)' (player identifier '") + string(kindIdentifier) + string("' is not supported)");
}

// Creates a player based on the type (Random or Strategic) and their initial
Player *GameConfiguration::_makePlayerKind(PLAYER_KIND playerKind, char playerInitial)
{
    // Switch statement to create the appropriate player based on the player kind
    switch (playerKind)
    {
    case PLAYER_KIND::random:
        return new RandomAIPlayer(playerInitial);

    case PLAYER_KIND::strategic:
        return new BasicStrategyAIPlayer(playerInitial);

    default:
        throw string("bad argument #0 to 'GameConfiguration::_makePlayerKind(PLAYER_KIND, char)' (player kind ") + to_string(static_cast<int>(playerKind)) + string(" is not supported)");
    }
}

// Deserialize a gmae configuration from an imput stream
GameConfiguration *GameConfiguration::deserializeGameConfiguration(istream &inputStream)
{
    // The SimpleHashMap used here does not dynamically resize.
    // The map is set to have a fixed size of 16 to handle up to 16 players (just in case).

    int columns;
    int rows;
    // Create a SimpleHashMap to store the player's initial and their kind
    SimpleHashMap<char, string, 16> *players = new SimpleHashMap<char, string, 16>();

    // Reading the number of rows and columns from the input stream
    inputStream >> rows >> columns;

    string playerInitial;
    string kindIdentifier;

    // Looping through the input stream to read player information
    while (inputStream >> playerInitial)
    {
        if (playerInitial == "END")
        {
            break;
        }

        inputStream >> kindIdentifier;

        // Store the player's kind in the hash map using their initial
        players->at(toupper(playerInitial.at(0))) = kindIdentifier;
    }

    // Return a new GameConfiguration object with the read values
    return new GameConfiguration(rows, columns, players);
}

GameConfiguration::GameConfiguration()
{
    this->_columns = -1;
    this->_rows = -1;

    this->_players = new SimpleHashMap<char, string, 16>();
}

// Constructor for GameConfiguration
GameConfiguration::GameConfiguration(int rows, int columns, SimpleHashMap<char, string, 16> *players)
{
    this->_columns = columns;
    this->_rows = rows;

    this->_players = players;
}

// Copy Constructor for GameConfiguration
GameConfiguration::GameConfiguration(const GameConfiguration &gameConfiguration)
{
    this->_columns = gameConfiguration._columns;
    this->_rows = gameConfiguration._rows;

    // Copy the players hash map (deep copy) from the provided GameConfiguration
    this->_players = new SimpleHashMap<char, string, 16>(*gameConfiguration._players);
}

// Destructor for GameConfiguration, frees the dynamically allocated memory for players
GameConfiguration::~GameConfiguration()
{
    delete this->_players;
}

// Equality operator for comparing two GameConfiguration objects
bool GameConfiguration::operator==(const GameConfiguration &rightHandConfiguration) const
{
    return this == &rightHandConfiguration;
}

// Inequality operator for comparing two GameConfiguration objects
bool GameConfiguration::operator!=(const GameConfiguration &rightHandConfiguration) const
{
    // See `GameConfiguration::operator==` for reasoning.
    return this != &rightHandConfiguration;
}
