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
public:
    //typedef PellatioDefinitions::Color Color;

    explicit InfoModel(QObject *parent = 0);

    ColorType::Color currentPlayer() const { return m_curPlayer; }

    void updateData(GameStateData data);

signals:
    void currentPlayerChanged();

public slots:

private:
    ColorType::Color m_curPlayer;
};

#endif // INFOMODEL_H
