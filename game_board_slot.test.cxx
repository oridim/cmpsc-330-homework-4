#include <iostream>

#include "game_board_slot.h"
#include "game_board_slot.cxx"

#include "player_move.h"
#include "player_move.cxx"

#include "player_turn.h"
#include "player_turn.cxx"

using namespace std;

int main()
{
     cout << "=> [UNIT TEST: game_board_slot.test.cxx]" << endl
          << endl;

     PlayerTurn playerTurn(3, 2, 4, 'D');

     GameBoardSlot undefinedSlot(0, 0); //

     GameBoardSlot dotSlot(0, 1, GameBoardSlot::SLOT_KIND::dot);
     GameBoardSlot scorableSlot(2, 1, GameBoardSlot::SLOT_KIND::scorable);
     GameBoardSlot spacerSlot(3, 4, GameBoardSlot::SLOT_KIND::spacer);

     GameBoardSlot initialSlot(5, 6, GameBoardSlot::SLOT_KIND::initial, playerTurn);
     GameBoardSlot lineSlot(7, 8, GameBoardSlot::SLOT_KIND::line, playerTurn);

     cout << "GameBoardSlot::determineSlotKind:" << endl
          << endl
          << "determineSlotKind(0, 0)\t= " << static_cast<int>(GameBoardSlot::determineSlotKind(0, 0)) << "\t(SHOULD BE: 1) [GameBoardSlot::SLOT_KIND::dot]" << endl
          << "determineSlotKind(0, 1)\t= " << static_cast<int>(GameBoardSlot::determineSlotKind(0, 1)) << "\t(SHOULD BE: 3) [GameBoardSlot::SLOT_KIND::spacer]" << endl
          << "determineSlotKind(1, 1)\t= " << static_cast<int>(GameBoardSlot::determineSlotKind(1, 1)) << "\t(SHOULD BE: 2) [GameBoardSlot::SLOT_KIND::scorable]" << endl
          << endl;

     cout << "undefinedSlot = GameBoardSlot(0, 0): " << endl
          << endl
          << "\tundefinedSlot.rowIndex()\t\t\t= " << undefinedSlot.rowIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tundefinedSlot.columnIndex()\t\t\t= " << undefinedSlot.columnIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tundefinedSlot.slotKind()\t\t\t= " << static_cast<int>(undefinedSlot.slotKind()) << "\t(SHOULD BE: 0)" << endl
          << "\tundefinedSlot.displayCharacter()\t\t= " << "'" << undefinedSlot.displayCharacter() << "'" << "\t(SHOULD BE: '!')" << endl
          << "\tundefinedSlot.playerTurn() == playerTurn\t= " << ((undefinedSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << endl;

     cout << "dotSlot = GameBoardSlot(0, 1, SLOT_KIND::dot): " << endl
          << endl
          << "\tdotSlot.rowIndex()\t\t\t= " << dotSlot.rowIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tdotSlot.columnIndex()\t\t\t= " << dotSlot.columnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tdotSlot.slotKind()\t\t\t= " << static_cast<int>(dotSlot.slotKind()) << "\t(SHOULD BE: 1)" << endl
          << "\tdotSlot.displayCharacter()\t\t= " << "'" << dotSlot.displayCharacter() << "'" << "\t(SHOULD BE: '.')" << endl
          << "\tdotSlot.playerTurn() == playerTurn\t= " << ((dotSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << endl;

     cout << "scorableSlot = GameBoardSlot(2, 1, SLOT_KIND::scorable): " << endl
          << endl
          << "\tscorableSlot.rowIndex()\t\t\t= " << scorableSlot.rowIndex() << "\t(SHOULD BE: 2)" << endl
          << "\tscorableSlot.columnIndex()\t\t= " << scorableSlot.columnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tscorableSlot.slotKind()\t\t\t= " << static_cast<int>(scorableSlot.slotKind()) << "\t(SHOULD BE: 2)" << endl
          << "\tscorableSlot.displayCharacter()\t\t= " << "'" << scorableSlot.displayCharacter() << "'" << "\t(SHOULD BE: ' ')" << endl
          << "\tscorableSlot.playerTurn() == playerTurn\t= " << ((scorableSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << endl;

     cout << "spacerSlot = GameBoardSlot(3, 4, SLOT_KIND::spacer): " << endl
          << endl
          << "\tspacerSlot.rowIndex()\t\t\t= " << spacerSlot.rowIndex() << "\t(SHOULD BE: 3)" << endl
          << "\tspacerSlot.columnIndex()\t\t= " << spacerSlot.columnIndex() << "\t(SHOULD BE: 4)" << endl
          << "\tspacerSlot.slotKind()\t\t\t= " << static_cast<int>(spacerSlot.slotKind()) << "\t(SHOULD BE: 3)" << endl
          << "\tspacerSlot.displayCharacter()\t\t= " << "'" << spacerSlot.displayCharacter() << "'" << "\t(SHOULD BE: ' ')" << endl
          << "\tspacerSlot.playerTurn() == playerTurn\t= " << ((spacerSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << endl;

     cout << "initialSlot = GameBoardSlot(5, 6, SLOT_KIND::initial, &playerTurn): " << endl
          << endl
          << "\tinitialSlot.rowIndex()\t\t\t= " << initialSlot.rowIndex() << "\t(SHOULD BE: 5)" << endl
          << "\tinitialSlot.columnIndex()\t\t= " << initialSlot.columnIndex() << "\t(SHOULD BE: 6)" << endl
          << "\tinitialSlot.slotKind()\t\t\t= " << static_cast<int>(initialSlot.slotKind()) << "\t(SHOULD BE: 4)" << endl
          << "\tinitialSlot.displayCharacter()\t\t= " << "'" << initialSlot.displayCharacter() << "'" << "\t(SHOULD BE: 'D')" << endl
          << "\tinitialSlot.playerTurn() == playerTurn\t= " << ((initialSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     cout << "lineSlot = GameBoardSlot(7, 8, SLOT_KIND::line, &playerTurn): " << endl
          << endl
          << "\tlineSlot.rowIndex()\t\t\t= " << lineSlot.rowIndex() << "\t(SHOULD BE: 7)" << endl
          << "\tlineSlot.columnIndex()\t\t\t= " << lineSlot.columnIndex() << "\t(SHOULD BE: 8)" << endl
          << "\tlineSlot.slotKind()\t\t\t= " << static_cast<int>(lineSlot.slotKind()) << "\t(SHOULD BE: 5)" << endl
          << "\tlineSlot.displayCharacter()\t\t= " << "'" << lineSlot.displayCharacter() << "'" << "\t(SHOULD BE: 'd')" << endl
          << "\tlineSlot.playerTurn() == playerTurn\t= " << ((lineSlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     cout << endl
          << "GameBoardSlot::operator==, GameBoardSlot::operator!=" << endl
          << endl
          << "\tundefinedSlot == undefinedSlot:\t" << ((undefinedSlot == undefinedSlot) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << "\tundefinedSlot != undefinedSlot:\t" << ((undefinedSlot != undefinedSlot) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tundefinedSlot == dotSlot:\t" << ((undefinedSlot == dotSlot) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << "\tundefinedSlot != dotSlot:\t" << ((undefinedSlot != dotSlot) ? "true" : "false") << "\t(SHOULD BE: true)" << endl
          << endl;

     GameBoardSlot copySlot(dotSlot);

     cout << "copySlot = GameBoardSlot(dotslot): " << endl
          << endl
          << "\tcopySlot.rowIndex()\t\t\t= " << copySlot.rowIndex() << "\t(SHOULD BE: 0)" << endl
          << "\tcopySlot.columnIndex()\t\t\t= " << copySlot.columnIndex() << "\t(SHOULD BE: 1)" << endl
          << "\tcopySlot.slotKind()\t\t\t= " << static_cast<int>(copySlot.slotKind()) << "\t(SHOULD BE: 1)" << endl
          << "\tcopySlot.displayCharacter()\t\t= " << "'" << copySlot.displayCharacter() << "'" << "\t(SHOULD BE: '.')" << endl
          << "\tcopySlot.playerTurn() == playerTurn\t= " << ((copySlot.playerTurn() == playerTurn) ? "true" : "false") << "\t(SHOULD BE: false)" << endl
          << endl;

     return 0;
}