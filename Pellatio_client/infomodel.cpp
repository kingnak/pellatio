#include "infomodel.h"

InfoModel::InfoModel(QObject *parent) :
    QObject(parent), m_curPlayer(static_cast<ColorType::Color> (PellatioDefinitions::Red))
{
}

void InfoModel::updateData(GameStateData data)
{
    if (data.currentPlayer() != m_curPlayer) {
        m_curPlayer = static_cast<ColorType::Color> (data.currentPlayer());
        emit currentPlayerChanged();
    }
}
