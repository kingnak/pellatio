#include "gamestatedata.h"

GameStateData::GameStateData()
    : m_currentPlayer(PellatioDefinitions::Black)
{
}

void operator << (QVariant &data, const GameStateData &target)
{
    QVariantMap m;
    m["currentPlayer"] << target.m_currentPlayer;
    m["board"] << target.m_board;
    data << m;
}

void operator >> (const QVariant &data, GameStateData &target)
{
    QVariantMap m;
    data >> m;
    m["currentPlayer"] >> target.m_currentPlayer;
    m["board"] >> target.m_board;
}
