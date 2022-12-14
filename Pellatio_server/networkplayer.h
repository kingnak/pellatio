#ifndef NETWORKPLAYER_H
#define NETWORKPLAYER_H

#include <QObject>
#include "player.h"
#include "clientconnection.h"

class NetworkPlayer : public QObject, public Player
{
    Q_OBJECT
public:
    explicit NetworkPlayer(ClientConnection *conn, PellatioDefinitions::Color color, QObject *parent = 0);

    virtual void activate();
    virtual void deactivate();
    virtual void showMove(MoveData move, BoardData board);
    virtual void commitUpdates();
    virtual void askForRemis();
    virtual void remisDeclined();
    virtual void notifyTerminatedConnection();

private slots:
    void handleMessage(const Message &msg);
    void shutdown();

private:
    ClientConnection *m_conn;

};

#endif // NETWORKPLAYER_H
