#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include "gamecontroller.h"
#include "pellatio_server_global.h"

class PELLATIO_SERVERSHARED_EXPORT GameServer : public QTcpServer
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
