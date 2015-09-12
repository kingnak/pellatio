#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include <player.h>

class LocalGameInterface;

class LocalPlayer : public Player
{
public:
    LocalPlayer(PellatioDefinitions::Color playerColor);

    void setGameInterface(LocalGameInterface *lgi);

    virtual void activate() {}
    virtual void deactivate() {}
    virtual void commitUpdates();
    virtual void showMove(MoveData move, BoardData board);

private:
    LocalGameInterface *m_inter;
};

#endif // LOCALPLAYER_H
