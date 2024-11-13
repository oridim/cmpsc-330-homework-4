#include <iostream>

#include "simple_vector.h"

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "random_ai_player.h"
#include "random_ai_player.cxx"

#include "player.h"
#include "player.cxx"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

#include "game_session.h"
#include "game_session.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_session.test.cxx]" << endl
          << endl;

     SimpleVector<Player> *players = new SimpleVector<Player>();

     players->push_back(RandomAIPlayer('D'));
     players->push_back(RandomAIPlayer('O'));

     // We have to allocate a second vector below otherwise the first one
     // will be deleted twice by `gameSession2`'s deconstructor a 2nd time.
     GameSession gameSession1(players);
     GameSession gameSession2(new SimpleVector<Player>(*players));

     cout << "gameSession1 = GameSession(&players): " << endl
          << endl
          << "\tgameSession1.turnIndex()\t= " << gameSession1.turnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tgameSession1.players.size()\t= " << gameSession1.players().size() << "\t(SHOULD BE: 2)" << endl;

     cout << endl
          << "GameSession::operator==, GameSession::operator!=" << endl
          << endl
          << "\tgameSession1 == gameSession1:\t" << ((gameSession1 == gameSession1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tgameSession1 != gameSession1:\t" << ((gameSession1 != gameSession1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameSession1 == gameSession2:\t" << ((gameSession1 == gameSession2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tgameSession1 != gameSession2:\t" << ((gameSession1 != gameSession2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     GameSession gameSessionCopy(gameSession1);

     cout << "gameSessionCopy = GameSession(gameSession1): " << endl
          << endl
          << "\tgameSessionCopy.turnIndex()\t= " << gameSessionCopy.turnIndex() << "\t(SHOULD BE: XXXX)" << endl
          << "\tgameSessionCopy.players.size()\t= " << gameSessionCopy.players().size() << "\t(SHOULD BE: 2)" << endl;

     return 0;
}