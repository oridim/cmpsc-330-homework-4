#include <fstream>
#include <iostream>

#include "simple_vector.h"
#include "simple_hash_map.h"

#include "game_board_slot.cxx"
#include "game_board.cxx"

#include "game_data.cxx"
#include "game_result.cxx"
#include "game_session.cxx"

#include "player_move.cxx"
#include "player_result.cxx"
#include "player_turn.cxx"

#include "dummy_player.cxx"

using namespace std;

int main()
{
     // Indicate the start of the unit test
     cout << "=> [UNIT TEST: game_result.test.cxx]" << endl
          << endl;

     // Input stream is created to load the data for each test case.
     ifstream inputStream;
     inputStream.open("./Test Cases/GameData/game.professor-supplied.txt");

     GameData *gameData1 = GameData::deserializeGameData(inputStream);
     inputStream.close();

     inputStream.open("./Test Cases/GameData/game.two-winners.txt");
     GameData *gameData2 = GameData::deserializeGameData(inputStream);
     inputStream.close();

     inputStream.open("./Test Cases/GameData/game.no-contest.txt");
     GameData *gameData3 = GameData::deserializeGameData(inputStream);
     inputStream.close();

     // Create game boards for each test case
     GameBoard *gameBoard1 = gameData1->makeGameBoard();
     GameBoard *gameBoard2 = gameData2->makeGameBoard();
     GameBoard *gameBoard3 = gameData3->makeGameBoard();

     // Create player sets for each test case
     SimpleVector<const Player *> *playerSet1 = new SimpleVector<const Player *>();
     SimpleVector<const Player *> *playerSet2 = new SimpleVector<const Player *>();
     SimpleVector<const Player *> *playerSet3 = new SimpleVector<const Player *>();

     // Initialize players for game 1, game 2, and game 3
     playerSet1->push_back(new DummyPlayer('B'));
     playerSet1->push_back(new DummyPlayer('R'));

     playerSet2->push_back(new DummyPlayer('B'));
     playerSet2->push_back(new DummyPlayer('G'));
     playerSet2->push_back(new DummyPlayer('R'));

     playerSet3->push_back(new DummyPlayer('B'));
     playerSet3->push_back(new DummyPlayer('R'));

     // Create game sessions for each test case
     GameSession gameSession1(playerSet1, gameData1->turns().size());
     GameSession gameSession2(playerSet2, gameData2->turns().size());
     GameSession gameSession3(playerSet3, gameData3->turns().size());

     // Apply scorable captures on each game board
     gameBoard1->applyScorableCaptures();
     gameBoard2->applyScorableCaptures();
     gameBoard3->applyScorableCaptures();

     // Compute game results for each test case
     GameResult *gameResult1 = GameResult::computeGameResult(gameSession1, *gameBoard1);
     GameResult *gameResult2 = GameResult::computeGameResult(gameSession2, *gameBoard2);
     GameResult *gameResult3 = GameResult::computeGameResult(gameSession3, *gameBoard3);

     // Display expected and actual results for game 1
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

     // Retrieve and iterate over player results for game 1
     const SimpleVector<PlayerResult> &playerResults1 = gameResult1->playerResults();

     for (int index = 0; index < playerResults1.size(); index++)
     {
          // Get the result for each player
          const PlayerResult &playerResult = playerResults1.get(index);

          // Extract player information: initial, score, and win kind
          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          // Display the actual result for the current player
          cout
              << "\tplayerResults1.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     // Display expected and actual results for game 2
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

     // Retriece and iterate over player results for game 2
     const SimpleVector<PlayerResult> &playerResults2 = gameResult2->playerResults();

     for (int index = 0; index < playerResults2.size(); index++)
     {
          // Get the result for each player
          const PlayerResult &playerResult = playerResults2.get(index);

          // Extract player information: initial, score, and win kind
          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          // Display the actual result for the current player
          cout
              << "\tplayerResults2.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     // Display expected and actual results for game 3
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

     // Retrieve and iterate over player results for game 3
     const SimpleVector<PlayerResult> &playerResults3 = gameResult3->playerResults();

     for (int index = 0; index < playerResults3.size(); index++)
     {
          // Get the result for each player
          const PlayerResult &playerResult = playerResults3.get(index);

          // Extract player information: initial, score, and win kind
          char playerInitial = playerResult.playerInitial();
          int score = playerResult.score();
          PlayerResult::WIN_KIND winKind = playerResult.winKind();

          // Display the actual result for the current player
          cout
              << "\tplayerResults3.get(" << index << ")\t= PlayerResult('"
              << playerInitial << "', " << score << ", " << static_cast<int>(winKind)
              << ")" << endl;
     }

     // Serialize results to standard ouput for comparison with expected values
     cout << endl
          << "gameResults1->serializeGameResult()" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 3 boxes (win)." << endl
          << "Player R has 1 box." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult1->serializeGameResult(cout);

     cout << endl
          << endl
          << "gameResults2->serializeGameResult(cout)" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 2 boxes (tie)." << endl
          << "Player G has 2 boxes (tie)." << endl
          << "Player R has 1 box." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult2->serializeGameResult(cout);

     cout << endl
          << endl
          << "gameResults3->serializeGameResult(cout)" << endl
          << endl
          << "(SHOULD BE)" << endl
          << endl
          << "Player B has 0 boxes (no contest)." << endl
          << "Player R has 0 boxes (no contest)." << endl
          << endl
          << "(ACTUAL)" << endl
          << endl;

     gameResult3->serializeGameResult(cout);

     cout << endl;

     // Clean up dynamically allocated resources
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