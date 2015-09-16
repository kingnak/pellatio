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

    quint8 blackPoints() const { return m_blackPoints; }
    void setBlackPoints(quint8 points) { m_blackPoints = points; }

    quint8 redPoints() const { return m_redPoints; }
    void setRedPoints(quint8 points) { m_redPoints = points; }

    PellatioDefinitions::GameState state() const { return m_state; }
    void setGameState(PellatioDefinitions::GameState state) { m_state = state; }

    PellatioDefinitions::Color winner() const { return m_winner; }
    void setWinner(PellatioDefinitions::Color winner) { m_winner = winner; }

    bool hasWinner() const { return m_hasWinner; }
    void setHasWinner(bool hasWinner) { m_hasWinner = hasWinner; }

    //bool isRemisOffered() const { return m_remisOffered; }
    //void setRemisOffered(bool offered) { m_remisOffered = offered; }

protected:
    PellatioDefinitions::Color m_currentPlayer;
    BoardData m_board;
    quint8 m_blackPoints;
    quint8 m_redPoints;
    PellatioDefinitions::GameState m_state;
    PellatioDefinitions::Color m_winner;
    bool m_hasWinner;
    //bool m_remisOffered;

    DECLARE_SERIALIZABLE_EXPORT(PELLATIO_COMMONSHARED_EXPORT, GameStateData);
};

//Q_DECLARE_METATYPE(GameStateData)

#endif // GAMESTATEDATA_H
