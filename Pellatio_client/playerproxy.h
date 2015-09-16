#ifndef PLAYERPROXY_H
#define PLAYERPROXY_H

#include <pellatiodefinitions.h>

class GameInterface;

class GameStateData;
class InteractionOptionsData;
class MoveData;

class PlayerProxy
{
public:
    PlayerProxy();
    virtual ~PlayerProxy() {}
    virtual void setGameInterface(GameInterface *lgi);
    virtual PellatioDefinitions::Color thisPlayer() const = 0;
    virtual void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm) = 0;
    virtual void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm) = 0;
    virtual void resetMove() = 0;
    virtual void confirmMove() = 0;

    virtual void giveUp() = 0;
    virtual void offerRemis() = 0;
    virtual void acceptRemis() = 0;
    virtual void declineRemis() = 0;

protected:
    virtual void updateAllData(const GameStateData &state, const InteractionOptionsData &interactOpts, const MoveData &preview);

protected:
    GameInterface *m_inter;
};

#endif // PLAYERPROXY_H
