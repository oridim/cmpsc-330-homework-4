#include <iostream>

#include "game_board.cxx"
#include "game_board_slot.cxx"

#include "game_session.cxx"

#include "player_move.cxx"
#include "player_turn.cxx"

#include "player.h"
#include "random_ai_player.cxx"

using namespace std;

int main()
{
     // Output indicating the start of the unit test for the RandomAIPlayer
     cout << "=> [UNIT TEST: random_ai_player.test.cxx]" << endl
          << endl;

     // srand(time(0));
     // Fixed seed for reproducibilty.
     srand(0);

     GameBoard gameBoard(3, 5);

     // Create two RandomAIPlayer objects with different player initials ('D' and 'O')
     RandomAIPlayer *randomAIPlayer1 = new RandomAIPlayer('D');
     RandomAIPlayer *randomAIPlayer2 = new RandomAIPlayer('O');

     // Create a vector to hold the players
     SimpleVector<const Player *> *playerSet = new SimpleVector<const Player *>();

     // Apply the first player's turn and get the result (should be Player 'D')
     playerSet->push_back(randomAIPlayer1);
     playerSet->push_back(randomAIPlayer2);

     // Create a GameSession object with the players
     GameSession gameSession(playerSet);

     PlayerTurn *playerTurn1 = gameSession.applyNextPlayerTurn(gameBoard);

     // Output the results of the first player's turn
     cout << "*playerTurn1 = randomAIPlayer1.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn1.turnIndex()\t\t= " << playerTurn1->turnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tplayerTurn1.row()\t\t= " << playerTurn1->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn1.column()\t\t= " << playerTurn1->columnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tplayerTurn1.playerInitial()\t= '" << playerTurn1->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     // Display the current game board state
     cout << endl
          << "gameBoard1.serializeGameBoard(cout):" << endl
          << endl;

     // Expected output: The game board with Player 'D' at row 3, column 0
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

     // Output the actual game board state after the first turn
     cout << "(ACTUAL):" << endl
          << endl;

     // Serialize and print the actual game board
     gameBoard.serializeGameBoard(cout);

     // Apply the second player's turn and get the result (should be Player 'O')
     PlayerTurn *playerTurn2 = gameSession.applyNextPlayerTurn(gameBoard);

     // Output the results of the second player's turn
     cout << endl
          << endl
          << "*playerTurn2 = randomAIPlayer2.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn2.turnIndex()\t\t= " << playerTurn2->turnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn2.row()\t\t= " << playerTurn2->rowIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn2.column()\t\t= " << playerTurn2->columnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tplayerTurn2.playerInitial()\t= '" << playerTurn2->playerInitial() << "'" << "\t(SHOULD BE: 'O')" << endl;

     // Display the current game board state after the second player's turn
     cout << endl
          << "gameBoard1.serializeGameBoard(cout):" << endl
          << endl;

     // Expected output: The game board with Player 'O' at row 2, column 1
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

     // Output the actual game board state after the second turn
     cout << "(ACTUAL):" << endl
          << endl;

     // Serialize and print the actual game board
     gameBoard.serializeGameBoard(cout);

     // Apply the third player's turn and get the result (should be Player 'D')
     PlayerTurn *playerTurn3 = gameSession.applyNextPlayerTurn(gameBoard);

     // Output the results of the third player's turn
     cout << endl
          << endl
          << "*playerTurn3 = randomAIPlayer1.computePlayerTurn(gameBoard1): " << endl
          << endl
          << "\tplayerTurn3.turnIndex()\t\t= " << playerTurn3->turnIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn3.row()\t\t= " << playerTurn3->rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn3.column()\t\t= " << playerTurn3->columnIndex() << "\t(SHOULD BE: 4)" << endl
          << "\tplayerTurn3.playerInitial()\t= '" << playerTurn3->playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     // Display the current game board state after the third player's turn
     cout << endl
          << "gameBoard1.serializeGameBoard(cout):" << endl
          << endl;

     // Expected output: The game board with Player 'D' at row 3, column 4
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

     // Output the actual game board state after the third turn
     cout << "(ACTUAL):" << endl
          << endl;

     // Serialize and print the actual game board
     gameBoard.serializeGameBoard(cout);

     cout << endl;

     return 0;
}