#include "gamestatedata.h"

GameStateData::GameStateData()
    : m_currentPlayer(PellatioDefinitions::Black), m_blackPoints(0), m_redPoints(0),
      m_state(PellatioDefinitions::NotStarted), m_winner(PellatioDefinitions::Black),
      m_hasWinner(false)
{
}

void operator << (QVariant &data, const GameStateData &target)
{
    QVariantMap m;
    m["currentPlayer"] << target.m_currentPlayer;
    m["board"] << target.m_board;
    m["blackPoints"] << target.m_blackPoints;
    m["redPoints"] << target.m_redPoints;
    m["state"] << target.m_state;
    m["winner"] << target.m_winner;
    m["hasWinner"] << target.m_hasWinner;
    data << m;
}

void operator >> (const QVariant &data, GameStateData &target)
{
    QVariantMap m;
    data >> m;
    m["currentPlayer"] >> target.m_currentPlayer;
    m["board"] >> target.m_board;
    m["blackPoints"] >> target.m_blackPoints;
    m["redPoints"] >> target.m_redPoints;
    m["state"] >> target.m_state;
    m["winner"] >> target.m_winner;
    m["hasWinner"] >> target.m_hasWinner;
}
