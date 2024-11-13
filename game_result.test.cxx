#include <fstream>
#include <iostream>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "game_board.h"
#include "game_board.cxx"

#include "player.h"
#include "player.cxx"

#include "game_data.h"
#include "game_data.cxx"

#include "game_session.h"
#include "game_session.cxx"

#include "player_result.h"
#include "player_result.cxx"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

#include "game_result.h"
#include "game_result.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_result.test.cxx]" << endl
          << endl;

     ifstream inputStream;
     inputStream.open("./Test Cases/game.professor-supplied.txt");

     GameData *gameData1 = GameData::readGameData(inputStream);
     inputStream.close();

     inputStream.open("./Test Cases/game.two-winners.txt");
     GameData *gameData2 = GameData::readGameData(inputStream);
     inputStream.close();

     inputStream.open("./Test Cases/game.no-contest.txt");
     GameData *gameData3 = GameData::readGameData(inputStream);
     inputStream.close();

     GameBoard *gameBoard1 = gameData1->makeGameBoard();
     GameBoard *gameBoard2 = gameData2->makeGameBoard();
     GameBoard *gameBoard3 = gameData3->makeGameBoard();

     SimpleVector<Player> *playerSet1 = new SimpleVector<Player>();
     SimpleVector<Player> *playerSet2 = new SimpleVector<Player>();
     SimpleVector<Player> *playerSet3 = new SimpleVector<Player>();

     playerSet1->push_back(Player('B'));
     playerSet1->push_back(Player('R'));

     playerSet2->push_back(Player('B'));
     playerSet2->push_back(Player('G'));
     playerSet2->push_back(Player('R'));

     playerSet3->push_back(Player('B'));
     playerSet3->push_back(Player('R'));

     GameSession gameSession1(playerSet1, gameData1->turns().size());
     GameSession gameSession2(playerSet2, gameData2->turns().size());
     GameSession gameSession3(playerSet3, gameData3->turns().size());

     gameBoard1->applyScorableCaptures();
     gameBoard2->applyScorableCaptures();
     gameBoard3->applyScorableCaptures();

     GameResult *gameResult1 = GameResult::computeGameResult(gameSession1, *gameBoard1);
     GameResult *gameResult2 = GameResult::computeGameResult(gameSession2, *gameBoard2);
     GameResult *gameResult3 = GameResult::computeGameResult(gameSession3, *gameBoard3);

     cout << "gameResult1 = GameResult::computeGameResult(*gameBoard1):" << endl
          << endl
          << "\tgameResult1.winKind()\t\t= " << static_cast<int>(gameResult1->winKind()) << "\t(SHOULD BE: 2) [GameResult::WIN_KIND::singular]" << endl
          << "\tgameResult1.highestScore()\t= " << gameResult1->highestScore() << "\t(SHOULD BE: 3)" << endl;

     cout << endl
          << "playerResults1 = gameResult1->playerResults()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "\tplayerResults1.get(0)   = PlayerResult('B', 3, 2)\t[PlayerResult::WIN_KIND::winner]" << endl
          << "\tplayerResults1.get(1)   = PlayerResult('R', 1, 1)\t[PlayerResult::WIN_KIND::loser]" << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     const SimpleVector<PlayerResult> &playerResults1 = gameResult1->playerResults();

     for (int index = 0; index < playerResults1.size(); index++)
     {
          const PlayerResult &playerResult = playerResults1.get(index);

          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          cout
              << "\tplayerResults1.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     cout
         << endl
         << "gameResult2 = GameResult::computeGameResult(*gameBoard2):" << endl
         << endl
         << "\tgameResult2.winKind()\t\t= " << static_cast<int>(gameResult2->winKind()) << "\t(SHOULD BE: 3) [GameResult::WIN_KIND::multiple]" << endl
         << "\tgameResult2.highestScore()\t= " << gameResult2->highestScore() << "\t(SHOULD BE: 2)" << endl;

     cout << endl
          << "playerResults2 = gameResult2->playerResults()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "\tplayerResults1.get(0)   = PlayerResult('B', 2, 2)\t[PlayerResult::WIN_KIND::winner]" << endl
          << "\tplayerResults1.get(1)   = PlayerResult('G', 2, 2)\t[PlayerResult::WIN_KIND::winner]" << endl
          << "\tplayerResults1.get(1)   = PlayerResult('R', 1, 1)\t[PlayerResult::WIN_KIND::loser]" << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     const SimpleVector<PlayerResult> &playerResults2 = gameResult2->playerResults();

     for (int index = 0; index < playerResults2.size(); index++)
     {
          const PlayerResult &playerResult = playerResults2.get(index);

          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          cout
              << "\tplayerResults2.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     cout
         << endl
         << "gameResult3 = GameResult::computeGameResult(*gameBoard3):" << endl
         << endl
         << "\tgameResult3.winKind()\t\t= " << static_cast<int>(gameResult3->winKind()) << "\t(SHOULD BE: 1) [GameResult::WIN_KIND::nocontest]" << endl
         << "\tgameResult3.highestScore()\t= " << gameResult3->highestScore() << "\t(SHOULD BE: 0)" << endl;

     cout << endl
          << "playerResults3 = gameResult3->playerResults()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "\tplayerResults3.get(0)   = PlayerResult('B', 0, 1)\t[PlayerResult::WIN_KIND::loser]" << endl
          << "\tplayerResults3.get(1)   = PlayerResult('R', 0, 1)\t[PlayerResult::WIN_KIND::loser]" << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     const SimpleVector<PlayerResult> &playerResults3 = gameResult3->playerResults();

     for (int index = 0; index < playerResults3.size(); index++)
     {
          const PlayerResult &playerResult = playerResults3.get(index);

          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          cout
              << "\tplayerResults3.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     cout << endl
          << "gameResults1->renderGameResult()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 3 boxes (win)." << endl
          << "Player R has 1 box." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult1->renderGameResult();

     cout << endl
          << endl
          << "gameResults2->renderGameResult()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 2 boxes (tie)." << endl
          << "Player G has 2 boxes (tie)." << endl
          << "Player R has 1 box." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult2->renderGameResult();

     cout << endl
          << endl
          << "gameResults3->renderGameResult()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 0 boxes (no contest)." << endl
          << "Player R has 0 boxes (no contest)." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult3->renderGameResult();

     cout << endl;

     delete gameResult3;
     delete gameResult2;
     delete gameResult1;

     delete gameBoard3;
     delete gameBoard2;
     delete gameBoard1;

     delete gameData3;
     delete gameData2;
     delete gameData1;

     return 0;
}