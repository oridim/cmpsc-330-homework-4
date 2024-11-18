#include <iostream>
#include <string>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board.h"
#include "game_session.h"

#include "player.h"
#include "basic_strategy_ai_player.h"
#include "random_ai_player.h"

#include "game_configuration.h"


GameConfiguration::PLAYER_KIND GameConfiguration::_determinePlayerKind(string kindIdentifier)
{
    // Determine the type of player based on the kind identifier
    // Switch statement to select the appropriate player kind based on the serialized input.
    if (kindIdentifier == "Random")
    {
        return PLAYER_KIND::random;
    }
    else if (kindIdentifier == "Strategic")
    {
        return PLAYER_KIND::strategic;
    }

    // Throws an error if the identifier is not recognized
    throw string("bad argument #0 to 'GameConfiguration::_determinePlayerKind(char *)' (player identifier '") + string(kindIdentifier) + string("' is not supported)");
}


Player *GameConfiguration::_makePlayerKind(PLAYER_KIND playerKind, char playerInitial)
{
    // Creates a player based on the type (Random or Strategic) and their initial
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

GameConfiguration *GameConfiguration::deserializeGameConfiguration(istream &inputStream)
{
    // Deserialize a gmae configuration from an imput stream

    // The SimpleHashMap used here does not dynamically resize.
    // The map is set to have a fixed size of 16 to handle up to 16 players (just in case).

    int columns;
    int rows;
    // Create a SimpleHashMap to store the player's initial and their kind
    SimpleHashMap<char, PLAYER_KIND, 16> *players = new SimpleHashMap<char, PLAYER_KIND, 16>();

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
        players->at(toupper(playerInitial.at(0))) = _determinePlayerKind(kindIdentifier);
    }

    // Return a new GameConfiguration object with the read values
    return new GameConfiguration(rows, columns, players);
}

GameConfiguration::GameConfiguration()
{
    this->_columns = -1;
    this->_rows = -1;

    this->_players = new SimpleHashMap<char, PLAYER_KIND, 16>();
}


GameConfiguration::GameConfiguration(int rows, int columns, SimpleHashMap<char, PLAYER_KIND, 16> *players)
{
    // Constructor for GameConfiguration
    this->_columns = columns;
    this->_rows = rows;

    this->_players = players;
}


GameConfiguration::GameConfiguration(const GameConfiguration &gameConfiguration)
{
    // Copy Constructor for GameConfiguration
    this->_columns = gameConfiguration._columns;
    this->_rows = gameConfiguration._rows;

    // Copy the players hash map (deep copy) from the provided GameConfiguration
    this->_players = new SimpleHashMap<char, PLAYER_KIND, 16>(*gameConfiguration._players);
}


GameConfiguration::~GameConfiguration()
{
    // Destructor for GameConfiguration, frees the dynamically allocated memory for players
    delete this->_players;
}


bool GameConfiguration::operator==(const GameConfiguration &rightHandConfiguration) const
{
    // Equality operator for comparing two GameConfiguration objects
    return this == &rightHandConfiguration;
}


bool GameConfiguration::operator!=(const GameConfiguration &rightHandConfiguration) const
{
    // Inequality operator for comparing two GameConfiguration objects
    return this != &rightHandConfiguration;
}

GameBoard *GameConfiguration::makeGameBoard()
{
    return new GameBoard(this->_rows, this->_columns);
}

GameSession *GameConfiguration::makeGameSession()
{
    SimpleHashMap<char, PLAYER_KIND, 16> *playerLookup = this->_players;
    SimpleVector<char> *playerInitials = playerLookup->keys();

    SimpleVector<const Player *> *players = new SimpleVector<const Player *>();

    for (int index = 0; index < playerInitials->size(); index++)
    {
        char playerInitial = playerInitials->at(index);
        PLAYER_KIND &playerKind = playerLookup->at(playerInitial);

        Player *player = GameConfiguration::_makePlayerKind(playerKind, playerInitial);
        players->push_back(player);
    }

    GameSession *gameSession = new GameSession(players);

    delete playerInitials;
    return gameSession;
}