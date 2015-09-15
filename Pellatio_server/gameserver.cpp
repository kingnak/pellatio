#include "gameserver.h"
#include "gamecontroller.h"
#include "networkplayer.h"
#include <QThread>

GameServer::GameServer(GameController *ctrl)
    : m_ctrl(ctrl)
{
}

void GameServer::start()
{
    listen(QHostAddress::Any, 8069);
}

void GameServer::incomingConnection(int socketDescriptor)
{
    /*
    ClientConnection *c = new ClientConnection(socketDescriptor, m_ctrl);
    //AH::Common::CleanupThread *t = new AH::Common::CleanupThread;
    QThread *t = new QThread;
    c->moveToThread(t);
    connect(t, SIGNAL(started()), c, SLOT(startup()));
    connect(t, SIGNAL(finished()), c, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));
    connect(c, SIGNAL(shutdown()), t, SLOT(quit()));
    //t->registerCleanupMethod(c, "cleanup");
    t->start();
    */
    QTcpSocket *tcp = new QTcpSocket(this);
    tcp->setSocketDescriptor(socketDescriptor);
    ClientConnection *c = new ClientConnection(tcp, m_ctrl, this);
    c->startup();
}
