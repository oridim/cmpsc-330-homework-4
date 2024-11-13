#include <fstream>
#include <iostream>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "game_data.h"
#include "game_data.cxx"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_data.test.cxx]" << endl
          << endl;

     ifstream inputStream;
     inputStream.open("./Test Cases/game.professor-supplied.txt");

     GameData *gameData1 = GameData::readGameData(inputStream);
     inputStream.close();

     SimpleVector<PlayerTurn> *turns2 = new SimpleVector<PlayerTurn>();

     GameData gameData2(0, 0, turns2);

     cout << "*gameData1 = GameData::readGameData(inputStream ['./Test Cases/game.professor-supplied.txt']): " << endl
          << endl
          << "\tgameData1->rows()\t\t= " << gameData1->rows() << "\t(SHOULD BE: 3)" << endl
          << "\tgameData1->columns()\t\t= " << gameData1->columns() << "\t(SHOULD BE: 8)" << endl;

     cout << endl
          << "gameData1->turns():" << endl
          << endl
          << "\tgameData1->turns().get(0)\t= PlayerTurn(1, 1, 0, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(1)\t= PlayerTurn(2, 0, 1, 'R')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(2)\t= PlayerTurn(3, 3, 2, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(3)\t= PlayerTurn(4, 4, 1, 'R')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(4)\t= PlayerTurn(5, 1, 4, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(5)\t= PlayerTurn(6, 2, 3, 'R')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(6)\t= PlayerTurn(7, 4, 3, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(7)\t= PlayerTurn(8, 3, 4, 'R')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(8)\t= PlayerTurn(9, 0, 3, 'R')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(9)\t= PlayerTurn(10, 1, 2, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(10)\t= PlayerTurn(11, 2, 1, 'B')\t(SHOULD BE)" << endl
          << "\tgameData1->turns().get(11)\t= PlayerTurn(12, 3, 0, 'B')\t(SHOULD BE)" << endl
          << endl;

     for (int index = 0; index < gameData1->turns().size(); index++)
     {
          const PlayerTurn &playerTurn = gameData1->turns().get(index);

          int columnIndex = playerTurn.columnIndex();
          int turnIndex = playerTurn.turnIndex();
          char playerInitial = playerTurn.playerInitial();
          int rowIndex = playerTurn.rowIndex();

          cout
              << "\tgameData1->turns().get(" << index << ")\t= PlayerTurn("
              << turnIndex << ", " << rowIndex << ", " << columnIndex << ", '" << playerInitial
              << "')" << endl;
     }

     cout << endl
          << "GameData::operator==, GameData::operator!=" << endl
          << endl
          << "\t*gameData1 == *gameData1:\t" << ((*gameData1 == *gameData1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\t*gameData1 != *gameData1:\t" << ((*gameData1 != *gameData1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\t*gameData1 == gameData2:\t" << ((*gameData1 == gameData2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\t*gameData1 != gameData2:\t" << ((*gameData1 != gameData2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     cout << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0         1    " << endl
          << "   012345678901234" << endl
          << "00 .r.r. . . . . ." << endl
          << " 1 b b b          " << endl
          << " 2 .b.r. . . . . ." << endl
          << " 3 b b r          " << endl
          << " 4 .r.b. . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     GameBoard *gameBoard1 = gameData1->makeGameBoard();
     gameBoard1->renderGameBoard();

     cout << endl
          << endl
          << "gameBoard1.applyScorableCaptures()" << endl
          << "gameBoard1.renderGameBoard()" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0         1" << endl
          << "   012345678901234" << endl
          << "00 .r.r. . . . . ." << endl
          << " 1 bBbBb          " << endl
          << " 2 .b.r. . . . . ." << endl
          << " 3 bBbRr          " << endl
          << " 4 .r.b. . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1->applyScorableCaptures();
     gameBoard1->renderGameBoard();

     cout << endl;

     delete gameBoard1;
     delete gameData1;
     // delete turns2; // **NOTE**: Handle by `gameData2` via `GameData::~GameData`

     return 0;
}