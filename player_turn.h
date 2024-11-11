#ifndef _PLAYER_TURN_H_
#define _PLAYER_TURN_H_

// `class PlayerTurn`
//
// Represents structured data containing a turn completed by a player.
class PlayerTurn
{
private:
    // `int PlayerTurn._columnIndex`
    //
    // Represents what column in the Dots and Boxes gameboard grid that this move
    // was performed.
    int _columnIndex;

    // `char PlayerTurn._playerInitial`
    //
    // Represents the initial of the player who placed the move onto the Dots and Boxes
    // gameboard grid.
    char _playerInitial;

    // `int PlayerTurn._rowIndex`
    //
    // Represents what row in the Dots and Boxes gameboard grid that this move was
    // performed.
    int _rowIndex;

    // `int PlayerTurn._turnIndex`
    //
    // Represents the indexing number in the order in which turn actions were
    // performed on the Dots and Boxes gameboard grid.
    //
    // The indexing is determined by the owning container type.
    // (ex. `GameData` / `GameManager`)
    int _turnIndex;

public:
    PlayerTurn();
    PlayerTurn(int turnIndex, int row, int column, char playerInitial);

    PlayerTurn(const PlayerTurn &playerTurn);

    bool operator==(const PlayerTurn &rightHandTurn) const;
    bool operator!=(const PlayerTurn &rightHandTurn) const;

    int columnIndex() const { return this->_columnIndex; }
    char playerInitial() const { return this->_playerInitial; }
    int rowIndex() const { return this->_rowIndex; }
    int turnIndex() const { return this->_turnIndex; }
};

#endif