#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include "gamecontroller.h"

class GameServer : public QTcpServer
{
public:
    GameServer(GameController *ctrl);

    void start();

protected:
    virtual void incomingConnection ( int socketDescriptor );

private:
    GameController *m_ctrl;
};

#endif // GAMESERVER_H
