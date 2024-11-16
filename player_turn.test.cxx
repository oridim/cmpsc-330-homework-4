#include <iostream>

#include "player_move.cxx"
#include "player_turn.cxx"

using namespace std;

int main()
{
      // Output to indicate the start of the unit test
     cout << "=> [UNIT TEST: player_turn.test.cxx]" << endl
          << endl;

     // Create two PlayerTurn objects with identical values
     PlayerTurn playerTurn1(3, 2, 4, 'D');
     PlayerTurn playerTurn2(3, 2, 4, 'D');

     // Display the values of playerTurn1 to verify correct initialization
     cout << "playerTurn1 = PlayerTurn(3, 2, 4, 'D'): " << endl
          << endl
          << "\tplayerTurn1.turnIndex()\t\t= " << playerTurn1.turnIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurn1.row()\t\t= " << playerTurn1.rowIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurn1.column()\t\t= " << playerTurn1.columnIndex() << "\t(SHOULD BE: 4)" << endl
          << "\tplayerTurn1.playerInitial()\t= '" << playerTurn1.playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

      // Test the equality and inequality operators
     cout << endl
          << "PlayerTurn::operator==, PlayerTurn::operator!=" << endl
          << endl
          << "\tplayerTurn1 == playerTurn1:\t" << ((playerTurn1 == playerTurn1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tplayerTurn1 != playerTurn1:\t" << ((playerTurn1 != playerTurn1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tplayerTurn1 == playerTurn2:\t" << ((playerTurn1 == playerTurn2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tplayerTurn1 != playerTurn2:\t" << ((playerTurn1 != playerTurn2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     // Create a copy of playerTurn1 using the copy constructor
     PlayerTurn playerTurnCopy(playerTurn1);

     // Display the values of playerTurnCopy to verify correct copying
     cout << "playerTurnCopy = PlayerTurn(playerTurn1): " << endl
          << endl
          << "\tplayerTurnCopy.turnIndex()\t= " << playerTurnCopy.turnIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tplayerTurnCopy.row()\t\t= " << playerTurnCopy.rowIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tplayerTurnCopy.column()\t\t= " << playerTurnCopy.columnIndex() << "\t(SHOULD BE: 4)" << endl
          << "\tplayerTurnCopy.playerInitial()\t= '" << playerTurnCopy.playerInitial() << "'" << "\t(SHOULD BE: 'D')" << endl;

     return 0;
}