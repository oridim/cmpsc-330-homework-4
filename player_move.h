#ifndef _PLAYER_MOVE_H_
#define _PLAYER_MOVE_H_

// `class PlayerMove`
//
// Represents structured data containing a move computed by a player.
class PlayerMove
{
protected:
    // `int PlayerMove._columnIndex`
    //
    // Represents what column in the Dots and Boxes gameboard grid that this move
    // was performed.
    int _columnIndex;

    // `int PlayerMove._rowIndex`
    //
    // Represents what row in the Dots and Boxes gameboard grid that this move was
    // performed.
    int _rowIndex;

public:
    PlayerMove();
    PlayerMove(int row, int column);

    PlayerMove(const PlayerMove &playerMove);

    bool operator==(const PlayerMove &rightHandMove) const;
    bool operator!=(const PlayerMove &rightHandMove) const;

    int columnIndex() const { return this->_columnIndex; }
    int rowIndex() const { return this->_rowIndex; }
};

#endif