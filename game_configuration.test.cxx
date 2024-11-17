#include <fstream>
#include <iostream>
#include <string>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.cxx"
#include "game_board.cxx"

#include "game_configuration.cxx"
#include "game_session.cxx"

#include "player_move.cxx"
#include "player_turn.cxx"

#include "player.h"
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

     const SimpleHashMap<char, GameConfiguration::PLAYER_KIND, 16UL> &playerLookup = gameConfiguration1->players();
     SimpleVector<char> *playerInitials = playerLookup.keys();

     cout << "*gameConfiguration1 = GameConfiguration::deserializeGameConfiguration(inputStream ['./Test Cases/GameConfiguration/configuration.professor-supplied.txt']): " << endl
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
          GameConfiguration::PLAYER_KIND playerKind = playerLookup.get(playerInitial);

          cout
              << "\tgameConfiguration1->players()->get('" << playerInitial << "')"
              << "\t= " << static_cast<int>(playerKind) << endl;
     }

     GameSession *gameSession = gameConfiguration1->makeGameSession();

     cout << endl
          << "gameSession = gameConfiguration1->makeGameSession(): " << endl
          << endl
          << "\tgameSession.players.size()\t= " << gameSession->players().size() << "\t(SHOULD BE: 2)" << endl
          << "\tgameSession.nextTurnIndex()\t= " << gameSession->nextTurnIndex() << "\t(SHOULD BE: 0)" << endl;

     cout << endl
          << "gameSession->players():" << endl
          << endl
          << "\tgameSession->players()->get(0)\t= Player('B')\t(SHOULD BE)" << endl
          << "\tgameSession->players()->get(1)\t= Player('R')\t(SHOULD BE)" << endl
          << endl;

     const SimpleVector<const Player *> &players = gameSession->players();

     for (int index = 0; index < players.size(); index++)
     {
          const Player *player = players.get(index);
          char playerInitial = player->playerInitial();

          cout
              << "\tgameSession->players()->get(" << index << ")"
              << "\t= Player('" << playerInitial << "')" << endl;
     }

     GameBoard *gameBoard = gameConfiguration1->makeGameBoard();

     cout << endl
          << "*gameBoard = gameConfiguration1->makeGameBoard(): " << endl
          << endl
          << "\tgameBoard->rows()\t\t= " << gameBoard->rows() << "\t(SHOULD BE: 3)" << endl
          << "\tgameBoard->columns()\t\t= " << gameBoard->columns() << "\t(SHOULD BE: 8)" << endl
          << endl
          << "\tgameBoard->rowPadding()\t\t= " << gameBoard->rowPadding() << "\t(SHOULD BE: 2)" << endl
          << "\tgameBoard->columnPadding()\t= " << gameBoard->columnPadding() << "\t(SHOULD BE: 7)" << endl
          << endl
          << "\tgameBoard->expandedRows()\t= " << gameBoard->expandedRows() << "\t(SHOULD BE: 5)" << endl
          << "\tgameBoard->expandedColumns()\t= " << gameBoard->expandedColumns() << "\t(SHOULD BE: 15)" << endl
          << endl;

     cout << "gameBoard.serializeGameBoard(cout):" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0         1    " << endl
          << "   012345678901234" << endl
          << "00 . . . . . . . ." << endl
          << " 1                " << endl
          << " 2 . . . . . . . ." << endl
          << " 3                " << endl
          << " 4 . . . . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard->serializeGameBoard(cout);

     GameConfiguration gameConfiguration2 = GameConfiguration();

     // Output test results for equality and inequality operators
     cout << endl
          << endl
          << "GameConfiguration::operator==, GameConfiguration::operator!=" << endl
          << endl
          << "\tgameConfiguration1 == gameConfiguration1:\t" << ((*gameConfiguration1 == *gameConfiguration1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tgameConfiguration1 != gameConfiguration1:\t" << ((*gameConfiguration1 != *gameConfiguration1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameConfiguration1 == gameConfiguration2:\t" << ((*gameConfiguration1 == gameConfiguration2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameConfiguration1 != gameConfiguration2:\t" << ((*gameConfiguration1 != gameConfiguration2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     delete gameBoard;
     delete gameSession;
     delete playerInitials;
     delete gameConfiguration1;

     return 0;
}