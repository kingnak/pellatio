#ifndef LOCALGAMEINTERFACE_H
#define LOCALGAMEINTERFACE_H

#include "gameinterface.h"
#include <QMap>

class PlayerProxy;

class DualGameInterface : public GameInterface
{
public:
    explicit DualGameInterface(PlayerProxy *p1, PlayerProxy *p2, QObject *parent = NULL);

    virtual void confirmMove();
    virtual void resetMove();
    virtual void select(PellatioDefinitions::FieldIndex idx);
    virtual void rotateSelected(PellatioDefinitions::Rotation rot);

    virtual PellatioDefinitions::Color thisPlayer();

    virtual void animateMove(MoveData move);

private:
    QMap<PellatioDefinitions::Color, PlayerProxy *> m_player;
    bool m_anim;
};

#endif // LOCALGAMEINTERFACE_H
