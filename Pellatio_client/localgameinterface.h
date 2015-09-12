#ifndef LOCALGAMEINTERFACE_H
#define LOCALGAMEINTERFACE_H

#include "gameinterface.h"
#include <QMap>

class LocalPlayer;

class LocalGameInterface : public GameInterface
{
public:
    explicit LocalGameInterface(QObject *parent = NULL);

    void addLocalPlayer(LocalPlayer *p);

    virtual void confirmMove();
    virtual void resetMove();
    virtual void select(PellatioDefinitions::FieldIndex idx);
    virtual void rotateSelected(PellatioDefinitions::Rotation rot);

    virtual PellatioDefinitions::Color thisPlayer();

    virtual void animateMove(MoveData move);

private:
    QMap<PellatioDefinitions::Color, LocalPlayer *> m_player;
    bool m_anim;
};

#endif // LOCALGAMEINTERFACE_H
