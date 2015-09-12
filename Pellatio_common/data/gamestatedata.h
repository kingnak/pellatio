#ifndef GAMESTATEDATA_H
#define GAMESTATEDATA_H

#include "boarddata.h"

class PELLATIO_COMMONSHARED_EXPORT GameStateData
{
public:
    GameStateData();

    PellatioDefinitions::Color currentPlayer() const { return m_currentPlayer; }
    void setCurrentPlayer(const PellatioDefinitions::Color &currentPlayer) { m_currentPlayer = currentPlayer; }

    BoardData board() const { return m_board; }
    void setBoard(const BoardData &board) { m_board = board; }

protected:
    PellatioDefinitions::Color m_currentPlayer;
    BoardData m_board;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, GameStateData);
};

#endif // GAMESTATEDATA_H
