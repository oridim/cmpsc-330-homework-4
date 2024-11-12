#include <iostream>

#include "player_turn.h"
#include "player_turn.cxx"

#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "player.h"
#include "player.cxx"

#include "random_ai_player.h"
#include "random_ai_player.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: random_ai_player.test.cxx]" << endl
          << endl;

     // **NOTE**: We need to seed our randomness with a constant number here
     // so our random AI players always generating the same moves.
     //
     // This allows us to check for correctness in the unit tests.
     //srand(time(0));
     srand(0);

     GameBoard gameBoard1(3, 5);

     RandomAIPlayer randomAIPlayer1('D');
     RandomAIPlayer randomAIPlayer2('O');

     PlayerTurn *playerTurn1 = randomAIPlayer1.computePlayerTurn(gameBoard1);

     cout << "*playerTurn1 = randomAIPlayer1.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn1.turnIndex()\t\t= " << playerTurn1->turnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tplayerTurn1.row()\t\t= " << playerTurn1->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn1.column()\t\t= " << playerTurn1->columnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tplayerTurn1.playerInitial()\t= '" << playerTurn1->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     gameBoard1.applyTurn(*playerTurn1);

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
          << " 3 d        " << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1.renderGameBoard();

     PlayerTurn *playerTurn2 = randomAIPlayer2.computePlayerTurn(gameBoard1);

     cout << endl
          << endl
          << "*playerTurn2 = randomAIPlayer2.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn2.turnIndex()\t\t= " << playerTurn2->turnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn2.row()\t\t= " << playerTurn2->rowIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn2.column()\t\t= " << playerTurn2->columnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn2.playerInitial()\t= '" << playerTurn2->playerInitial() << "'" << "\t(SHOULD BE: 'O')" << endl;

     gameBoard1.applyTurn(*playerTurn2);

     cout << endl
          << "RandomAIPlayer::operator==, RandomAIPlayer::operator!=" << endl
          << endl
          << "\trandomAIPlayer1 == randomAIPlayer1:\t" << ((randomAIPlayer1 == randomAIPlayer1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\trandomAIPlayer1 != randomAIPlayer1:\t" << ((randomAIPlayer1 != randomAIPlayer1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\trandomAIPlayer1 == randomAIPlayer2:\t" << ((randomAIPlayer1 == randomAIPlayer2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\trandomAIPlayer1 != randomAIPlayer2:\t" << ((randomAIPlayer1 != randomAIPlayer2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl;

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1          " << endl
          << " 2 .o. . . ." << endl
          << " 3 d        " << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1.renderGameBoard();

     PlayerTurn *playerTurn3 = randomAIPlayer1.computePlayerTurn(gameBoard1);

     cout << endl
          << endl
          << "*playerTurn3 = randomAIPlayer1.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn3.turnIndex()\t\t= " << playerTurn3->turnIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn3.row()\t\t= " << playerTurn3->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn3.column()\t\t= " << playerTurn3->columnIndex() << "\t(SHOULD BE: 4)" << endl
          << "\tplayerTurn3.playerInitial()\t= '" << playerTurn3->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     gameBoard1.applyTurn(*playerTurn3);

     cout << endl
          << "gameBoard1.renderGameBoard():" << endl
          << endl;

     cout << "(SHOULD BE):" << endl
          << endl
          << "   0        " << endl
          << "   012345678" << endl
          << "00 . . . . ." << endl
          << " 1          " << endl
          << " 2 .o. . . ." << endl
          << " 3 d   d    " << endl
          << " 4 . . . . ." << endl
          << endl;

     cout << "(ACTUAL):" << endl
          << endl;

     gameBoard1.renderGameBoard();

     cout << endl
          << endl
          << "RandomAIPlayer::operator==, RandomAIPlayer::operator!=" << endl
          << endl
          << "\trandomAIPlayer1 == randomAIPlayer1:\t" << ((randomAIPlayer1 == randomAIPlayer1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\trandomAIPlayer1 != randomAIPlayer1:\t" << ((randomAIPlayer1 != randomAIPlayer1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\trandomAIPlayer1 == randomAIPlayer2:\t" << ((randomAIPlayer1 == randomAIPlayer2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\trandomAIPlayer1 != randomAIPlayer2:\t" << ((randomAIPlayer1 != randomAIPlayer2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     delete playerTurn2;
     delete playerTurn1;

     return 0;
}