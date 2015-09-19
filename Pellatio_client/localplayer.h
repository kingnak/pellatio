#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <player.h>
#include <playerproxy.h>

class GameInterface;

class LocalPlayer : public Player, public PlayerProxy
{
public:
    LocalPlayer(PellatioDefinitions::Color playerColor);

    virtual PellatioDefinitions::Color thisPlayer() const;

    virtual void activate() {}
    virtual void deactivate() {}
    virtual void commitUpdates();
    virtual void showMove(MoveData move, BoardData board);
    virtual void askForRemis();
    virtual void remisDeclined();

    virtual void giveUp();
    virtual void offerRemis();
    virtual void acceptRemis();
    virtual void declineRemis();

    virtual void notifyTerminatedConnection();

    void selectField(PellatioDefinitions::FieldIndex idx, bool autoConfirm);
    void rotateSelected(PellatioDefinitions::Rotation dir, bool autoConfirm);
    void resetMove();
    void confirmMove();
};

#endif // LOCALPLAYER_H
