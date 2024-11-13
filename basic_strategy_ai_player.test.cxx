#include <iostream>

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "game_session.h"
#include "game_session.cxx"

#include "player.h"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

#include "basic_strategy_ai_player.h"
#include "basic_strategy_ai_player.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: basic_strategy_ai_player.test.cxx]" << endl
          << endl;

     // **NOTE**: We need to seed our randomness with a constant number here
     // so our strategic AI players always generating the same moves.
     //
     // This allows us to check for correctness in the unit tests.
     // srand(time(0));
     srand(0);

     GameBoard gameBoard(3, 5);

     BasicStrategyAIPlayer *basicStrategyAIPlayer1 = new BasicStrategyAIPlayer('D');
     BasicStrategyAIPlayer *basicStrategyAIPlayer2 = new BasicStrategyAIPlayer('O');

     SimpleVector<const Player *> *playersBabadi = new SimpleVector<const Player *>();

     playersBabadi->push_back(basicStrategyAIPlayer1);
     playersBabadi->push_back(basicStrategyAIPlayer2);

     GameSession gameSession(playersBabadi);

     PlayerTurn *playerTurn1 = gameSession.applyNextPlayerTurn(gameBoard);

     cout << "*playerTurn1 = gameSession.applyNextPlayerTurn(gameBoard): " << endl
          << endl
          << "\tplayerTurn1.turnIndex()\t\t= " << playerTurn1->turnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tplayerTurn1.row()\t\t= " << playerTurn1->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn1.column()\t\t= " << playerTurn1->columnIndex() << "\t(SHOULD BE: 6)" << endl
          << "\tplayerTurn1.playerInitial()\t= '" << playerTurn1->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1          " << endl
          << " 2 . . . . ." << endl
          << " 3       d  " << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard.renderGameBoard();

     PlayerTurn *playerTurn2 = gameSession.applyNextPlayerTurn(gameBoard);

     cout << endl
          << endl
          << "*playerTurn2 = gameSession.applyNextPlayerTurn(gameBoard): " << endl
          << endl
          << "\tplayerTurn2.turnIndex()\t\t= " << playerTurn2->turnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn2.row()\t\t= " << playerTurn2->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn2.column()\t\t= " << playerTurn2->columnIndex() << "\t(SHOULD BE: 8)" << endl
          << "\tplayerTurn2.playerInitial()\t= '" << playerTurn2->playerInitial() << "'" << "\t(SHOULD BE: 'O')" << endl;

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1          " << endl
          << " 2 . . . . ." << endl
          << " 3       d o" << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard.renderGameBoard();

     PlayerTurn *playerTurn3 = gameSession.applyNextPlayerTurn(gameBoard);

     cout << endl
          << endl
          << "*playerTurn3 = gameSession.applyNextPlayerTurn(gameBoard): " << endl
          << endl
          << "\tplayerTurn3.turnIndex()\t\t= " << playerTurn3->turnIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn3.row()\t\t= " << playerTurn3->rowIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn3.column()\t\t= " << playerTurn3->columnIndex() << "\t(SHOULD BE: 8)" << endl
          << "\tplayerTurn3.playerInitial()\t= '" << playerTurn3->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1         d" << endl
          << " 2 . . . . ." << endl
          << " 3       d o" << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard.renderGameBoard();

     cout << endl;

     return 0;
}