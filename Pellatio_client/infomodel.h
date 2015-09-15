#ifndef INFOMODEL_H
#define INFOMODEL_H

#include <QObject>
#include <pellatiodefinitions.h>
#include <data/gamestatedata.h>
#include "pellatioqmldefinitions.h"

class InfoModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ColorType::Color currentPlayer READ currentPlayer NOTIFY currentPlayerChanged)
    Q_PROPERTY(ColorType::Color thisPlayer READ thisPlayer NOTIFY thisPlayerChanged)
    Q_PROPERTY(quint8 blackPoints READ blackPoints NOTIFY blackPointsChanged)
    Q_PROPERTY(quint8 redPoints READ redPoints NOTIFY redPointsChanged)
public:
    //typedef PellatioDefinitions::Color Color;

    explicit InfoModel(QObject *parent = 0);

    ColorType::Color currentPlayer() const { return static_cast<ColorType::Color> (m_data.currentPlayer()); }
    ColorType::Color thisPlayer() const { return m_thisPlayer; }
    quint8 blackPoints() const { return m_data.blackPoints(); }
    quint8 redPoints() const { return m_data.redPoints(); }

    void setThisPlayer(ColorType::Color player);

    void updateData(GameStateData data);

signals:
    void currentPlayerChanged();
    void thisPlayerChanged();
    void blackPointsChanged();
    void redPointsChanged();

    void won();
    void lost();
    void terminated();

public slots:

private:
    GameStateData m_data;
    ColorType::Color m_thisPlayer;
};

#endif // INFOMODEL_H
