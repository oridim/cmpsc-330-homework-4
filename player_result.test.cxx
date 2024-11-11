#include <iostream>

#include "player_result.h"
#include "player_result.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: player_result.test.cxx]" << endl
          << endl;

     PlayerResult playerResult1('O', 5, PlayerResult::WIN_KIND::winner);
     PlayerResult playerResult2('O', 5, PlayerResult::WIN_KIND::winner);

     cout << "playerResult1 = PlayerResult('O', 5, PlayerResult::WIN_KIND::winner): " << endl
          << endl
          << "\tplayerResult1.playerInitial()\t= '" << playerResult1.playerInitial() << "'\t(SHOULD BE: 'O')" << endl
          << "\tplayerResult1.score()\t\t= " << playerResult1.score() << "\t(SHOULD BE: 5)" << endl
          << "\tplayerResult1.winKind()\t\t= " << static_cast<int>(playerResult1.winKind()) << "\t(SHOULD BE: 2) [PlayerResult::WIN_KIND::winner]" << endl;

     cout << endl
          << "PlayerResult::operator==, PlayerResult::operator!=" << endl
          << endl
          << "\tplayerResult1 == playerResult1:\t" << ((playerResult1 == playerResult1) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tplayerResult1 != playerResult1:\t" << ((playerResult1 != playerResult1) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tplayerResult1 == playerResult2:\t" << ((playerResult1 == playerResult2) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tplayerResult1 != playerResult2:\t" << ((playerResult1 != playerResult2) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     PlayerResult playerResultCopy(playerResult1);

     cout << "playerResultCopy = PlayerResult(playerResult1): " << endl
          << endl
          << "\tplayerResultCopy.playerInitial()\t= '" << playerResultCopy.playerInitial() << "'\t(SHOULD BE: 'O')" << endl
          << "\tplayerResultCopy.score()\t\t= " << playerResultCopy.score() << "\t(SHOULD BE: 5)" << endl
          << "\tplayerResultCopy.winKind()\t\t= " << static_cast<int>(playerResultCopy.winKind()) << "\t(SHOULD BE: 2) [PlayerResult::WIN_KIND::winner]" << endl
          << endl;

     return 0;
}