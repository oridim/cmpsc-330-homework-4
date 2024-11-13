#include <iostream>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "player_result.h"
#include "player_result.cxx"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_board.test.cxx]" << endl
          << endl;

     GameBoard gameBoard1(3, 5);
     GameBoard gameBoard2(3, 5);

     cout << "gameBoard1 = GameBoard(3, 5): " << endl
          << endl
          << "\tgameBoard1.rows()\t\t= " << gameBoard1.rows() << "\t(SHOULD BE: 3)" << endl
          << "\tgameBoard1.columns()\t\t= " << gameBoard1.columns() << "\t(SHOULD BE: 5)" << endl
          << endl
          << "\tgameBoard1.rowPadding()\t\t= " << gameBoard1.rowPadding() << "\t(SHOULD BE: 2)" << endl
          << "\tgameBoard1.columnPadding()\t= " << gameBoard1.columnPadding() << "\t(SHOULD BE: 4)" << endl
          << endl
          << "\tgameBoard1.expandedRows()\t= " << gameBoard1.expandedRows() << "\t(SHOULD BE: 5)" << endl
          << "\tgameBoard1.expandedColumns()\t= " << gameBoard1.expandedColumns() << "\t(SHOULD BE: 9)" << endl
          << endl;

     cout << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1          " << endl
          << " 2 . . . . ." << endl
          << " 3          " << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1.renderGameBoard();

     cout << endl
          << endl
          << "GameBoard::operator==, GameBoard::operator!=" << endl
          << endl
          << "\tgameBoard1 == gameBoard1:\t" << ((gameBoard1 == gameBoard1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tgameBoard1 != gameBoard1:\t" << ((gameBoard1 != gameBoard1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameBoard1 == gameBoard2:\t" << ((gameBoard1 == gameBoard2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameBoard1 != gameBoard2:\t" << ((gameBoard1 != gameBoard2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     SimpleVector<GameBoardSlot> *legalSlots1 = gameBoard1.computeLegalSlots();

     cout << "legalSlots1 = gameBoard1.computeLegalSlots()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "(0, 1)" << endl
          << "(0, 3)" << endl
          << "(0, 5)" << endl
          << "(0, 7)" << endl
          << "(1, 0)" << endl
          << "(1, 2)" << endl
          << "(1, 4)" << endl
          << "(1, 6)" << endl
          << "(1, 8)" << endl
          << "(2, 1)" << endl
          << "(2, 3)" << endl
          << "(2, 5)" << endl
          << "(2, 7)" << endl
          << "(3, 0)" << endl
          << "(3, 2)" << endl
          << "(3, 4)" << endl
          << "(3, 6)" << endl
          << "(3, 8)" << endl
          << "(4, 1)" << endl
          << "(4, 3)" << endl
          << "(4, 5)" << endl
          << "(4, 7)" << endl
          << endl;

     cout << "(ACTUAL)" << endl
          << endl;

     for (int index = 0; index < legalSlots1->size(); index++)
     {
          GameBoardSlot &slot = legalSlots1->at(index);

          cout << "(" << slot.rowIndex() << ", " << slot.columnIndex() << ")" << endl;
     }

     cout << endl
          << "gameBoard1.applyTurn(playerTurn1...6)"
          << endl;

     PlayerTurn playerTurn1(0, 0, 7, 'A');
     PlayerTurn playerTurn2(1, 1, 4, 'B');
     PlayerTurn playerTurn3(2, 2, 3, 'C');
     PlayerTurn playerTurn4(3, 3, 8, 'A');
     PlayerTurn playerTurn5(4, 4, 5, 'B');
     PlayerTurn playerTurn6(5, 3, 6, 'C');

     gameBoard1.applyTurn(playerTurn1);
     gameBoard1.applyTurn(playerTurn2);
     gameBoard1.applyTurn(playerTurn3);
     gameBoard1.applyTurn(playerTurn4);
     gameBoard1.applyTurn(playerTurn5);
     gameBoard1.applyTurn(playerTurn6);

     cout << endl
          << "legalSlots2 = gameBoard1.computeLegalSlots()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "(0, 1)" << endl
          << "(0, 3)" << endl
          << "(0, 5)" << endl
          << "(1, 0)" << endl
          << "(1, 2)" << endl
          << "(1, 6)" << endl
          << "(1, 8)" << endl
          << "(2, 1)" << endl
          << "(2, 5)" << endl
          << "(2, 7)" << endl
          << "(3, 0)" << endl
          << "(3, 2)" << endl
          << "(3, 4)" << endl
          << "(4, 1)" << endl
          << "(4, 3)" << endl
          << "(4, 7)" << endl
          << endl;

     cout << "(ACTUAL)" << endl
          << endl;

     SimpleVector<GameBoardSlot> *legalSlots2 = gameBoard1.computeLegalSlots();

     for (int index = 0; index < legalSlots2->size(); index++)
     {
          GameBoardSlot &slot = legalSlots2->at(index);

          cout << "(" << slot.rowIndex() << ", " << slot.columnIndex() << ")" << endl;
     }

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . .a." << endl
          << " 1     b    " << endl
          << " 2 . .c. . ." << endl
          << " 3       c a" << endl
          << " 4 . . .b. ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1.renderGameBoard();

     cout << endl
          << endl
          << "lineSlots = gameBoard1.computeKindSlots(GameBoardSlot::SLOT_KIND::line)" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "(0, 7)" << endl
          << "(1, 4)" << endl
          << "(2, 3)" << endl
          << "(3, 6)" << endl
          << "(3, 8)" << endl
          << "(4, 5)" << endl
          << endl;

     cout << "(ACTUAL)" << endl
          << endl;

     SimpleVector<GameBoardSlot> *lineSlots = gameBoard1.computeKindSlots(GameBoardSlot::SLOT_KIND::line);

     for (int index = 0; index < lineSlots->size(); index++)
     {
          GameBoardSlot &slot = lineSlots->at(index);

          cout << "(" << slot.rowIndex() << ", " << slot.columnIndex() << ")" << endl;
     }

     delete legalSlots1;
     delete legalSlots2;
     delete lineSlots;

     return 0;
}