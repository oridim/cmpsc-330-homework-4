#include <iostream>

#include "simple_vector.h"

#include "game_board_slot.cxx"
#include "game_board.cxx"

#include "game_session.cxx"

#include "player_move.cxx"
#include "player_turn.cxx"

#include "dummy_player.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_session.test.cxx]" << endl
          << endl;

     // Create a dynamic vector to hold pointers to Player objects
     SimpleVector<const Player *> *playerSet = new SimpleVector<const Player *>();

     // Add two DummyPlayer objects to the vector, one for each player
     playerSet->push_back(new DummyPlayer('D'));
     playerSet->push_back(new DummyPlayer('O'));

     // We have to allocate a second vector below otherwise the first one
     // will be deleted twice by `gameSession2`'s deconstructor a 2nd time.
     GameSession gameSession1(playerSet);
     GameSession gameSession2 = GameSession();

     // Output gameSession1's details
     cout << "gameSession1 = GameSession(playerSet): " << endl
          << endl
          << "\tgameSession1.players.size()\t= " << gameSession1.players().size() << "\t(SHOULD BE: 2)" << endl
          << "\tgameSession1.nextTurnIndex()\t= " << gameSession1.nextTurnIndex() << "\t(SHOULD BE: 0)" << endl;

     // Output test results for equality and inequality operators
     cout << endl
          << "GameSession::operator==, GameSession::operator!=" << endl
          << endl
          << "\tgameSession1 == gameSession1:\t" << ((gameSession1 == gameSession1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tgameSession1 != gameSession1:\t" << ((gameSession1 != gameSession1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameSession1 == gameSession2:\t" << ((gameSession1 == gameSession2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameSession1 != gameSession2:\t" << ((gameSession1 != gameSession2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     return 0;
}