#include <fstream>
#include <iostream>
#include <string>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.cxx"
#include "game_board.cxx"

#include "game_configuration.cxx"

#include "player_move.cxx"
#include "player_turn.cxx"

#include "basic_strategy_ai_player.cxx"
#include "random_ai_player.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_configuration.test.cxx]" << endl
          << endl;

     ifstream inputStream;
     inputStream.open("./Test Cases/GameConfiguration/configuration.professor-supplied.txt");

     GameConfiguration *gameConfiguration1 =
         GameConfiguration::deserializeGameConfiguration(inputStream);
     inputStream.close();

     const SimpleHashMap<char, GameConfiguration::PLAYER_KIND, 16UL> &players = gameConfiguration1->players();
     SimpleVector<char> *playerInitials = players.keys();

     cout << "*gameConfiguration1 = GameConfiguration::deserializeGameConfiguration(inputStream ['./Test Cases/GameConfiguration/game.professor-supplied.txt']): " << endl
          << endl
          << "\tgameConfiguration1->rows()\t\t\t= " << gameConfiguration1->rows() << "\t(SHOULD BE: 3)" << endl
          << "\tgameConfiguration1->columns()\t\t\t= " << gameConfiguration1->columns() << "\t(SHOULD BE: 8)" << endl
          << "\tgameConfiguration1->players().keys()->size()\t= " << playerInitials->size() << "\t(SHOULD BE: 2)" << endl;

     cout << endl
          << "gameConfiguration1->players():" << endl
          << endl
          << "\tgameConfiguration1->players()->get('B')\t= 2\t(SHOULD BE)\t[GameConfiguration::PLAYER_KIND::random]" << endl
          << "\tgameConfiguration1->players()->get('R')\t= 3\t(SHOULD BE)\t[GameConfiguration::PLAYER_KIND::strategic]" << endl
          << endl;

     for (int index = 0; index < playerInitials->size(); index++)
     {
          char playerInitial = playerInitials->at(index);
          GameConfiguration::PLAYER_KIND playerKind = players.get(playerInitial);

          cout
              << "\tgameConfiguration1->players()->get('" << playerInitial << "')"
              << "\t= \"" << static_cast<int>(playerKind) << '"' << endl;
     }

     GameConfiguration gameConfiguration2 = GameConfiguration();

     // Output test results for equality and inequality operators
     cout << endl
          << "GameConfiguration::operator==, GameConfiguration::operator!=" << endl
          << endl
          << "\tgameConfiguration1 == gameConfiguration1:\t" << ((*gameConfiguration1 == *gameConfiguration1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tgameConfiguration1 != gameConfiguration1:\t" << ((*gameConfiguration1 != *gameConfiguration1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameConfiguration1 == gameConfiguration2:\t" << ((*gameConfiguration1 == gameConfiguration2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameConfiguration1 != gameConfiguration2:\t" << ((*gameConfiguration1 != gameConfiguration2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     delete playerInitials;
     delete gameConfiguration1;

     return 0;
}