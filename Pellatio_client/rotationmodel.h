#ifndef ROTATIONMODEL_H
#define ROTATIONMODEL_H

#include <QObject>
#include <data/interactionoptionsdata.h>

class GameInterface;

class RotationModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool canRotateCW READ canRotateCW NOTIFY canRotateCWChanged)
    Q_PROPERTY(bool canRotateCCW READ canRotateCCW NOTIFY canRotateCCWChanged)
public:
    explicit RotationModel(GameInterface *ctrl, QObject *parent = 0);

    bool canRotateCW() const;
    bool canRotateCCW() const;

    void updateData(InteractionOptionsData data);

signals:
    void canRotateCWChanged();
    void canRotateCCWChanged();

public slots:
    void rotateCW();
    void rotateCCW();

private:
    GameInterface *m_ctrl;
    InteractionOptionsData m_data;
};

#endif // ROTATIONMODEL_H
