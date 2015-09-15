#include "infomodel.h"

InfoModel::InfoModel(QObject *parent) :
    QObject(parent)
{
}

void InfoModel::setThisPlayer(ColorType::Color player)
{
    if (player == m_thisPlayer)
        return;
    m_thisPlayer = player;
    emit thisPlayerChanged();
}

void InfoModel::updateData(GameStateData data)
{
    //GameStateData old = m_data;
    m_data = data;
    emit currentPlayerChanged();
    emit blackPointsChanged();
    emit redPointsChanged();

    if (data.hasWinner()) {
        if (data.winner() == m_thisPlayer) {
            emit won();
        } else {
            emit lost();
        }
    }

}
