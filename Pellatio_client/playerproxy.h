#ifndef PLAYERPROXY_H
#define PLAYERPROXY_H

#include <pellatiodefinitions.h>

class GameInterface;

class PlayerProxy
{
public:
    PlayerProxy();
    virtual ~PlayerProxy() {}
    virtual void setGameInterface(GameInterface *lgi) = 0;
    virtual PellatioDefinitions::Color thisPlayer() const = 0;
    virtual void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm) = 0;
    virtual void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm) = 0;
    virtual void resetMove() = 0;
    virtual void confirmMove() = 0;
};

#endif // PLAYERPROXY_H
