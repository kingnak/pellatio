#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <networkconnection.h>

class NetworkPlayer;
class Message;
class GameController;

class ClientConnection : public NetworkConnection
{
public:
    //ClientConnection(int socketDescriptor, GameController *ctrl);
    ClientConnection(QTcpSocket *sock, GameController *ctrl, QObject *parent = NULL);

protected slots:
    void cleanup();

protected:
    void receivedMessage(const Message &msg);

private:
    void handleVersion(const QVariant &v);

private:
    NetworkPlayer *m_player;
    bool m_versionReceived;
    GameController *m_ctrl;
};

#endif // CLIENTCONNECTION_H
